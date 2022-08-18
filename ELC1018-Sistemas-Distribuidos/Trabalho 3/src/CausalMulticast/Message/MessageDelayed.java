package CausalMulticast.Message;
import java.net.InetAddress;

/**
 * Classe que organiza mensagens com recebimento atrasado
 * @author Gabriel Haddad, Pedro Carvalho 
 * @version 1.0
 */
public class MessageDelayed {
    // A mensagem com recebimento atrasado
    public MessageClockVector message;
    // O endereço do remetente
    public InetAddress sender;

    public MessageDelayed(MessageClockVector message, InetAddress sender) {
        this.message = message;
        this.sender = sender;
    }

    // Formatador para o output da mensagem
    @Override
    public String toString() {
        return String.format("%s, <%s>}", message, sender);
    }
}