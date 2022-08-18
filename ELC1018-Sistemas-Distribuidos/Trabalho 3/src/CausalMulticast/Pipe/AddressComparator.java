package CausalMulticast.Pipe;

import java.net.InetAddress;
import java.util.Comparator;

/**
 * Classe responsável por realizar uma comparação entre dois endereços de clientes.
 * @author Gabriel Haddad, Pedro Carvalho 
 * @version 1.0
 */
public class AddressComparator implements Comparator<InetAddress> {
    /**
     * Método responsável por realizar esta comparação.
     * @param address1 Endereço a ser comparado.
     * @param address2 Endereço a ser comparado
     * @return int: Caso address1 < address2, retorna um valor negativo. 
     *              Caso address1 = address2, retorna 0. 
     *              Caso address1 > address2, retorna um valor positivo.
     */
    @Override
    public int compare(InetAddress address1, InetAddress address2) {
        return address1.getHostAddress().compareTo(address2.getHostAddress());
    }
}
