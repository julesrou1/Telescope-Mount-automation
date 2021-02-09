#include <Arduino.h>
#include "functions.h"

int RArotation=1;
int mapX = 0;
int mapY = 0;
int swstate=0;
int fill=0;

struct Motor M1;
struct Motor M2;
struct Motor M3;
struct MsgReceived msg;

struct Date date;

void tim1(){
  if(swstate==2){
    cstRotate(&M1,1);
  }
  if(swstate==1){//Joystick control
    digitalWrite(pinLED,HIGH);
    mapX = map(analogRead(VRx), 0, 1023, -512, 512);
    mapY = map(analogRead(VRy), 0, 1023, -512, 512);
    if(mapX>100){
      rotate(1,&M1,1,'F');
    }
    if(mapX<-100){
      rotate(1,&M1,-1,'F');
    }
    if(mapY>100){
      rotate(1,&M2,1,'F');
    }
    if(mapY<-100){
      rotate(1,&M2,-1,'F');
    }
  } 
  if(swstate==0){digitalWrite(pinLED,LOW);}
  if(swstate==0 && msg.newinstruction==1){
    if (msg.mode == "01"){
      Serial.println(msg.RARelatif);
      Serial.println(msg.DARelatif);
    }
  }
 }
void tim4(){//Tracking de la position du moteur lors du suivie
  //TODO FIX
  if (fill==1){
  if(M1.cst==1){M1.EquatorialPosition+=(0.417828/2);// si le moteur tourne on ajoute l'angle //! Probleme de logique a revoir ici
  }else{M1.EquatorialPosition-=(0.417828/2);}// si il ne tourne pas sont angle diminue //! melange de la position eq et de la possition relatif a la monture
  }
}

void swactivation(){
  swstate=(swstate+1)%3;
}
void setup() {
  Serial.begin(9600); 
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(pinLED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(swPin), swactivation, LOW);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(tim1);
  Timer4.initialize(1000000);
	Timer4.attachInterrupt(tim4);
// Sets the two pins as Outputs
  pinMode(M1stepPin,OUTPUT); 
  pinMode(M1dirPin,OUTPUT);
  pinMode(M1ms1pin,OUTPUT);
  pinMode(M1ms2pin,OUTPUT);
  pinMode(M1ms3pin,OUTPUT);

  pinMode(M2stepPin,OUTPUT); 
  pinMode(M2dirPin,OUTPUT);
  pinMode(M2ms1pin,OUTPUT);
  pinMode(M2ms2pin,OUTPUT);
  pinMode(M2ms3pin,OUTPUT);
// Control for switch
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);

  digitalWrite(outPin,HIGH);
  digitalWrite(M2dirPin,HIGH);
  digitalWrite(M1dirPin,HIGH);
 //microstep resolution to 1/16
  digitalWrite(M1ms1pin,HIGH);
  digitalWrite(M1ms2pin,HIGH);
  digitalWrite(M1ms3pin,HIGH);
  //microstep resolution to 1/16
  digitalWrite(M2ms1pin,HIGH);
  digitalWrite(M2ms2pin,HIGH);
  digitalWrite(M2ms3pin,HIGH);
}

void loop() {
  if(fill!=1){fill=MotorStructFiller(&M1,&M2,&M3);}
  read(&msg,&date);
}
