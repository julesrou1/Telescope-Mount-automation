#include <Arduino.h>

// defines pins numbers
// Step pin and directional pin
const int stepPin = 3; 
const int dirPin = 4; 
//Control Microstepping Resolution
const int ms1pin = 8;
const int ms2pin = 9;
const int ms3pin = 10;
//Use for switch
int inPin = 2;
int outPin=12;

void setup() {
// Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(ms1pin,OUTPUT);
  pinMode(ms2pin,OUTPUT);
  pinMode(ms3pin,OUTPUT);
// Control for switch
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin,HIGH);
//Setup direction and microstep resolution to 1/16
  digitalWrite(dirPin,HIGH);
  digitalWrite(ms1pin,LOW);
  digitalWrite(ms2pin,LOW);
  digitalWrite(ms3pin,LOW);
  pinMode(13, OUTPUT);
}

void setAngularMotion(float angle){
    int step=round(angle/(1.8));
    for(int x = 0; x < step; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
  }
}

void loop() {
  digitalWrite(dirPin,HIGH);
  if(digitalRead(inPin) == HIGH){
     for(int x = 0; x < 200; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
  }
  }
    else{
      setAngularMotion(45);
      digitalWrite(13, HIGH);            
      delay(500);
      digitalWrite(13, LOW);
    }
    
}