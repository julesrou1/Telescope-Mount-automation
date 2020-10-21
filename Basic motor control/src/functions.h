#ifndef FUNCTIONS_H

#define FUNCTIONS_H

#include <Arduino.h>
#include <math.h>
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
const int  inPin = 48;
const int outPin=53;



void setAngularMotion(float angle,String Motor,int Direction,int Time);
//Use to do set angle(in degree), specify motor with string "M1","M2", and the time between LOW and HIGH. 
//microstepp conf is in function directly for now is't for 1/16 step(0.1125°) NEED TO ADD NEW ARGUMENT

void constantRotation(String Motor,int step,int Direction,int Time);
//Use to do 360, specify motor with string "M1","M2", the step by default 3200 for 1/16 microstep, and the time between LOW and HIGH

void Motorposition(int Motorsteptaken, float Motorposition);
//NEED TO ADD REDUCTION FATOR to have the correct value for now it's assume to be one for all motor

void rotate(float angle,String Motor,int Direction);//use setAngularMotion and Motorposition to rotate the motor and note it's position change

#endif