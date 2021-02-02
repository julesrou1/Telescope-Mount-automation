import com.fazecast.jSerialComm.SerialPort;

import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class ArduinoConnect {
SerialPort sp;
//Data data;
    public ArduinoConnect(String port,String buf) throws IOException, InterruptedException {
       //Ouverture du port
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
        System.out.println("Je viens d'envoyer :" + cbuf.toString());
        Thread.sleep(1);
        //Fermeture du port
        if (sp.closePort()){
            System.out.println("Port refermé !");
        } else {
            System.out.println("Port toujours ouvert ...");
        }
    }
}
