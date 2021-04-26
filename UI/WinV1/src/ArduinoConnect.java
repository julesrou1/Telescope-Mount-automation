import com.fazecast.jSerialComm.SerialPort;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class ArduinoConnect {
SerialPort sp;
//Data data;
    public ArduinoConnect(String port,Data coords,String m) throws IOException, InterruptedException {
       //Ouverture du port
        //char[] cbuf=buf.toCharArray();

        coords.setMode(m);

        String buf=coords.mode+coords.ra+coords.dec+coords.time;
        char[] cbuf=buf.toCharArray();

        sp = SerialPort.getCommPort(port);
        sp.setComPortParameters(9600, 8, 1, 0);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING,0,0);
        if (sp.openPort()){
            System.out.println("Port ouvert !");
        } else {
            System.out.println("Port fermé...");
        }
        //Envoi des données
        for (char c : cbuf) {
            sp.getOutputStream().write(c);
        }
        sp.getOutputStream().flush();
        System.out.println("Je viens d'envoyer :" + Arrays.toString(cbuf));
        Thread.sleep(0,1);
        //Fermeture du port
        if (sp.closePort()){
            System.out.println("Port refermé !");
        } else {
            System.out.println("Port toujours ouvert ...");
        }
    }

    public ArduinoConnect(String port, String coords, String m) throws IOException,InterruptedException{

        String buf=m+coords;
        char[] cbuf=buf.toCharArray();

        sp = SerialPort.getCommPort(port);
        sp.setComPortParameters(9600, 8, 1, 0);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING,0,0);
        if (sp.openPort()){
            System.out.println("Port ouvert !");
        } else {
            System.out.println("Port fermé...");
        }
        //Envoi des données
        for (char c : cbuf) {
            sp.getOutputStream().write(c);
        }
        sp.getOutputStream().flush();
        System.out.println("Je viens d'envoyer :" + Arrays.toString(cbuf));
        Thread.sleep(0,1);
        //Fermeture du port
        if (sp.closePort()){
            System.out.println("Port refermé !");
        } else {
            System.out.println("Port toujours ouvert ...");
        }
    }
}
