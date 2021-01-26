#include <SoftwareSerial.h>

SoftwareSerial sserial(19,18); //j'ai branché le tx de mon usb-TTL sur le port Rx1=19 , surement remplaceable avec Serial1.write()/Serial1.read ----> OUI

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial1.available() >0){
  byte incomingByte = Serial1.read();
    if (incomingByte != -1){
      Serial.print("J'ai reçu : ");
      Serial.println(incomingByte);
    }
  }

}
//
//void SerialEvent1(){
//    byte incomingByte = Serial1.read();
//    if (incomingByte != -1){
//      Serial.print("J'ai reçu : ");
//      Serial.println(incomingByte);
//    }
//}
