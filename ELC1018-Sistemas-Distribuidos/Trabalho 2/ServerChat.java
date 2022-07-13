import java.util.*;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.LocateRegistry;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ServerChat extends UnicastRemoteObject implements IServerChat {
    
    // RFA1: O servidor central deve manter uma lista de salas (roomList).
    // A lista de salas deve declarada como private ArrayList<String> roomList.
    // RFA3: No servidor central, não deve haver limite de salas, tampouco de usuários por sala.
    private ArrayList<String> roomList;
    
    /* GUI STUFF */
    //buttons
    private JFrame frame;
    private JButton closeButton;
    private JLabel availableLabel;
    private JList<String> availableList;
    private DefaultListModel<String> availableListModel;
    private JScrollPane listScroller;
    

    public ServerChat() throws RemoteException {
        super();

        roomList = new ArrayList<String>();

        frame = new JFrame();        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setTitle("Server");
        serverGUI(frame.getContentPane());
        frame.pack();
        frame.setVisible(true);
    }


    public void serverGUI(Container pane) {
        pane.setLayout(new GridBagLayout());
        GridBagConstraints constraint = new GridBagConstraints();

        availableListModel = new DefaultListModel<String>();

        availableList = new JList<String>(availableListModel);
        availableList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        availableList.setLayoutOrientation(JList.VERTICAL);
        availableList.setVisibleRowCount(-1);

        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridwidth = 3;
        constraint.gridx = 0;
        constraint.gridy = 0;
        pane.add(availableList, constraint);

        listScroller = new JScrollPane(availableList);
        listScroller.setPreferredSize(new Dimension(250, 100));

        pane.add(listScroller);


        //RFA13: Uma sala só deve poder ser fechada pelo servidor. O servidor deve fechar a sala invocando o método remoto closeRoom() do controlador de sala. 
        // Caso haja usuários na sala, antes de ser finalizado o controlador da sala deve enviar uma mensagem "Sala fechada pelo servidor." aos usuários.
        closeButton = new JButton("Close");
        closeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                java.util.List<String> string = availableList.getSelectedValuesList();
                for(String s : string) {
                    try {
                        IRoomChat roomObj = (IRoomChat) Naming.lookup("//localhost:2020/Rooms/" + s);
                        // RFA14: Após fechar a sala o servidor deve eliminar a sala da lista de salas. 
                        // Cada usuário deve fazer o mesmo ao receber a mensagem "Sala fechada pelo servidor." do controlador.
                        roomList.remove(s);
                        availableListModel.removeElement(s);

                        roomObj.closeRoom();
                        availableLabel.setText("Available rooms: " + roomList.size());
                        Naming.unbind("//localhost:2020/Rooms/" + s);
                        
                        
                    } catch (Exception exception) {
                        System.out.println("ServerChat error: " + exception.getMessage());
                        exception.printStackTrace();
                    }
                }
            }
        });

        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 0;
        constraint.gridy = 1;
        pane.add(closeButton, constraint);

        availableLabel = new JLabel();
        availableLabel.setText("Available rooms: " + roomList.size());
        availableLabel.setVerticalTextPosition(JLabel.BOTTOM);
        availableLabel.setHorizontalTextPosition(JLabel.CENTER);

        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 0;
        constraint.gridy = 2;
        pane.add(availableLabel, constraint);
    }

    public ArrayList<String> getRooms() throws RemoteException {
        return roomList;
    }


    public void createRoom(String roomName) throws RemoteException {
        try {
            RoomChat obj = new RoomChat(roomName);
            roomList.add(roomName);
            Naming.rebind("//localhost:2020/Rooms/" + roomName, obj);
            System.out.println("The room " + roomName + " was created.");

            availableListModel.addElement(roomName);
            availableLabel.setText("Available rooms: " + roomList.size());
        } catch (Exception exception) {
            System.out.println("ServerChat error: " + exception.getMessage());
            exception.printStackTrace();
        }
    }

    public static void main(String args[]) {
        try {
            //RFA16: O servidor deve ser registrado no registro de RMI (rmiregistry) com o nome "Servidor" e usar a porta "2020" para escutar clientes. 
            // O registro deve executar na máquina do servidor.
            ServerChat serverObj = new ServerChat();
            LocateRegistry.createRegistry(2020).rebind("Servidor", serverObj);
        }
        catch (Exception exception) {
            System.out.println("ServerChat error: " + exception.getMessage());
            exception.printStackTrace();
        }
    }
}