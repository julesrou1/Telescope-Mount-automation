#include "functions.h"
#include <Arduino.h>

int MotorStructFiller(Motor *M1, Motor *M2, Motor *M3, SemiAuto *Instruction){

  M1->Name = "M1";//DA motor
  M1->dirPin = M1dirPin;
  M1->stepPin = M1stepPin;
  M1->Direction = 1;
  M1->Reduction = 100;
  M1->Position = 0;
  M1->TimesFast = 100;
  M1->TimesSlow = 100;

  M2->Name = "M2";//moteur d'asservisement RA
  M2->dirPin = M2dirPin;
  M2->stepPin = M2stepPin;
  M2->Direction = 1;
  M2->Reduction = 100;
  M2->Position = 0;
  M2->TimesFast = 100;
  M2->TimesSlow = 100;

  M3->Name = "M3";// Latitde motor
  M3->dirPin = M3dirPin;
  M3->stepPin = M3stepPin;
  M3->Direction = 1;
  M3->Reduction = 100;
  M3->Position = 0;
  M3->TimesFast = 100;
  M3->TimesSlow = 100;

  Instruction->newinstruction=0;
  return 1;
}

void setAngularMotion(float angle, Motor *M, int *nbsteptaken, char speed){
  int step = round((angle * (M->Reduction)) / (0.1125)); //warning 0.1125 for 1/16 step change value if using microstep

  if (M->Direction == 1){ //setup direction high seen has positive rotation
    digitalWrite(M->dirPin, HIGH);
  }
  else{
    digitalWrite(M->dirPin, LOW);
  }
  if (speed == 'F'){
    for (int x = 0; x < step; x++){
      digitalWrite(M->stepPin, HIGH);
      delayMicroseconds(100);
      digitalWrite(M->stepPin, LOW);
      delayMicroseconds(M->TimesFast);
      *nbsteptaken += (M->dirPin);
    }
  }
  else{
    for (int x = 0; x < step; x++){
      digitalWrite(M->stepPin, HIGH);
      delay(100);
      digitalWrite(M->stepPin, LOW);
      delay(M->TimesSlow);
      *nbsteptaken += (M->dirPin);
    }
  }
}

void Motorpositionadd(int *nbsteptaken, Motor *M){
  M->Position = +((*nbsteptaken) * 0.1125) / (M->Reduction);
}

void rotate(float angle, Motor *M, int Direction, char speed){
  M->Direction = Direction;
  int nbsteptaken = 0;
  setAngularMotion(angle, M, &nbsteptaken, speed);
  Motorpositionadd(&nbsteptaken, M);
}

void cstRotate(Motor *M, int Direction){
  char speed = 'S';
  int nbsteptaken = 0;
  setAngularMotion(1, M, &nbsteptaken, speed);
  Motorpositionadd(&nbsteptaken, M);
}

void positionInit(float *PosMRA, float *PosMDA, float Polaris_RA, float Polaris_DA){
  *PosMRA = Polaris_RA;
  *PosMDA = Polaris_DA;
}
void positionreset(Motor *M){
  M->Position = 0;
}

void msgFormating(MsgReceived *msg,Date * dt){
  char *piece = strtok(msg->buf, ";");
  msg->mode = piece;
  if (strcmp(msg->mode,"01"))//Instruction for new object to observ
  {
    for (int i = 0; i < 8; i++){
      piece = strtok(NULL, ";");
      if (i == 0){msg->RA = atof(piece);}
      if (i == 1){msg->DA = atof(piece);}
      if (i == 2){
        msg->y = atof(piece);
        dt->y=  atof(piece);
      }
      if (i == 3){
        msg->m = atof(piece);
        dt->m=  atof(piece);
      }
      if (i == 4){
        msg->d = atof(piece);
        dt->d=  atof(piece);
      }
      if (i == 5){msg->h = atof(piece);}
      if (i == 6){msg->mm = atof(piece);}
      if (i == 7){msg->s = atof(piece);}
    }
    angleCorrection(msg,dt);
  }
  if (strcmp(msg->mode,"00")){
    for (int i = 0; i < 8; i++){
      piece = strtok(NULL, ";");
      if (i == 0){msg->latitude = atof(piece);}
      if (i == 1){msg->longitude = atof(piece);}
      if (i == 2){msg->altitude = atof(piece);}
    }
  }
  msg->flags = 0;
  msg->newinstruction=1;
  strcpy(msg->buf,"");
}

void read(MsgReceived * msg,Date * d){
  int i = 0;
  while (Serial1.available() > 0){
    msg->flags = 1;
    byte incomingByte = Serial1.read();
    char x1 = (char)incomingByte;
    if (incomingByte != -1){
      msg->buf[i] = x1;
      i = i + 1;
    }
  }
  if (msg->flags == 1){
    msgFormating(msg,d);
  }
}

//////////////////////////////////////////////////////////////////////////////
//Number for day in each months

int countLeapYears(Date d){
  int years = d.y;
  // Check if the current year needs to be considered for the count of leap years
  if (d.m <= 2)
    years--;
  return (years / 4) - (years / 100) + (years / 400); // An year is a leap year if it  is a multiple of 4,multiple of 400 and not a  multiple of 100.
}

int getDifference(Date dt1, Date dt2)
{    // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1'  initialize count using years and day
  long int n1 = dt1.y * 365 + dt1.d;
  // Add days for months in given date
  for (int i = 0; i < dt1.m - 1; i++)
    n1 += monthDays[i];
  // Since every leap year is of 366 days, Add a day for every leap year
  n1 += countLeapYears(dt1);
  // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2'
  long int n2 = dt2.y * 365 + dt2.d;
  for (int i = 0; i < dt2.m - 1; i++)
  {
    n2 += monthDays[i];
  }
  n2 += countLeapYears(dt2);

  return (n2 - n1);
}

void angleBehindTheSun(MsgReceived * msg,Date * dt){
    
  int daybetween = getDifference({ 21, 3, 2020 },*dt);
  // return(RA-daybetween*(360/365));
  msg->RARelatif=msg->RA-daybetween*(360/365);
}

void declinationAngle(MsgReceived * msg){
   // return(AD - lattitude);
  msg->DARelatif=msg->DA-msg->latitude;
}

void angleCorrection(MsgReceived * msg,Date * dt){
  angleBehindTheSun(msg, dt);
  declinationAngle(msg);
}
