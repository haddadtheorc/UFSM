import java.rmi.*;
import java.util.*;
import java.rmi.server.UnicastRemoteObject;

public class RoomChat extends UnicastRemoteObject implements IRoomChat{
    // RFA2: Cada sala (RoomChat) da roomList deve manter uma lista de usuários (userList). 
    // A lista de usuários deve declarada como private Map<String, IUserChat> userList.
    private Map<String, IUserChat> userList;
    private String roomName;
    private boolean isOpen;
    
    
    public RoomChat(String roomName) throws RemoteException {
        super();
        this.roomName = roomName;
        userList = new HashMap<String, IUserChat>();
        isOpen = true;
    }


    public String getRoomName() throws RemoteException {
        return roomName;
    }


    public void joinRoom(String usrName, IUserChat user) throws RemoteException {
        // Adiciona o usuário ao mapa de usuários (userList) da sala.
        userList.put(usrName, user);
        
        // Para cada usuário da sala, envia uma mensagem de que o usuário entrou na sala
        for(Map.Entry<String, IUserChat> entry : userList.entrySet()) {
            try {
                entry.getValue().deliverMsg(usrName, " has entered room " + roomName + ".");
            } catch (Exception exception) {
                System.out.println("RoomChat error: " + exception.getMessage());
                exception.printStackTrace();
            }
        }
    }


    // RFA12: Os usuários devem sair da sala invocando o método remoto leaveRoom(String usrName) da sala.
    public void leaveRoom(String usrName) throws RemoteException {

        // Para cada usuário da sala, envia uma mensagem de que o usuário saiu da sala
        for(Map.Entry<String, IUserChat> entry : userList.entrySet()) {
            try {
                entry.getValue().deliverMsg(usrName, " has left room " + roomName + ".");
            } 
            catch (Exception exception) {
                System.out.println("RoomChat error: " + exception.getMessage());
                exception.printStackTrace();
            }
        }
        // Remove o usuário do mapa de usuários (userList) da sala .
        userList.remove(usrName);
    }
    

    public void closeRoom() throws RemoteException {
        // Para cada usuário da sala, envia uma mensagem de que a sala foi fechada
        for(Map.Entry<String, IUserChat> entry : userList.entrySet()) {
            try {
                entry.getValue().deliverMsg("Server", "Room was closed.");
            } catch (Exception exception) {
                System.out.println("RoomChat error: " + exception.getMessage());
                exception.printStackTrace();
            }
        }
        // Fecha a sala
        isOpen = false;
    }


    // RFA11: O controlador da sala (sala) é quem deve controlar o envio das mensagens aos membros da sala
    public void sendMsg(String usrName, String msg) throws RemoteException {
        // Em caso do comando para sair
        if(msg.equals("/quit")) {
            leaveRoom(usrName);
        } else {
            if(isOpen) {
                // Para cada usuário da sala, envia a mensagem acompanhada do usrName
                for(Map.Entry<String, IUserChat> entry : userList.entrySet()) {
                    try {
                        entry.getValue().deliverMsg(usrName, msg);
                    } catch (Exception exception) {
                        System.out.println("RoomChat error: " + exception.getMessage());
                        exception.printStackTrace();
                    }
                }
            }
        }
    }

}