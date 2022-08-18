package CausalMulticast.Message;
import java.io.*;
import java.util.Arrays;

/**
 * Classe que organiza as mensagens recebidas
 * @author Gabriel Haddad, Pedro Carvalho
 * @version 1.0
 */
public class MessageClockVector implements Serializable {
    // A mensagem recebida
    public String content;
    // O vetor de relógios
    public int[] clockArray;

    public MessageClockVector(String content, int[] clockArray) {
        this.content = content;
        this.clockArray = clockArray;
    }

    /**
     * Método pra serializar uma mensagem
     * @return mensagem
     * @throws IOException
     */
    public byte[] serialize() throws IOException {
        var out = new ByteArrayOutputStream();
        var os = new ObjectOutputStream(out);
        os.writeObject(this);
        return out.toByteArray();
    }

    /**
     * Método  pra desserializar uma mensagem
     * @param data array de bytes
     * @return mensagem
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public static MessageClockVector deserialize(byte[] data) throws IOException, ClassNotFoundException {
        var in = new ByteArrayInputStream(data);
        var is = new ObjectInputStream(in);
        return (MessageClockVector) is.readObject();
    }

    // Formatador para o output da mensagem
    @Override
    public String toString() {
        return String.format("<MSG-REC> '%s', <CV> %s", content, Arrays.toString(clockArray));
    }
}
