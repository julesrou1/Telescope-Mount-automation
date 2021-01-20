#include <Arduino.h>
#include "functions.h"
#include <stdio.h>
#include "Find_And_Identify.h"
#include <TimerOne.h>
//#include "sqlite3.h"
int RArotation=1;
int n=0;
const int pinLED=4;
const int swPin = 2;
const int VRx = A0;
const int VRy = A1;
int mapX = 0;
int mapY = 0;
int xPosition = 0;
int yPosition = 0;
int swstate=0;
int fill=0;
struct Motor M1;
struct Motor M2;
void tim1(){
  if(swstate==1){
    digitalWrite(pinLED,HIGH);
    xPosition = analogRead(VRx);
    yPosition = analogRead(VRy);
    mapX = map(xPosition, 0, 1023, -512, 512);
    mapY = map(yPosition, 0, 1023, -512, 512);
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
 }
void swactivation(){
  swstate=(swstate+1)%2;
}
void setup() {
  Serial.begin(9600); 
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(pinLED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(swPin), swactivation, LOW);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(tim1);

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
  if(fill!=1){fill=MotorStructFiller(&M1,&M2);}
  // rotate(90,&M2,1,'F');
  // delay(500);
}
