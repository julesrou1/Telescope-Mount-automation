import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.PrintWriter;

import com.fazecast.jSerialComm.*;

public class GridWin extends JFrame implements ActionListener {

    protected JTextField textField;
    static SerialPort chosenPort;
    protected JComboBox<String> portList;
    protected JButton connectButton;
    protected JLabel port;
    protected JLabel conn;
    protected JButton searchButton;

    @Override
    public void actionPerformed(ActionEvent a) {
        String cmd = a.getActionCommand();
        switch (cmd)
        {
            case "Verrouiller" : //Séléction du port d'envoi
                chosenPort = SerialPort.getCommPort(portList.getSelectedItem().toString());
                //chosenPort.setComPortParameters(9600, 8,1,0);
                //chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0); inclus dans la classe ArduinoConnect
                System.out.println("Port choisi !");
                connectButton.setText("Déverrouiller");
                conn.setText("Port séléctionné");
                portList.setEnabled(false);

                break;
            case "Déverrouiller" :
                // Désélectionne le port
                chosenPort.closePort();
                portList.setEnabled(true);
                connectButton.setText("Verrouiller");
                conn.setText("Port non sélectionné");
                break;
            case "Rechercher" :
                //Récupération de l'id + recherche dans la bdd + ouverture du port + envoi à la arduino du buffer + fermeture du port
                String id = textField.getText();
                System.out.println(id);// ptits test despi
                Data data=new Data(id,"C:\\Users\\Ggvg1\\Documents\\GitHub\\Telescope-Mount-automation\\Database\\data2.db");

                textField.setText("");
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
        textPanel.add(textField);
        textPanel.add(searchButton);
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


