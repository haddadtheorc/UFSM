package ClientApplication;
import CausalMulticast.*;
import java.io.*;

/**
 * Classe que inicia a aplicação, middleware e controle prévio de mensagens
 * @author Gabriel Haddad, Pedro Carvalho 
 * @version 1.0
 */
public class Client implements Middleware.ICausalMulticast {
    private Middleware middleware;

    public Client() throws IOException {
        middleware = new Middleware(this);
    }

    /**
     * Método que incia middleware e lê mensagens
     * @throws IOException
     */
    public void start() throws IOException {

        middleware.start();

        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        while(true) {

            // Lê a mensagem do usuário
            String msg = bufferedReader.readLine();

            // Se for para enviar as atrasadas, envia
            if(msg.equals("/sendall")) {
                middleware.sendNotSent();
            }
            // Se tem atrasadas, avisa e não envia
            else if(middleware.delayedMessages.size() > 0) {
                System.out.println("\n<DLY> Can't send while having delayed messages.\n");
            }
            // Senão, envia
            else {
                middleware.mcsend(msg);
            }
        }
    }

    /**
     * Método obrigatório de envio de mensagens
     */
    @Override
    public void deliver(String msg) {
        System.out.println("\n<MSG-DEL> " + msg);
    }
}