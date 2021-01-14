#ifndef FUNCTIONS_H

#define FUNCTIONS_H

#include <Arduino.h>
#include <math.h>
#include "Find_And_Identify.h"

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
const int outPin=44;



int motorselection(String Motor,int* dirPin,int* stepPin,int* nbsteptaken, int* reduction);
//use to chose motor(define pin to use), simplify setAngularMotion a lot. return(MXdirPin,MXstepPin,MXnbsteptaken,reduction). May add more return such as time.

void setAngularMotion(float angle,int dirPin,int stepPin,int* nbsteptaken,int Direction,int reduction,int Time);
//Use to do set angle(in degree),  and the time between LOW and HIGH. 
//microstepp conf is in function directly for now is't for 1/16 step(0.1125°) NEED TO ADD NEW ARGUMENT

void Motorpositionadd(int* nbsteptaken, float* Motorposition, int reduction);
//NEED TO ADD REDUCTION FATOR to have the correct value for now it's assume to be one for all motor

void rotate(float angle,String Motor,int Direction, float* Position);//use  motorselection setAngularMotion motorselectionposition 
//and Motorposition to rotate the motor and note it's position change

void positionInit(float* PosMRA,float* PosMDA,float Polaris_RA,float Polaris_DA);
//Initial position of RA motor and DA motor to the corresponding value of polaris, to use after observing polaris.

void positionreset(float* Pos);
// to reset position to 0


#endif