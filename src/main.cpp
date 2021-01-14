#include <Arduino.h>
#include "functions.h"
#include <stdio.h>
#include "Find_And_Identify.h"
#include <TimerOne.h>
//#include "sqlite3.h"
int RArotation=1;
const int swPin = 2;
int n=0;
const int VRx = A0;
const int VRy = A1;
const int down = 30;
const int up =36;
const int right = 34;
const int left = 32;
int mapX = 0;
int mapY = 0;
int xPosition = 0;
int yPosition = 0;
int swstate=0;

void tim1(){
  if(swstate==1){
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      mapX = map(xPosition, 0, 1023, -512, 512);
      mapY = map(yPosition, 0, 1023, -512, 512);
      if(mapX>100){
        digitalWrite(right,HIGH);
        delay(1000);
        digitalWrite(right,LOW);
      }
      if(mapX<-100){
        digitalWrite(left,HIGH);
        delay(1000);
        digitalWrite(left,LOW);
      }
      if(mapY>100){
        digitalWrite(up,HIGH);
        delay(1000);
        digitalWrite(up,LOW);
      }
      if(mapY<-100){
        digitalWrite(down,HIGH);
        delay(1000);
        digitalWrite(down,LOW);
      }
      } 
    if(swstate==0){
    digitalWrite(up,LOW);
    digitalWrite(down,LOW);
    digitalWrite(right,LOW);
    digitalWrite(left,LOW);
    }
 }
void blink(){
  swstate=(swstate+1)%2;
}
void setup() {
  Serial.begin(9600); 
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(up,OUTPUT);
  pinMode(down,OUTPUT);
  pinMode(right,OUTPUT);
  pinMode(left,OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(swPin), blink, LOW);
  Timer1.initialize(100);
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
  //microstep resolution to 1
  digitalWrite(M2ms1pin,HIGH);
  digitalWrite(M2ms2pin,HIGH);
  digitalWrite(M2ms3pin,HIGH);
}

void loop() {
    //float PosM1=0;
    float PosM2=0;
    
    while(RArotation==1){
      rotate(360,"M2",1,&PosM2);
      delay(500);
    }
    
}
