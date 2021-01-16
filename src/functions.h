#ifndef FUNCTIONS_H

#define FUNCTIONS_H

#include <Arduino.h>
#include <math.h>
#include "Find_And_Identify.h"
#include <stdio.h>
#include <TimerOne.h>

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

typedef struct Motor{
    String Name;
    char Speed;
    int dirPin;
    int stepPin;
    int Direction;//direction +1 for trigo -1 for clock
    int Reduction; //reduction ratio
    float Position;
    int TimesSlow;
    int TimesFast;
} Motor;

//fill struct M1 abd M2
int MotorStructFiller(Motor* M1,Motor* M2);

//Use to do move angle(in degree),  and the time between LOW and HIGH. 
//microstepp conf is in function directly for now is't for 1/16 step(0.1125°) NEED TO ADD NEW ARGUMENT
void setAngularMotion(float angle,Motor* M,int* nbsteptaken,char speed);

//Change position
void Motorpositionadd(int* nbsteptaken,Motor* M);

//Input angle to ratate, the motor the dirrection +1,-1 and the speed 'F' Fast, 'S' Slow rotate(1,&M2,-1,'F')
//use setAngularMotion Motorpositionadd
void rotate(float angle,Motor* M,int Direction,char speed);

//Initial position of RA motor and DA motor to the corresponding value of polaris, to use after observing polaris.
void positionInit(float* PosMRA,float* PosMDA,float Polaris_RA,float Polaris_DA);

// to reset position to 0
void positionreset(Motor* M);



#endif