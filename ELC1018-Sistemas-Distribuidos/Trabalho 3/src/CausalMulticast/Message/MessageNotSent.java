package CausalMulticast.Message;
import java.net.InetAddress;

/**
 * Classe que organiza mensagens com envio atrasado
 * @author Gabriel Haddad, Pedro Carvalho 
 * @version 1.0
 */
public class MessageNotSent {
    // A mensagem com envio atrasado
    public byte[] serializedMessage;
    // O endereço do destinatário
    public InetAddress recipient;

    public MessageNotSent(byte[] serializedMessage, InetAddress recipient) {
        this.serializedMessage = serializedMessage;
        this.recipient = recipient;
    }
}