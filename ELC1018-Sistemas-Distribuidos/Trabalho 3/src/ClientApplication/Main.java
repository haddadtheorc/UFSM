package ClientApplication;

/**
 * Classe que inicia o programa.
 * @author Gabriel Haddad, Pedro Carvalho
 * @version 1.0
 */
public class Main {
    /**
     * Método que inicia o cliente.
     * @param args String[]: argumentos de linha de comando.
     */
    public static void main(String[] args) {
        try {
            new Client().start();
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
