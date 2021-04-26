import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.PrintWriter;

import com.fazecast.jSerialComm.*;

public class GridWin extends JFrame implements ActionListener {

    protected JTextField textField;
    static SerialPort chosenPort;
    protected String cport;
    protected JComboBox<String> portList;
    protected JButton connectButton;
    protected JLabel port;
    protected JLabel conn;
    protected  JLabel id;
    protected  JLabel coor;
    protected JButton searchButton;
    protected JButton sendButton;
    protected JTextField testField;

    @Override
    public void actionPerformed(ActionEvent a) {
        String cmd = a.getActionCommand();
        switch (cmd)
        {
            case "Verrouiller" : //Séléction du port d'envoi
               //chosenPort = SerialPort.getCommPort(portList.getSelectedItem().toString());
                cport=portList.getSelectedItem().toString();
                //chosenPort.setComPortParameters(9600, 8,1,0);
                //chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0); inclus dans la classe ArduinoConnect
                System.out.println("Port choisi !");
                connectButton.setText("Déverrouiller");
                conn.setText("Port séléctionné");
                portList.setEnabled(false);

                break;
            case "Déverrouiller" :
                // Désélectionne le port
                //chosenPort.closePort();
                portList.setEnabled(true);
                connectButton.setText("Verrouiller");
                conn.setText("Port non sélectionné");
                break;
            case "Rechercher" :
                //Récupération de l'id + recherche dans la bdd + ouverture du port + envoi à la arduino du buffer + fermeture du port
                String id = textField.getText();
                System.out.println(id);// ptits test despi
                Data data=new Data(id,"D:\\Cours\\2A\\Projet2A\\Telescope-Mount-automation\\Database\\data2.db");
                data.printData();
                try {
                    ArduinoConnect con = new ArduinoConnect(cport,data,"01");
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                textField.setText("");
                break;
            case "Envoyer" :
            // envoi des coordonnées à la carte
            String coor=testField.getText();
            System.out.println(coor);
            try{
                ArduinoConnect con = new ArduinoConnect(cport,coor,"00;");
            } catch (IOException e){
                e.printStackTrace();
            } catch (InterruptedException e){
                e.printStackTrace();
            }
            testField.setText("");
            break;

        }
    }

    public GridWin(String titre, int x, int y) {
        super(titre);
        this.setLocation(400, 200);
        this.setSize(x, y);
        this.setLayout(new BorderLayout());
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        /*Création du panel port*/
        //Container pan=getContentPane();
        JPanel portPanel = new JPanel();
        port = new JLabel("Port :");
        conn = new JLabel("Port non sélectionné");
        portList = new JComboBox<String>();
        connectButton = new JButton("Verrouiller");
        connectButton.addActionListener(this);
        portPanel.add(port);
        portPanel.add(portList);
        portPanel.add(connectButton);
        portPanel.add(conn);
        this.add(portPanel, BorderLayout.NORTH);

        /*remplissage de la liste des ports*/
        SerialPort[] portNames = SerialPort.getCommPorts();
        for (int i = 0; i < portNames.length; i++) {
            portList.addItem(portNames[i].getSystemPortName());
        }
        /*Création du panel text*/

        JPanel textPanel = new JPanel();
        searchButton = new JButton("Rechercher");
        searchButton.addActionListener(this);
        textField = new JTextField(20);
        textField.addActionListener(this);
        id=new JLabel("id de l'objet à viser:");
        coor=new JLabel("Long;Lat;Alt");
        textPanel.add(id);
        textPanel.add(textField);
        textPanel.add(searchButton);
        sendButton = new JButton("Envoyer");
        sendButton.addActionListener(this);
        testField=new JTextField(20);
        testField.addActionListener(this);
        textPanel.add(coor);
        textPanel.add(testField);
        textPanel.add(sendButton);
        this.add(textPanel, BorderLayout.CENTER);



/*        *//* Configuration du bouton de connexion *//*
        connectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                if (connectButton.getText().equals("Connect")) {
                    //essai de connexion au port
                    chosenPort = SerialPort.getCommPort(portList.getSelectedItem().toString());
                    chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
                    if (chosenPort.openPort()) {
                        connectButton.setText("Déconnecter");
                        conn.setText("Connecté");
                        portList.setEnabled(false);

                        // création d'un thread pour envoyer des données à la carte.
                        Thread thread = new Thread() {
                            public void run() {
                                //attente du tmps que la carte met à reset après connection
                                try {
                                    Thread.sleep(100);
                                } catch (Exception e) {
                                }

                                PrintWriter output = new PrintWriter(chosenPort.getOutputStream());
                                //entrée dans une boucle infinie qui envoie du texte à la carte
                                while (true) {
                                    output.print("ra");
                                    output.flush();//envoie ce qu'on vient d'écrire dans le buffer
                                    output.print("dec");
                                    output.flush();
                                    try{Thread.sleep(1000);} catch (Exception e) {}
                                }
                            }
                        };
                        thread.start();
                    }
                } else {
                    // déconnection du port série
                    chosenPort.closePort();
                    portList.setEnabled(true);
                    connectButton.setText("Connecter");
                    conn.setText("Déconnecté");
                }
            }
        });*/

        /* rend la fenêtre visible*/
        this.setVisible(true);
    }
}


