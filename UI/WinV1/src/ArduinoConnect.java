import com.fazecast.jSerialComm.SerialPort;

import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class ArduinoConnect {
SerialPort sp;
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
        for(int i=0;i< cbuf.length;i++) {
            sp.getOutputStream().write(cbuf[i]);
        }
        sp.getOutputStream().flush();
        System.out.println("Je viens d'envoyer :" + cbuf);
        Thread.sleep(1000);
        //Fermeture du port
        if (sp.closePort()){
            System.out.println("Port refermé !");
        } else {
            System.out.println("Port toujours ouvert ...");
        }
    }
}
