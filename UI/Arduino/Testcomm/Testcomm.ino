#include <SoftwareSerial.h>
#include <TimerThree.h>

SoftwareSerial sserial(22,24); //j'ai branché le tx de mon usb-TTL sur le port Rx1=22 , surement remplaceable avec Serial1.write()/Serial1.read ----> OUI
char buf[5];
int i=0;
int led=31;


void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  sserial.begin(9600);
  Serial1.begin(9600);
  Serial.begin(9600);
  Timer3.initialize(100);
  Timer3.attachInterrupt(readData);
//  while(!Serial){
//    ;
//  }
  
}

void loop() {

  // put your main code here, to run repeatedly:
//if (Serial1.available() >0){
//  String incomingString = Serial1.readString();
//    //if (incomingString != -1){
//      Serial.print("J'ai reçu : ");
//      Serial.println(incomingString);
//    //}
//  }

}
//
//void SerialEvent1(){
  //digitalWrite(led,HIGH);
  //delay(1000);
  //digitalWrite(led,LOW);
//    while(Serial1.available()){
//      byte incomingByte = Serial1.read();
//      if (incomingByte != -1){
//        buf[i]=incomingByte;
//        i=i+1;
        //Serial.print("J'ai reçu : ");
        //Serial.println(incomingByte);
      
//}

void readData(){
if (Serial1.available()>0){
  byte incomingString = Serial1.read();
    Serial.print("J'ai reçu : ");
    Serial.println(incomingString);
    digitalWrite(led,HIGH);
    delay(1000);
//  if(i%2==1){
//    digitalWrite(led,HIGH);
//    i=i+1;
//}
  
}else{
    digitalWrite(led,LOW);
//    i=i+1;
  }

}
