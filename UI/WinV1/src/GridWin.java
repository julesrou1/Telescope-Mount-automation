import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.fazecast.jSerialComm.*;

public class GridWin extends JFrame implements ActionListener {
    protected JTextField textField;
    static SerialPort chosenPort;

    public GridWin(String titre, int x, int y){
        super(titre);
        this.setLocation(400,200);
        this.setSize(x,y);
        this.setLayout(new BorderLayout());
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        /*Création du panel port*/
        //Container pan=getContentPane();
        JPanel portPanel=new JPanel();
        JLabel port = new JLabel("Port :");
        JLabel conn = new JLabel("Non connecté");
        JComboBox<String> portList = new JComboBox<String>();
        JButton connectButton = new JButton("Connecter");
        connectButton.addActionListener(this);
        portPanel.add(port);
        portPanel.add(portList);
        portPanel.add(connectButton);
        portPanel.add(conn);
        this.add(portPanel,BorderLayout.NORTH);

        /*remplissage de la liste des ports*/
        SerialPort[] portNames = SerialPort.getCommPorts();
        for (int i=0;i<portNames.length;i++){
            portList.addItem(portNames[i].getSystemPortName());
        }
        /*Création du panel text*/
        JPanel textPanel=new JPanel();
        JButton searchButton=new JButton("Rechercher");
        textField=new JTextField(20);
        textField.addActionListener(this);
        textPanel.add(textField);
        textPanel.add(searchButton);
        this.add(textPanel,BorderLayout.CENTER);


        /* rend la fenêtre visible*/
        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String cmd = e.getActionCommand();
        switch(cmd){
            //case "Connecter" : chosenPort = SerialPort.getCommPort(portList)
        }


    }
}
