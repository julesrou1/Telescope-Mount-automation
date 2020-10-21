#include "functions.h"
#include <Arduino.h>

int M1nbsteptaken=0;
int M2nbsteptaken=0;
float M1position=0;
float M2position=0;

void setAngularMotion(float angle,String Motor,int Direction,int Time=1000){
    int dir;
    if (Motor=="M1"){
      if (Direction==1){
        digitalWrite(M1dirPin,HIGH);
        dir=1;
        }else{
          digitalWrite(M1dirPin,LOW);
          dir=-1;
        }
      }else{
      if (Direction==1){
        digitalWrite(M2dirPin,HIGH);
        dir=1;
      }else{
        digitalWrite(M2dirPin,LOW);
        dir=-1;
      }
    }

    int step=round(angle/(0.1125)); //warning 0.1125 for 1/16 step change value if using microstep
    for(int x = 0; x < step; x++) {
      if (Motor=="M1"){
        digitalWrite(M1stepPin,HIGH);  
        delayMicroseconds(Time);
        digitalWrite(M1stepPin,LOW);
        delayMicroseconds(Time);
        M1nbsteptaken+=dir;
      }else{
        digitalWrite(M2stepPin,HIGH); 
        delayMicroseconds(Time);
        digitalWrite(M2stepPin,LOW);
        delayMicroseconds(Time);
        M2nbsteptaken+=dir;
      }
    }
}

void constantRotation(String Motor,int step=3200,int Direction=1,int Time=1000){
    int dir;
    if (Motor=="M1"){
      if (Direction==1){
        digitalWrite(M1dirPin,HIGH);
        dir=1;
        }else{
          digitalWrite(M1dirPin,LOW);
          dir=-1;
        }
      }else{
      if (Direction==1){
        digitalWrite(M2dirPin,HIGH);
        dir=1;
      }else{
        digitalWrite(M2dirPin,LOW);
        dir=-1;
      }
    }
    for(int x = 0; x < step; x++) {
      if (Motor=="M1"){
        M1nbsteptaken+=dir;
        digitalWrite(M1stepPin,HIGH);  
        delayMicroseconds(Time);
        digitalWrite(M1stepPin,LOW);
        delayMicroseconds(Time);  
      }else{
        digitalWrite(M2stepPin,HIGH); 
        delayMicroseconds(Time);
        digitalWrite(M2stepPin,LOW);
        delayMicroseconds(Time); 
        M1nbsteptaken+=dir;
      }
    }
}

void Motorpositionadd(int Motorsteptaken, float Motorposition){
  int angl=Motorsteptaken*0.1125;
  Motorsteptaken=0;
  Motorposition=+angl;
}

void rotate(float angle,String Motor,int Direction){
  setAngularMotion(angle,Motor,Direction,1000);
  if (Motor=="M1")
  {
    Motorpositionadd(M1nbsteptaken,M1position);
  }else{
    Motorpositionadd(M2nbsteptaken,M2position);
  }
  
}