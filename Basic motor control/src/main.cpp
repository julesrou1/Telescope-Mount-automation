#include <Arduino.h>
#include "functions.h"
#include <stdio.h>
//#include "visual.h"

void setup() {
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
  digitalWrite(M2ms1pin,LOW);
  digitalWrite(M2ms2pin,LOW);
  digitalWrite(M2ms3pin,LOW);
  pinMode(13, OUTPUT);
}

void loop() {
  while (digitalRead(inPin) == HIGH){
  float PosM1=0;

  rotate(100,"M1",1,&PosM1);

  } 
}