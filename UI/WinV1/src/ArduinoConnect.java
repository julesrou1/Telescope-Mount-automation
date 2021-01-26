import com.fazecast.jSerialComm.SerialPort;

import java.io.IOException;
import java.nio.charset.StandardCharsets;

public class ArduinoConnect {
SerialPort sp;
    public ArduinoConnect(String port){
        sp = SerialPort.getCommPort(port);
        sp.setComPortParameters(9600, 8, 1, 0);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING,0,0);
        if (sp.openPort()){
            System.out.println("Port ouvert !");
        } else {
            System.out.println("Port fermé...");
        }
    }
    public void ArduinoSend() throws IOException, InterruptedException {
        for (Integer I=0;I<5;I++) {
            sp.getOutputStream().write(I.byteValue());
            sp.getOutputStream().flush();
            System.out.println("Je viens d'envoyer :" + I);
            Thread.sleep(1000);
        }
    }

    public void ArdDC(){
        if (sp.closePort()){
            System.out.println("Port refermé !");
        } else {
            System.out.println("Port toujours ouvert ...");
        }
    }
}
