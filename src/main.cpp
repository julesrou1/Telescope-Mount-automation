#include <Arduino.h>
#include "functions.h"

int RArotation=1;
int mapX = 0;
int mapY = 0;
int swstate=0;
int fill=0;
char spd='F';
unsigned long lastFire = 0;
const int commonPin = 2;//TODO change mode for print screen
const int buttonPins[] = {23,25,27};//TODO change number
struct Motor M1;
struct Motor M2;
struct Motor M3;
struct MsgReceived msg;
struct Date date;
struct SemiAuto Instruction;
void tim1(){
  if(swstate==0 && msg.newinstruction==1){
    if (strcmp(msg.mode,"01")==0){
      Serial.println(msg.RARelatif);
      Serial.println(msg.DARelatif);
    }
    if(strcmp(msg.mode,"12")==0){//Calibration angle
      Instruction.RA=msg.RARelatif;
      Instruction.DA=msg.DARelatif;
    }
    if (strcmp(msg.mode,"22")==0){
      Instruction.first++;
      if (Instruction.first<=1){
        Instruction.NextRA=msg.RARelatif;
        Instruction.NextDA=msg.DARelatif;
      }
      
      Instruction.RA=Instruction.NextRA;
      Instruction.DA=Instruction.NextDA;

      Instruction.NextRA=msg.RARelatif;
      Instruction.NextDA=msg.DARelatif;
      
      Instruction.deltaRA=Instruction.NextRA-Instruction.RA;
      Instruction.deltaDA=Instruction.NextDA-Instruction.DA;
      //TODO add direction depending on result of delta.
      rotate(Instruction.deltaRA,&M1,1,'S'); //TODO actualise les valeurs
      rotate(Instruction.deltaRA,&M2,1,'S');
      Instruction.rotate=1;
    }
    msg.newinstruction=0;
  }
  if(Instruction.rotate==1 || swstate==2){
    digitalWrite(pinLED3,HIGH);
    digitalWrite(pinLED2,LOW);
    rotate(0.001125,&M2,1,'F'); //TODO Actualise la valeur afin de tournée a la bonne vitesse, verifier le moteur a tournée
    //TODO Condition to exit the function
  }
 }

void tim4(){//Tracking de la position du moteur lors du suivie
  //TODO FIX
  // if (fill==1){
  // if(M1.cst==1){M1.EquatorialPosition+=(0.417828/2);// si le moteur tourne on ajoute l'angle //! Probleme de logique a revoir ici
  // }else{M1.EquatorialPosition-=(0.417828/2);}// si il ne tourne pas sont angle diminue //! melange de la position eq et de la possition relatif a la monture
  // }
  if(swstate==0){
    digitalWrite(pinLED1,HIGH);
    digitalWrite(pinLED3,LOW);
    mapX = map(analogRead(VRx), 0, 1023, -512, 512);
    if(mapX>100){
      if(spd=='F'){rotate(0.1,&M3,1,spd);}
      else{rotate(0.01,&M1,1,spd);}
    }
    if(mapX<-100){
      if(spd=='F'){rotate(0.1,&M3,-1,spd);}
      else{rotate(0.01,&M3,-1,spd);}
    }
  }
  if(swstate==1){//Joystick control
    digitalWrite(pinLED1,LOW);
    digitalWrite(pinLED2,HIGH);
    mapX = map(analogRead(VRx), 0, 1023, -512, 512);
    mapY = map(analogRead(VRy), 0, 1023, -512, 512);
    if(mapX>100){
      if(spd=='F'){rotate(0.1,&M1,1,spd);}
      else{rotate(0.01,&M1,1,spd);}
    }
    if(mapX<-100){
      if(spd=='F'){rotate(0.1,&M1,-1,spd);}
      else{rotate(0.01,&M1,-1,spd);}
    }
    if(mapY>100){
      if(spd=='F'){rotate(0.1,&M2,1,spd);}
      else{rotate(0.01,&M2,1,spd);}
    }
    if(mapY<-100){
      if(spd=='F'){rotate(0.1,&M2,-1,spd);}
      else{rotate(0.01,&M2,-1,spd);}
    }
  } 
}

void configureCommon() {
  pinMode(commonPin, INPUT_PULLUP);

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], OUTPUT);
    digitalWrite(buttonPins[i], LOW);
  }
}

void configureDistinct() {
  pinMode(commonPin, OUTPUT);
  digitalWrite(commonPin, LOW);

  for (int i = 0; i <3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void press(int button) { // Our handler
//TODO add code for each button
  if (button==0){
    swstate=(swstate+1)%3;
    digitalWrite(pinLED3,LOW);
  }
  if (button==1){
    if(swstate==1||swstate==0){spd='S';}
    digitalWrite(pinLED2,LOW);
  }
  if (button==2){
    Instruction.rotate=0;
    if(swstate==1||swstate==0){spd='F';}
    digitalWrite(pinLED2,LOW);
  } 
}

void pressInterrupt() { // ISR
  if (millis() - lastFire < 200) { // Debounce
    return;
  }//check if over interup cut the reading
  lastFire = millis();

  configureDistinct(); // Setup pins for testing individual buttons

  for (int i = 0; i < 3 ; i++) { // Test each button for press
    if (!digitalRead(buttonPins[i])) {
      press(i);
    }
  }
  configureCommon(); // Return to original state
}


void setup() {
  Serial.begin(9600); 
  //display.begin();
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(pinLED1,OUTPUT);
  pinMode(pinLED2,OUTPUT);
  pinMode(pinLED3,OUTPUT);
  pinMode(commonPin, INPUT_PULLUP);
  configureCommon(); // Setup pins for interrupt
  attachInterrupt(digitalPinToInterrupt(commonPin), pressInterrupt, FALLING);

  Timer1.initialize(268978);
  Timer1.attachInterrupt(tim1);
  Timer4.initialize(10000);
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

  pinMode(M3stepPin,OUTPUT); 
  pinMode(M3dirPin,OUTPUT);
  pinMode(M3ms1pin,OUTPUT);
  pinMode(M3ms2pin,OUTPUT);
  pinMode(M3ms3pin,OUTPUT);
// Control for switch
// Control for switch

  digitalWrite(M2dirPin,HIGH);
  digitalWrite(M1dirPin,HIGH);
  digitalWrite(M3dirPin,HIGH);
 //microstep resolution to 1/16
  digitalWrite(M1ms1pin,HIGH);
  digitalWrite(M1ms2pin,HIGH);
  digitalWrite(M1ms3pin,HIGH);
  //microstep resolution to 1/16
  digitalWrite(M2ms1pin,HIGH);
  digitalWrite(M2ms2pin,HIGH);
  digitalWrite(M2ms3pin,HIGH);

  digitalWrite(M3ms1pin,HIGH);
  digitalWrite(M3ms2pin,HIGH);
  digitalWrite(M3ms3pin,HIGH);
}

void loop(){
  if(fill!=1){
    Instruction.first=0;
    fill=MotorStructFiller(&M1,&M2,&M3,&Instruction);
    }
  if(swstate==0){
    read(&msg,&date);
  }
}
