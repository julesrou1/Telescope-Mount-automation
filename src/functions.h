#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include <math.h>
#include <TimerOne.h>
#include <TimerFour.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// defines pins numbers FOR MOTOR 1
// Step pin and directional pin
const int M1stepPin = 24; 
const int M1dirPin = 22; 
//Control Microstepping Resolution
const int M1ms1pin = 30;
const int M1ms2pin = 28;
const int M1ms3pin = 26;

// defines pins numbers FOR MOTOR 2
// Step pin and directional pin
const int M2stepPin = 34; 
const int M2dirPin = 32; 
//Control Microstepping Resolution
const int M2ms1pin = 40;
const int M2ms2pin = 38;
const int M2ms3pin = 36;
// defines pins numbers FOR MOTOR 3
// Step pin and directional pin
const int M3stepPin = 44; 
const int M3dirPin = 42; 
//Control Microstepping Resolution
const int M3ms1pin = 50;
const int M3ms2pin = 48;
const int M3ms3pin = 46;
//Led
const int pinLED1=29;
const int pinLED2=31;
const int pinLED3=33;
//Joystick
const int swPin = 21;
const int VRx = A0;
const int VRy = A1;

typedef struct Motor{
    String Name;
    int dirPin;
    int stepPin;
    int Direction;//direction +1 for trigo -1 for clock
    int Reduction; //reduction ratio
    float Position;
    float EquatorialPosition;
    int Times;
    int cst;

} Motor;

typedef struct MsgReceived{
    char * buf;
    float RA,DA;
    float RARelatif,DARelatif;
    int y,m,d,h,mm,s;
    char * mode;
    float latitude,longitude,altitude;
    int flags; 
    int newinstruction;
}MsgReceived;

typedef struct SemiAuto{
    int first;
    float RA,DA;
    float NextRA,NextDA;
    float deltaRA,deltaDA;
    int rotate; 
    int newinstruction;
}SemiAuto;

struct Date {int d, m, y;};


//fill struct M1 abd M2
int MotorStructFiller(Motor* M1,Motor* M2,Motor* M3, SemiAuto *Instruction);

//Use to do move angle(in degree),  and the time between LOW and HIGH. 
//microstepp conf is in function directly for now is't for 1/16 step(0.1125°) NEED TO ADD NEW ARGUMENT
void setAngularMotion(float angle,Motor* M,int* nbsteptaken);

//Use for RA cst rotation
void cstRotate(Motor *M, int Direction);

//Change position
void Motorpositionadd(int* nbsteptaken,Motor* M);

//Input angle to ratate, the motor the dirrection +1,-1 and the speed 'F' Fast, 'S' Slow rotate(1,&M2,-1,'F')
//use setAngularMotion Motorpositionadd
void rotate(float angle,Motor* M,int Direction);

//Initial position of RA motor and DA motor to the corresponding value of polaris, to use after observing polaris.
//TODO to work on, not sure if it is usefull
void positionInit(float* PosMRA,float* PosMDA,float Polaris_RA,float Polaris_DA);

// to reset position to 0
void positionreset(Motor* M);

//fill the struct msg
//TODO ADD more mode and action to do after
void msgFormating(MsgReceived * msg,Date * d);

//to read incoming data comming from port 21 22 use msgFormating
// void read(MsgReceived * msg,Date * d);

/////////////////////////////
//Find and Identify
const int monthDays[12]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
// AD is angle of declination; RA is right ascension ; RA H M S hours minutes seconds

int countLeapYears(Date d);

int getDifference(Date dt1, Date dt2);

void angleBehindTheSun(MsgReceived * msg,Date * dt);

void declinationAngle(MsgReceived * msg);

void angleCorrection(MsgReceived * msg,Date * dt);

#endif

