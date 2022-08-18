package CausalMulticast.Thread;

import java.io.*;
import java.net.*;
import java.util.*;

import CausalMulticast.Middleware;
import CausalMulticast.Pipe.AddressComparator;

/**
 * Classe responsável por verificar e executar o multicast com os demais processos que estão conectados
 * @author Gabriel Haddad, Pedro Carvalho 
 * @version 1.0
 */
public class Discovery extends Thread {

    // A mensagem default de descoberta
    private static final String discoveryMessage = "PING";
    // O array de clientes descobertos
    public ArrayList<InetAddress> discovered;
    // O socket para o descobrimento
    private MulticastSocket socket;
    // O endereço do grupo de clientes
    private InetAddress group;
    // O comparador de endereços
    private AddressComparator comparator;

    public Discovery() throws IOException {
        socket = new MulticastSocket(Middleware.multiPort);
        comparator = new AddressComparator();
        group = InetAddress.getByName(Middleware.multiAddress);
        discovered = new ArrayList<>();
    }

    /**
     * Método pra descobrir os clientes conectados, uma thread rodando continuamente que procura e salva novos usuários
     */
    @Override
    public void run() {
        var buffer = new byte[32];

        try {
            System.out.println("\n<DESCOBERTA> Serviço iniciado.\n");
            socket.joinGroup(group);

            // Ao iniciar, envia mensagem de descoberta
            ping();

            while(true) {
                // Recebe mensagem de descoberta
                var receivedMessage = new DatagramPacket(buffer, buffer.length);
                socket.receive(receivedMessage);
                var messageContent = new String(receivedMessage.getData(), 0, receivedMessage.getLength(), "UTF-8");

                // Se for uma mensagem de descoberta, salva o endereço do seu remetente
                if(messageContent.equals(discoveryMessage)) {
                    synchronized (this) {
                        var client = receivedMessage.getAddress();
                        var knownClient = false;

                        // Se já o conhece, ignora
                        for(InetAddress address : discovered) {
                            if(address.equals(client)) {
                                knownClient = true;
                            }
                        }

                        // Senão, adiciona ao array de clientes conhecidos
                        if(!knownClient) {
                            System.out.println(String.format("\n<DESCOBERTA> Cliente %s conectado. \n", client.getHostAddress()));

                            discovered.add(client);
                            discovered.sort(comparator);

                            // Envia mensagem de descoberta para o novo cliente
                            ping();
                        }
                    }
                }
            }
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Método pra enviar discoveryPacket
     * @throws IOException
     */
    private void ping() throws IOException {
        DatagramPacket discoveryPacket = new DatagramPacket(discoveryMessage.getBytes("UTF-8"), 
                                    discoveryMessage.length(), group, Middleware.multiPort);
        socket.send(discoveryPacket);
    }
}
