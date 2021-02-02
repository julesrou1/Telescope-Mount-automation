#include <SoftwareSerial.h>
#include <TimerThree.h>

SoftwareSerial sserial(22,24); //j'ai branché le tx de mon usb-TTL sur le port Rx1=22 , surement remplaceable avec Serial1.write()/Serial1.read ----> OUI
char buf[64];
int i=0;
int led=31;


void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  sserial.begin(9600);
  Serial1.begin(9600);
  Serial.begin(9600);
  Timer3.initialize(100);
//  Timer3.attachInterrupt(readData);
//  while(!Serial){
//    ;
//  }
  
}

void loop() {
// put your main code here, to run repeatedly:

  while(Serial1.available()>0){
    byte incomingByte = Serial1.read();
    char x1=(char) incomingByte;
    
      if (incomingByte!=-1){
        buf[i]=x1;
        Serial.print("J'ai reçu : ");
        Serial.println(incomingByte);
        Serial.print("qui se convertit :");
        Serial.println(x1);
        Serial.println(i);
        Serial.println(buf);
        Serial.print("\n");
        i=i+1;
    }
  }
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

//void readData(){
//while(Serial1.available()>0){
//  
//  byte incomingString = Serial1.read();
//  char x1=(char) incomingString;
//    buf[i]=x1;
//    Serial.print("J'ai reçu : ");
//    Serial.println(incomingString);
//    Serial.print("qui se convertit :");
//    Serial.println(x1);
//    Serial.println(i);
//    Serial.println(buf);
//    Serial.print("\n");
//    i=i+1;
//    //digitalWrite(led,HIGH);
////  if(i%2==1){
////    digitalWrite(led,HIGH);
////    i=i+1;
////}
//  
////}else{
//    //digitalWrite(led,LOW);
////    i=i+1;
//  }
//i=0;
//}

static byte c1;
// Convert a single Character from UTF8 to Extended ASCII
// Return "0" if a byte has to be ignored
byte utf8ascii(byte ascii) {
    if ( ascii<128 )   // Standard ASCII-set 0..0x7F handling  
    {   c1=0;
        return( ascii );
    }

    // get previous input
    byte last = c1;   // get last char
    c1=ascii;         // remember actual character

    switch (last)     // conversion depending on first UTF8-character
    {   case 0xC2: return  (ascii);  break;
        case 0xC3: return  (ascii | 0xC0);  break;
        case 0x82: if(ascii==0xAC) return(0x80);       // special case Euro-symbol
    }

    return  (0);                                     // otherwise: return zero, if character has to be ignored
}
