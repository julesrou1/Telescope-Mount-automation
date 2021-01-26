import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;

import com.fazecast.jSerialComm.*;

public class PortConnect {
    public static void main(String[] args) throws IOException, InterruptedException {
        // ArduinoConnect connection = new ArduinoConnect("COM4");
        // connection au port
        // connection.ArduinoSend();
        //envoi des données
        // connection.ArdDC();
        //fermeture du port
        //Visiblement impossible de former le code en sous fonctions
        //Donc on va rester sur du bourrinage

        // A TESTER AVEC LA METHODE ARDUINOCONNECT AU LIEU DE TOUT CE BOUZIN

        SerialPort sp = SerialPort.getCommPort("COM5");
        sp.setComPortParameters(9600, 8, 1, 0);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING,0,0);
        if (sp.openPort()){
            System.out.println("Port ouvert !");
        } else {
            System.out.println("Port fermé...");
        }

/*        for (Integer I=0;I<5;I++) {
            sp.getOutputStream().write(I.byteValue());
            sp.getOutputStream().flush();
            System.out.println("Je viens d'envoyer :" + I);
            Thread.sleep(100);
        }*/
        String test="101";
        sp.getOutputStream().write(test.getBytes("ASCII"));//// Les caractères sortent en code donc on va éviter de mettre des lettres
        sp.getOutputStream().flush();
        System.out.println("Je viens d'envoyer :"+ test);
/*        OutputStream output = sp.getOutputStream();
        PrintWriter outprint = new PrintWriter(output);
        outprint.print(test);*/
        //System.out.println("Je viens d'envoyer :"+ test);
        Thread.sleep(1000);

        if (sp.closePort()){
            System.out.println("Port refermé !");
        } else {
            System.out.println("Port toujours ouvert ...");
        }
    }
}
