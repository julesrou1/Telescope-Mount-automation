#include <Arduino.h>

// defines pins numbers
// Step pin and directional pin
const int stepPin = 3; 
const int dirPin = 4; 
//Control Microstepping Resolution
const int ms1pin = 8;
const int ms2pin = 9;
const int ms3pin = 10; 


void setup() {
// Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ms1pin,OUTPUT);
  pinMode(ms2pin,OUTPUT);
  pinMode(ms3pin,OUTPUT);
//Setup direction and microstep resolution to 1/16
  digitalWrite(dirPin,HIGH);
  digitalWrite(ms1pin,HIGH);
  digitalWrite(ms2pin,HIGH);
  digitalWrite(ms3pin,HIGH);
}

void loop() {
  for(int x = 0; x < 3600; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
}