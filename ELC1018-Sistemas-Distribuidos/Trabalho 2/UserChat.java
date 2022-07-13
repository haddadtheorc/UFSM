import java.util.*;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;

public class UserChat extends UnicastRemoteObject implements IUserChat{
    
    /* USER_CHAT STUFF */
    String usrName; 
    String roomName; 
    IRoomChat room; 
    ArrayList<String> rooms;

    /* GUI STUFF */
    //buttons
    private JButton buttonSend;
    private JButton buttonRefresh;
    private JButton buttonConnect;
    private JButton buttonLeave;
    private JButton buttonCreateRoom;

    private JFrame frame;
    private JList<String> chatList;
    private JList<String> roomList;
    private DefaultListModel<String> chatListModel;
    private DefaultListModel<String> roomListModel;
    private JScrollPane chatListScroller;
    private JScrollPane roomListScroller;
    private JTextField chatTextField;


    public UserChat() throws RemoteException {
        super();
        frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setTitle("Client");
        userGUI(frame.getContentPane(), this);
        frame.pack();
        frame.setVisible(true);
    }


    public void userGUI(Container pane, UserChat user) {
        
        pane.setLayout(new GridBagLayout());
        GridBagConstraints constraint = new GridBagConstraints();

        chatListModel = new DefaultListModel<String>();
        chatList = new JList<String>(chatListModel);
        chatList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        chatList.setLayoutOrientation(JList.VERTICAL);
        chatList.setVisibleRowCount(-1);
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridwidth = 2;
        constraint.gridheight = 3;
        constraint.gridx = 0;
        constraint.gridy = 0;
        pane.add(chatList);

        chatListScroller = new JScrollPane(chatList);
        chatListScroller.setPreferredSize(new Dimension(250, 250));

        pane.add(chatListScroller);

        //RFA9: Após pertencer a uma sala, o usuário deve enviar mensagens de texto à sala através da invocação ao método remoto sendMsg(String usrName, String msg) da sala.
        // tecla enter
        chatTextField = new JTextField(20);
        chatTextField.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    if(room != null)
                    {
                        room.sendMsg(usrName, chatTextField.getText());
                        chatTextField.setText("");
                    }
                    else
                    {
                        deliverMsg("Server","You are not currently in a room!");
                    }
                } catch (Exception exception) {
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }
        });
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridwidth = 1;
        constraint.gridx = 0;
        constraint.gridy = 5;
        pane.add(chatTextField, constraint);

        //roomList
        roomListModel = new DefaultListModel<String>();
        roomList = new JList<String>(roomListModel);
        roomList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        roomList.setLayoutOrientation(JList.VERTICAL);
        roomList.setVisibleRowCount(-1);
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridwidth = 1;
        constraint.gridheight = 2;
        constraint.gridx = 3;
        constraint.gridy = 0;
        pane.add(roomList, constraint);
        roomListScroller = new JScrollPane(roomList);
        roomListScroller.setPreferredSize(new Dimension(125, 250));
        pane.add(roomListScroller, constraint);


        //RFA9: Após pertencer a uma sala, o usuário deve enviar mensagens de texto à sala através da invocação ao método remoto sendMsg(String usrName, String msg) da sala.
        // botão send
        buttonSend = new JButton("Send");
        buttonSend.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    // Invocar o método remoto sendMsg(String usrName, String msg) da sala.
                    if(room != null)
                    {
                        room.sendMsg(usrName, chatTextField.getText());
                        chatTextField.setText("");
                    }
                    else
                    {
                        deliverMsg("Server","You are not currently in a room!");
                    }
                } catch (Exception exception) {
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }
        });
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 2;
        constraint.gridy = 5;
        pane.add(buttonSend, constraint);


        //button for creating new rooms
        buttonCreateRoom = new JButton("Create Room");
        buttonCreateRoom.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                try{
                    IServerChat serverObj = (IServerChat) Naming.lookup("//localhost:2020/Servidor");
                    user.roomName = JOptionPane.showInputDialog(null, "Type your desired room:", "Client", JOptionPane.INFORMATION_MESSAGE);

                    boolean existingRoom = false;
                        for(String room : user.rooms) {
                            if(room.equals(user.roomName)) {
                                existingRoom = true;
                            }
                        }
                    
                        //if room already exists
                        if(existingRoom){
                            int response = JOptionPane.showConfirmDialog(null, user.roomName + " already exists. Do you wish to join this room?",  
                            "Client", JOptionPane.YES_NO_OPTION);
                            if(response == JOptionPane.YES_OPTION){
                                // if already in a room, leaves
                                if(room != null){
                                    try {
                                        if(roomName != null && room != null) {
                                            // Invocar o método remoto leaveRoom(String usrName) da sala.
                                            room.leaveRoom(usrName);
                                            room = null;
                                        }
                                    } catch (Exception exception) {
                                        System.out.println("UserChat error: " + exception.getMessage());
                                        exception.printStackTrace();
                                    }
                                }
                                //join room
                                user.room = (IRoomChat) Naming.lookup("//localhost:2020/Rooms/" + user.roomName);
                                user.room.joinRoom(user.usrName, user);
                                user.frame.setTitle("Client: " + user.usrName + " [Room: " + user.room.getRoomName() + "]");
                                //refresh
                                try {
                                    // Invocar o método remoto getRooms() do servidor.
                                    rooms = serverObj.getRooms();
                                    roomListModel.removeAllElements();
                                    for(String r : rooms) {
                                        roomListModel.addElement(r);
                                    }
                
                                } catch (Exception exception) {
                                    System.out.println("UserChat error: " + exception.getMessage());
                                    exception.printStackTrace();
                                }
                            }
                        }
                        
                        // creates a new room
                        else{
                            // if already in a room, leaves
                            if(room != null){
                                try {
                                    if(roomName != null && room != null) {
                                        // Invocar o método remoto leaveRoom(String usrName) da sala.
                                        room.leaveRoom(usrName);
                                        room = null;
                                    }
                                } catch (Exception exception) {
                                    System.out.println("UserChat error: " + exception.getMessage());
                                    exception.printStackTrace();
                                }
                            }
                            //creates room
                            serverObj.createRoom(user.roomName);
                            user.room = (IRoomChat) Naming.lookup("//localhost:2020/Rooms/" + user.roomName);
                            //join room
                            user.room.joinRoom(user.usrName, user);  
                            user.frame.setTitle("Client: " + user.usrName + " [Room: " + user.room.getRoomName() + "]");
                            //refresh
                            try {
                                // Invocar o método remoto getRooms() do servidor.
                                rooms = serverObj.getRooms();
                                roomListModel.removeAllElements();
                                for(String r : rooms) {
                                    roomListModel.addElement(r);
                                }
            
                            } catch (Exception exception) {
                                System.out.println("UserChat error: " + exception.getMessage());
                                exception.printStackTrace();
                            }   
                        }

                } catch (Exception exception){
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }
        });
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 3;
        constraint.gridy = 2;
        pane.add(buttonCreateRoom, constraint);

        
        buttonRefresh = new JButton("Refresh");
        buttonRefresh.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    IServerChat serverObj = (IServerChat) Naming.lookup("//localhost:2020/Servidor");
                    // Invocar o método remoto getRooms() do servidor.
                    rooms = serverObj.getRooms();
                    roomListModel.removeAllElements();
                    for(String r : rooms) {
                        roomListModel.addElement(r);
                    }

                } catch (Exception exception) {
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }
        });
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 3;
        constraint.gridy = 4;
        pane.add(buttonRefresh, constraint);


        buttonConnect = new JButton("Join");
        buttonConnect.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    if(room != null){
                        try {
                            if(roomName != null && room != null) {
                                // Invocar o método remoto leaveRoom(String usrName) da sala.
                                room.leaveRoom(usrName);
                                room = null;
                                roomName = null;
                            }
                        } catch (Exception exception) {
                            System.out.println("UserChat error: " + exception.getMessage());
                            exception.printStackTrace();
                        }
                    }

                    roomName = roomList.getSelectedValue();

                    if(roomName != null) {
                        user.room = (IRoomChat) Naming.lookup("//localhost:2020/Rooms/" + user.roomName);
                        // Invocar o método remoto joinRoom(String usrName) do servidor.
                        room.joinRoom(usrName, user);
                        roomName = null;
                    }
                    user.frame.setTitle("Client: " + user.usrName + " [Room: " + user.room.getRoomName() + "]");   

                } catch (Exception exception) {
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }
        });
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 3;
        constraint.gridy = 6;
        pane.add(buttonConnect, constraint);


        // RFA12: Os usuários devem sair da sala invocando o método remoto leaveRoom(String usrName) da sala.
        buttonLeave = new JButton("Leave");
        buttonLeave.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    if(roomName != null && room != null) {
                        // Invocar o método remoto leaveRoom(String usrName) da sala.
                        room.leaveRoom(usrName);
                        room = null;
                        roomName = null;
                        user.frame.setTitle("Client: " + user.usrName);
                    }
                } catch (Exception exception) {
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }
        });
        constraint.fill = GridBagConstraints.HORIZONTAL;
        constraint.gridx = 3;
        constraint.gridy = 8;
        pane.add(buttonLeave, constraint);
    }

    // RFA10: Para receber mensagens, o processo do usuário deve implementar um método remoto deliverMsg(String senderName, String msg).
    public void deliverMsg(String senderName, String msg) throws RemoteException {
        // Exibir a mensagem recebida na lista de mensagens.
        chatListModel.addElement("[" + senderName + "]: " + msg);

        // RFA14: Após fechar a sala o servidor deve eliminar a sala da lista de salas. 
        // Cada usuário deve fazer o mesmo ao receber a mensagem "Sala fechada pelo servidor." do controlador.
        if(msg.contains("Room was closed.")){
            // Refresh da lista de salas
            try {
                IServerChat serverObj = (IServerChat) Naming.lookup("//localhost:2020/Servidor");
                // Invocar o método remoto getRooms() do servidor.
                rooms = serverObj.getRooms();
                roomListModel.removeAllElements();
                for(String r : rooms) {
                    roomListModel.addElement(r);
                }

            } catch (Exception exception) {
                System.out.println("UserChat error: " + exception.getMessage());
                exception.printStackTrace();
            }
        }

        
    }


    public static void main(String[] args) throws RemoteException {
        try {
            
            // RFA4: No início, todo cliente, identificado pelo seu nome (usrName).
            UserChat user = new UserChat(); 
            user.usrName = JOptionPane.showInputDialog(null, "Type your name:", "Client", JOptionPane.INFORMATION_MESSAGE);
            user.frame.setTitle("Client: " + user.usrName);
            
            //, deve contatar o servidor e solicitar a lista de salas roomList.
            IServerChat serverObj = (IServerChat) Naming.lookup("//localhost:2020/Servidor");  

            // RFA5: A solicitação da lista de salas deve ser realizada através da invocação ao método remoto getRooms()da lista de salas roomList.
            user.rooms = serverObj.getRooms();

            // RFA6: A lista de salas deve ser exibida na interface do usuário (GUI), para permitir a escolha da sala.
            for(String r : user.rooms) {
                user.roomListModel.addElement(r);
            }

            // Selecionar uma sala para entrar.
            user.roomName = JOptionPane.showInputDialog(null, "Type your desired room:", "Client", JOptionPane.INFORMATION_MESSAGE);
            user.room = null;
            boolean existingRoom = false;
            for(String room : user.rooms) {
                if(room.equals(user.roomName)) {
                    existingRoom = true;
                }
            }


            if(user.roomName != null){

                // RFA7: Sempre que um usuário desejar entrar numa sala já existente ele deve solicitar a referência ao objeto remoto ao RMI Registry usando o nome da sala
                // Após conhecer o objeto, deve invocar o método remoto joinRoom(String usrName) da respectiva sala.
                if(existingRoom){
                    user.room = (IRoomChat) Naming.lookup("//localhost:2020/Rooms/" + user.roomName);
                    user.room.joinRoom(user.usrName, user);
                    user.frame.setTitle("Client: " + user.usrName + " [Room: " + user.room.getRoomName() + "]");
                }
                // RFA8: Caso o usuário não encontre no servidor a sala desejada ele deve poder solicitar a criação de uma nova sala. 
                // Isto deve ser feito através da invocação ao método remoto criateRoom(String roomName) do servidor. 
                // A vinculação do usuário a esta sala não deve ser automática. Ele deve solicitar a entrada invocando o método remoto joinRoom() da sala.
                else{
                    int response = JOptionPane.showConfirmDialog(null, user.roomName + " does not exist. Do you wish to create this room?",  
                    "Client", JOptionPane.YES_NO_OPTION);
                    
                    if(response == JOptionPane.YES_OPTION){
                        serverObj.createRoom(user.roomName);
                        user.room = (IRoomChat) Naming.lookup("//localhost:2020/Rooms/" + user.roomName);
                        user.room.joinRoom(user.usrName, user);  
                        user.frame.setTitle("Client: " + user.usrName + " [Room: " + user.room.getRoomName() + "]");   
                    }
                }

                // Refresh da lista de salas
                try {
                    // Invocar o método remoto getRooms() do servidor.
                    user.rooms = serverObj.getRooms();
                    user.roomListModel.removeAllElements();
                    for(String room :user.rooms) {
                        user.roomListModel.addElement(room);
                    }
    
                } catch (Exception exception) {
                    System.out.println("UserChat error: " + exception.getMessage());
                    exception.printStackTrace();
                }
            }

        } catch (Exception exception) {
            System.out.println("UserChat error: " + exception.getMessage());
            exception.printStackTrace();
        }
    }
}