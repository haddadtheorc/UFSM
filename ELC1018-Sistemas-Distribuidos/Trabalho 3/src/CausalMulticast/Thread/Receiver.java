package CausalMulticast.Thread;

import java.net.*;

import CausalMulticast.Middleware;
import CausalMulticast.Message.MessageClockVector;

/**
 * Classe pra receber mensagens de usuários
 * @author Gabriel Haddad, Pedro Carvalho 
 * @version 1.0
 */
public class Receiver extends Thread {
    public interface IReceiver {
        void messageReceived(MessageClockVector message, InetAddress sender);
    }

    // O middleware recebedor das mensagens
    private IReceiver receiver;
    // O socket de recebimento de mensagens
    private DatagramSocket socket;
    // O buffer para armazenamento do pacote recebido
    private final byte[] buffer = new byte[65535];

    public Receiver(IReceiver receiver) throws SocketException {
        this.receiver = receiver;
        this.socket = new DatagramSocket(Middleware.uniPort);
    }

    /**
     * Método pra receber mensagens de usuários, uma thread rodando continuamente que busca DatagramPackets
     */
    @Override
    public void run() {
        try {
            while (true) {
                var packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                // Ao receber mensagem, chama o middleware para tratar o que deve ser feito
                receiver.messageReceived(MessageClockVector.deserialize(packet.getData()), packet.getAddress());
            }
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
