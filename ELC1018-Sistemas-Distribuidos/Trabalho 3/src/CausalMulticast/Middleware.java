package CausalMulticast;

import java.io.*;
import java.net.*;
import java.util.*;

import CausalMulticast.Message.*;
import CausalMulticast.Thread.*;

/**
 * Classe que armazena métodos responsáveis pelo envio e recebimento de mensagens, assim como pela manutenção dos vetores de relógios.
 * @author Gabriel Haddad, Pedro Carvalho
 * @version 1.0
 */
public class Middleware implements Receiver.IReceiver {
    public static String multiAddress = "228.5.6.7";
    public static int multiPort = 6789;
    public static int uniPort = 6790;

    /**
     * Interface definida na especificação do trabalho. Utilizada pelo Client.
     */
    public interface ICausalMulticast {
        void deliver(String msg);
    }

    // O cliente que está utilizando o Middleware
    private ICausalMulticast client;
    // Endereço do cliente atual
    private InetAddress currentAddress;
    private DatagramSocket socket;
    

    // A thread de descoberta de clientes
    private Discovery discovery;
    // A thread de recebimento de mensagens
    private Receiver receiver;

    // O vetor de relógios do cliente atual
    private int[] clockArray;
    // O índice do cliente atual no vetor de relógios'
    private int indexClockArray;
    // A lista de mensagens com recebimento atrasado
    public ArrayList<MessageDelayed> delayedMessages;
    // A lista de mensagens com envio atrasado
    private ArrayList<MessageNotSent> notSentMessages;

    public Middleware(ICausalMulticast client) throws IOException {
        this.client = client;
        this.currentAddress = InetAddress.getLocalHost();
        this.socket = new DatagramSocket();

        this.discovery = new Discovery();
        this.receiver = new Receiver(this);

        this.indexClockArray = -1;
        this.delayedMessages = new ArrayList<MessageDelayed>();
        this.notSentMessages = new ArrayList<MessageNotSent>();
    }

    /**
     * Método responsável por iniciar o middleware. Continuamente escuta por mensgens de descoberta/comunicação
     */
    public void start() {
        System.out.println(String.format("\n<MIDDLEWARE> Host %s iniciado.\n", currentAddress.getHostAddress()));
        discovery.start();
        receiver.start();
    }

    /**
     * Método responsável pela lógica de envio de mensagens
     * @param msg mensagem que será enviada para outros clientes
     */
    public void mcsend(String msg) {
        // Se o indice do array for menor que 0, significa que ele nao foi criado ainda entao inicializa
        if(indexClockArray < 0) {
            initializeClockArray();
        }

        try {
            // Coleta a mensagem
            var br = new BufferedReader(new InputStreamReader(System.in));
            var message = new MessageClockVector(msg, clockArray);
            var messageBytes = message.serialize();

            // Seleciona para quem fará o envio
            var addressToSend = new ArrayList<InetAddress>();
            // Pergunta se devemos enviar para todos os endereços
            System.out.println("Send to all? [Y/n]");
            // Em caso negativo, pergunta individualmente
            if(br.readLine().equalsIgnoreCase("n")) {
                // Pergunta se deseja o usuário enviar mensagem para aquele endereço
                for(InetAddress address : discovery.discovered) {
                    System.out.print(String.format("Send to %s? [Y/n]", address));
                    // Se não, adiciona a mensagem e o endereço para o vetor de mensagens não enviadas / com envio atrasado
                    if(br.readLine().equalsIgnoreCase("n")) {
                        notSentMessages.add(new MessageNotSent(messageBytes, address));
                    }
                    // Se sim, adiciona o endereço para o vetor de mensagens para enviar
                    else {
                        addressToSend.add(address);
                    }
                }
            // Em caso positivo, adiciona todos os endereços à lista de envio
            } else {
                for(InetAddress address : discovery.discovered) {
                    addressToSend.add(address);
                }
            }

            // Para cada endereço, dentro do vetor de endereços a serem enviados
            // envia um packet atraves do socket em unicast para cada endereço
            for(InetAddress address : addressToSend) {
                DatagramPacket packet = new DatagramPacket(messageBytes, messageBytes.length, address, uniPort);
                socket.send(packet);
            }

            // Incrementa o valor do indice do relogio, de acordo com o processo atual
            clockArray[indexClockArray]++;
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Método responsável por enviar todas as mensagens ainda não enviadas para determinado endereço. 
     * Para isso, o usuário deve enviar a mensagem "/sendall" durante a execução do programa.
     */
    public void sendNotSent() throws IOException {
        synchronized (this) {
            // Limpa o array de mensagens não enviadas em ordem, fazendo o envio para o par de endereço e mensagem
            while(notSentMessages.size() > 0) {
                var message = notSentMessages.get(0);
                var messageBytes = message.serializedMessage;
                var packet = new DatagramPacket(messageBytes, messageBytes.length, message.recipient, uniPort);

                System.out.println(String.format("\n<MID> Delayed message sent to %s.\n", 
                                   message.recipient.getHostAddress()));

                socket.send(packet);
                notSentMessages.remove(0);
            }
        }
    }

    /**
     * Método responsável pelo recebimento de mensagens por determinado cliente
     * 
     * @param message Mensagem recebida
     * @param sender Remetente da respectiva mensagem 
     */
    @Override
    public void messageReceived(MessageClockVector message, InetAddress sender) {
        synchronized (this) {
            // Se o indice do array for menor que 0, significa que ele nao foi criado ainda entao inicializa
            if(indexClockArray < 0) {
                initializeClockArray();
            }
            
            // A mensagem sempre chega e é printada, mas deve ser checada se será entregue
            System.out.println("\n" + message.toString() + 
                                "\n<CLK> Current local clock: " + Arrays.toString(clockArray));

            // Se não puder entregar a mensagem, adiciona ela na lista de mensagens com recebimento atrasado
            if(!canDeliver(message)) {
               delayedMessages.add(new MessageDelayed(message, sender));
                System.out.printf("\n<DLY><%s> MSG %s was delayed.\n<DLY> Delayed messages:\n%s\n",
                                   sender.getHostAddress(), message.content, Arrays.toString(delayedMessages.toArray()));
                return;
            }

            // Se puder, entrega e as demais que estavam atrasadas
            deliverMessage(message, sender);
            receiveDelayed();
        }
    }

    /**
     * Método responsável para receber as mensagens atrasadas
     */
    private void receiveDelayed() {
        for(int i = 0; i < delayedMessages.size(); i++) {
            var delayedMessage = delayedMessages.get(i);

            // Verifica se a mensagem pode ser enviada
            if(canDeliver(delayedMessage.message)) {
                deliverMessage(delayedMessage.message, delayedMessage.sender);
                delayedMessages.remove(i);

                // Checa recursivamente se há mais mensagens atrasadas
                receiveDelayed();
                break;
            }
        }
    }

    /**
     * Método responsável por verificar se a mensagem atrasada pode ser enviada.
     * @param message Mensagem em questão
     * @return boolean: Resposta
     */
    private boolean canDeliver(MessageClockVector message) {
        for(int i = 0; i < clockArray.length; i++) {
            // Se o valor do clock da mensagem for maior que o valor do clock local, não pode entregar
            if(message.clockArray[i] > clockArray[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Método responsável por entregar as mensagens ao usuário
     * @param message Mensagem a ser entregue
     * @param sender Remetente da mensagem
     */
    private void deliverMessage(MessageClockVector message, InetAddress sender) {
        var indexOfSource = getAddressIndex(sender);

        // Incrementa o valor do indice do relogio, de acordo com o processo eremente
        if(indexOfSource != indexClockArray) {
            clockArray[indexOfSource]++;
        }

        client.deliver(message.content);
    }

    /**
     * Método responsável por inicializar o vetor de relógios.
     */
    private void initializeClockArray() {
        System.out.println("\n<MID> Initializing clock vector.\n");

        var allIps = discovery.discovered;

        this.clockArray = new int[allIps.size()];
        this.indexClockArray = getAddressIndex(currentAddress);

        for(int i = 0; i < allIps.size(); i++) {
            clockArray[i] = 0;
        }
    }

    /**
     * Método responsável por obter o índice de cada endereço de cliente, necessário para manutenção do vetor de relógios
     * @param address Endereço de IP do cliente
     * @return int: Um índice para o endereço
     */
    private int getAddressIndex(InetAddress address) {
        var allIps = discovery.discovered;

        for(int i = 0; i < allIps.size(); i++) {
            if(allIps.get(i).getHostAddress().equals(address.getHostAddress())) {
                return i;
            }
        }

        return -1;
    }
}