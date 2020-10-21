#include <Arduino.h>
// defines pins numbers FOR MOTOR 1
// Step pin and directional pin
const int M1stepPin = 29; 
const int M1dirPin = 31; 
//Control Microstepping Resolution
const int M1ms1pin = 23;
const int M1ms2pin = 25;
const int M1ms3pin = 27;

// defines pins numbers FOR MOTOR 2
// Step pin and directional pin
const int M2stepPin = 43; 
const int M2dirPin = 45; 
//Control Microstepping Resolution
const int M2ms1pin = 37;
const int M2ms2pin = 39;
const int M2ms3pin = 41;

//Use for switch
int inPin = 48;
int outPin=53;
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
//Setup direction and microstep resolution to 1/16
  digitalWrite(M1dirPin,HIGH);
  digitalWrite(M1ms1pin,HIGH);
  digitalWrite(M1ms2pin,HIGH);
  digitalWrite(M1ms3pin,HIGH);
  digitalWrite(M2dirPin,HIGH);
  digitalWrite(M2ms1pin,LOW);
  digitalWrite(M2ms2pin,LOW);
  digitalWrite(M2ms3pin,LOW);
  pinMode(13, OUTPUT);
}

void setAngularMotion(float angle){
    int step=round(angle/(1.8));
    for(int x = 0; x < step; x++) {
      digitalWrite(M1stepPin,HIGH); 
      digitalWrite(M2stepPin,HIGH); 
      delayMicroseconds(1000);
      digitalWrite(M1stepPin,LOW);
      digitalWrite(M2stepPin,LOW);
      delayMicroseconds(1000);  
  }
}


void loop() {
  digitalWrite(M1dirPin,HIGH);
  if(digitalRead(inPin) == HIGH){
     for(int x = 0; x < 3200; x++) {
      digitalWrite(M1stepPin,HIGH); 
      digitalWrite(M2stepPin,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(M1stepPin,LOW);
      digitalWrite(M2stepPin,LOW);
      delayMicroseconds(1000); 
  }
  }
    else{
      setAngularMotion(45);
      digitalWrite(13, HIGH);            
      delay(500);
      digitalWrite(13, LOW);
    }
    
}