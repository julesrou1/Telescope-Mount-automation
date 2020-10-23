#include "functions.h"
#include <Arduino.h>

int M1nbsteptaken=0;
int M2nbsteptaken=0;
float M1position=0;
float M2position=0;
int Motordirectory[] = {M1dirPin,M1stepPin,M1nbsteptaken,M2dirPin,M2stepPin,M2nbsteptaken};

int motorselection(String Motor,int* dirPin,int* stepPin,int* nbsteptaken){
  if (dirPin == NULL || stepPin == NULL || nbsteptaken == NULL) //flag if pointer were not created to prevend crash
  {
    return 0;
  }else{
    if (Motor=="M1")
    {*dirPin = Motordirectory[0];
    *stepPin = Motordirectory[1];
    *nbsteptaken = Motordirectory[2];}
    else if (Motor=="M2")
    {*dirPin = Motordirectory[3];
    *stepPin = Motordirectory[4];
    *nbsteptaken = Motordirectory[5];}
    else if (Motor=="M3")//motor 3 and 4 not declare may or may not be added to the system for now send to Motor 1
    {*dirPin = Motordirectory[3];
    *stepPin = Motordirectory[4];
    *nbsteptaken = Motordirectory[5];}
    else
    {*dirPin = Motordirectory[3];
    *stepPin = Motordirectory[4];
    *nbsteptaken = Motordirectory[5];}
    return 1;
  }
}

float motorselectionposition(String Motor){
    if (Motor=="M1"){return(M1position);}
    else if (Motor=="M2"){return(M2position);}
    else if (Motor=="M3"){return(M1position);}
    else{return(M1position);}
}


void setAngularMotion(float angle,int dirPin,int stepPin,int nbsteptaken,int Direction,int Time=1000){
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
        nbsteptaken+=dir;
      }
}


void Motorpositionadd(int Motorsteptaken, float Motorposition){
  int angl=Motorsteptaken*0.1125;
  Motorsteptaken=0;
  Motorposition=+angl;
}

void rotate(float angle,String Motor,int Direction){
  int dirPin;
  int stepPin;
  int nbsteptaken;
  float Mposition;
  int Time=1000;
  int status = motorselection(Motor,&dirPin,&stepPin,&nbsteptaken);
  if(status==0) {printf("Oh no issue with motorselection\n");};
  Mposition = motorselectionposition(Motor);

  setAngularMotion(angle,dirPin,stepPin,nbsteptaken,Direction,Time);

  Motorpositionadd(nbsteptaken,Mposition);
}