#include "functions.h"
#include <Arduino.h>

int Motordirectory[] = {M1dirPin,M1stepPin,1,M2dirPin,M2stepPin,1};

int motorselection(String Motor,int* dirPin,int* stepPin,int* nbsteptaken, int* reduction){
  if (dirPin == NULL || stepPin == NULL || nbsteptaken == NULL) //flag if pointer were not created, return 0 to prevend crash
  {
    return 0;
  }else{
    if (Motor=="M1")
    {*dirPin = Motordirectory[0];
    *stepPin = Motordirectory[1];
    *reduction = Motordirectory[2];}
    else if (Motor=="M2")
    {*dirPin = Motordirectory[2];
    *stepPin = Motordirectory[3];
    *reduction = Motordirectory[4];}
    else if (Motor=="M3")//motor 3 and 4 not declare may or may not be added to the system for now send to Motor 2
    {*dirPin = Motordirectory[2];
    *stepPin = Motordirectory[3];
    *reduction = Motordirectory[4];}
    else
    {*dirPin = Motordirectory[2];
    *stepPin = Motordirectory[3];
    *reduction = Motordirectory[4];}
    return 1;
  }
}


void setAngularMotion(float angle,int dirPin,int stepPin,int* nbsteptaken,int Direction,int Time=1000){
    int dir;
    int step=round(angle/(0.1125)); //warning 0.1125 for 1/16 step change value if using microstep

    if (Direction==1){ //setup direction high seen has positive rotation
      digitalWrite(dirPin,HIGH);
      dir=1;
      }else{
        digitalWrite(dirPin,LOW);
        dir=-1;}


    for(int x = 0; x < step; x++) {
        digitalWrite(stepPin,HIGH);  
        delayMicroseconds(Time);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(Time);
        *nbsteptaken+=dir;
      }
}


void Motorpositionadd(int* nbsteptaken, float* Motorposition,int reduction){
  float angl=((*nbsteptaken)*0.1125)/reduction;
  *nbsteptaken=0;
  *Motorposition=+angl;
}

void rotate(float angle,String Motor,int Direction, float* Position){
  int dirPin;
  int stepPin;
  int nbsteptaken=0;
  int Time=1000;
  int reduction;
  int status = motorselection(Motor,&dirPin,&stepPin,&nbsteptaken,&reduction);
  if(status==0) {printf("Oh no issue with motorselection\n");};

  setAngularMotion(angle,dirPin,stepPin,&nbsteptaken,Direction,Time);

  Motorpositionadd(&nbsteptaken, Position,reduction);

}

void positionreset(float* Pos){
  *Pos=0;
}