#include "functions.h"
#include <Arduino.h>

int MotorStructFiller(Motor* M1,Motor* M2){

  M1->Name="M1";
  M1->dirPin=M1dirPin;
  M1->stepPin=M1stepPin;
  M1->Direction=1;
  M1->Reduction=1;
  M1->Position=0;
  M1->TimesFast=500;
  M1->TimesSlow=113;

  M2->Name="M2";
  M2->dirPin=M2dirPin;
  M2->stepPin=M2stepPin;
  M2->Direction=1;
  M2->Reduction=1;
  M2->Position=0;
  M2->TimesFast=500;
  M2->TimesSlow=500;

  return 1;
}

void setAngularMotion(float angle,Motor* M,int* nbsteptaken,char speed){
    int step=round((angle*(M->Reduction))/(0.1125)); //warning 0.1125 for 1/16 step change value if using microstep

    if (M->Direction==1){ //setup direction high seen has positive rotation
      digitalWrite(M->dirPin,HIGH);
      }else{
        digitalWrite(M->dirPin,LOW);}
    if (speed=='F')
    {
      for(int x = 0; x < step; x++) {
        digitalWrite(M->stepPin,HIGH);  
        delayMicroseconds(M->TimesFast);
        digitalWrite(M->stepPin,LOW);
        delayMicroseconds(M->TimesFast);
        *nbsteptaken+=(M->dirPin);}
    }else{
        for(int x = 0; x < step; x++) {
        digitalWrite(M->stepPin,HIGH);  
        delay(M->TimesSlow);
        digitalWrite(M->stepPin,LOW);
        delay(M->TimesSlow);
        *nbsteptaken+=(M->dirPin);
      }
    } 
}

void Motorpositionadd(int* nbsteptaken,Motor* M){
  M->Position=+((*nbsteptaken)*0.1125)/(M->Reduction);
}

void rotate(float angle,Motor* M,int Direction,char speed){
  M->Direction=Direction;
  int nbsteptaken=0;
  setAngularMotion(angle,M,&nbsteptaken,speed);
  Motorpositionadd(&nbsteptaken,M);
}

void positionInit(float* PosMRA,float* PosMDA,float Polaris_RA,float Polaris_DA){
  *PosMRA=Polaris_RA;
  *PosMDA=Polaris_DA;
}
void positionreset(Motor* M){
  M->Position=0;
}
