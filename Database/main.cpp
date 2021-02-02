#include "spa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define pi       3.1415926535897932384626433832795028841971
struct Date {int d, m, y;};

const int monthDays[12]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int countLeapYears(Date d){
    int years = d.y;
    // Check if the current year needs to be considered for the count of leap years
    if (d.m <= 2)
        years--;
    return (years/4) - (years/100) + (years/400); // An year is a leap year if it  is a multiple of 4,multiple of 400 and not a  multiple of 100.
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
    for (int i = 0; i < dt2.m - 1; i++){
        n2 += monthDays[i];
    }
    n2 += countLeapYears(dt2);

    return (n2 - n1);
}

float angleBehindTheSun(Date dt,float RA){

    float daybetween = getDifference({ 21, 3, 2020 },dt);
    return(RA-(float) (daybetween*360/365));
}

float declinationAngle(float lattitude, float AD){ //utilise pour verifier que l'object est observable si abs>90 non observable
    return(AD - lattitude); //donne angle par rapport a la tangente au sol
}


float HourToDegree(float Hours, float Minutes,float Seconds){
    return (Hours + Minutes/60 + Seconds/3600)*(360/24);
}

void DegreeToHour(float degree,int* h,int* m,int* s){
    int sec;
    sec =3600*degree;
	*h = (sec/3600); 
	*m = (sec -(3600*(*h)))/60;
	*s = (sec -(3600*(*h))-(*m*60));
    *h = degree*6/90;
}

void angleFormating(float RAH,float RAM,float RAS,float ADD,float ADM,float ADS,float* RA,float* AD){
    *RA=HourToDegree(RAH, RAM,RAS);
    *AD=ADD + (ADM/60) + (ADS/3600);
}

void lineSpliting(char* extractline){

    float RA,DA;
    int y,m,j,h,mm,s;
    char * mode;

    char* piece=strtok(extractline,";");
    mode = piece;
    for (int i = 0; i < 8; i++)
    {
        piece=strtok(NULL,";");
        if (i==0){RA=atof(piece);}
        if (i==1){DA=atof(piece);}
        if (i==2){y=atof(piece);}
        if (i==3){m=atof(piece);}
        if (i==4){j=atof(piece);}
        if (i==5){h=atof(piece);}
        if (i==6){mm=atof(piece);}
        if (i==7){s=atof(piece);}
    }
    printf("test %s, %f,%f,%d;%d,%d,%d,%d,%d\n",mode,RA,DA,y,m,j,h,mm,s);

}

void lineExtraction(int n,char* returnLine){
    char tempLine[255];
    FILE * fPointer;
    fPointer = fopen("ISBD.txt","r");
    int i=0;
    while (i!=n+1)
    {
        if(i==n){fgets(returnLine, 255,fPointer);}
        else{fgets(tempLine, 255,fPointer);}
        i++;
    }
    //printf("%s",returnLine);
}

void getTime(int* hour,int* min,int* sec,int* day,int* month,int* year,float* DegTime){
    time_t now;
    struct tm *now_tm;
    now = time(NULL);
    now_tm = localtime(&now);
    *hour = now_tm->tm_hour;
    *min = now_tm->tm_min;
    *sec = now_tm->tm_sec;
    *day = now_tm->tm_mday;
    *month = now_tm->tm_mon+1;
    *year = now_tm->tm_year+1900;
    *DegTime=HourToDegree(*hour,*min,*sec);
}

float RApositionCalulation(float RAcorrige,float SoleilDeg, float DegTime){ 
    // Not usefull actually
    // float Correctionsol=(SoleilDeg-90);
    // printf("Possition du couche de soleil soleil %f\n",SoleilDeg);
    // printf("Ecart entre soleil et couche du soleil %f\n",DegTime-SoleilDeg);
    // printf("ecart en astre observe et couche du soleil %f\n",fmodf((DegTime-SoleilDeg)-objet,360));
    // printf("position astre par rapport a 90 : %f\n",90+fmodf((DegTime-SoleilDeg)-objet,360));
    return 90+fmodf((DegTime-SoleilDeg)-RAcorrige,360);
}

void EqToH(){
    // TODO add input to fct
    float altitude=(90-64.294)* pi / 180;
    float Azimute=165.8* pi / 180;
    float latitude=40* pi / 180;
    float LST=(265.57+2)* pi / 180;
    float declination=asin(sin(altitude)*sin(latitude)+cos(latitude)*cos(altitude)*cos(Azimute));
    float RA=LST-asin(-sin(Azimute)*cos(altitude)/cos(declination));
    printf("RA : %f, Declination :%f\n",RA*180/pi,declination*180/pi);
}

void HToEq(){
    // ! Doesn't work
    float RA=281.39* pi / 180;
    float DA=-23* pi / 180;
    float LST=(265.57+2)* pi / 180;
    float latitude=40*pi/180;
    float H=LST-RA;
    float altitude=asin(sin(DA)*sin(latitude)+cos(DA)*cos(latitude)*cos(H));
    float Azimute= asin(-sin(H)*cos(latitude)/cos(altitude));
    printf("Zenith : %f, Azimute :%f\n",90-altitude,Azimute*180/pi);
}

int main(){
    char Line0[255],Line1[255],Line20[255];
    float RA,AD;
    lineExtraction(0,Line0);
    //lineSpliting(Line0,&RA,&AD);
    printf("%f,%f\n",RA,AD);
    time_t now;
    struct tm *now_tm;
    int hour,min,sec,day,month,year;
    float DegTime;
    // getTime(;,&DegTime);

    printf("the hour is %d %d %d date is %d %d %d\n",hour,min,sec,day,month,year);
    int result;
    spa_data spa;
    double latitude=(double)49.0356;
    double longitude=(double)2.0603;
    spa.year          = year;
    spa.month         = month;
    spa.day           = day;
    spa.hour          =hour;
    spa.minute        = min;
    spa.second        = sec;
    spa.timezone      = 1;
    spa.delta_ut1     = 0;
    spa.delta_t       = 67;
    spa.longitude     = longitude;
    spa.latitude      = latitude;
    spa.elevation     = 25;
    spa.pressure      = 820;
    spa.temperature   = 11;
    spa.slope         = 30;
    spa.azm_rotation  = -10;
    spa.atmos_refract = 0.5667;
    spa.function      = SPA_ZA;
    // result = spa_calculate(&spa);
    // if (result == 1) printf("SPA Error Code: %d\n", result);
    // printf("Zenith:        %.6f degrees\n", spa.zenith);
    // printf("Azimuth:       %.6f degrees\n", spa.azimuth);
    // printf("Right ascension %.6f degrees\n",spa.alpha);
    // printf("Declination %.6f degrees\n",spa.delta);
    char line[200]="01;40.15;340;2021;01;26;17;0;13";
    lineSpliting(line);
    EqToH();
    HToEq();
    printf("%f\n",HourToDegree(22,34,01));
    // float Latitude=49.052502;
    // int hsol=16;
    // int msol=53;
    // int ssol=0;
    // float SoleilDeg=HourToDegree(hsol,msol,ssol);

    // float ADcorrioge=declinationAngle(Latitude,AD);
    // float RAcorrige=angleBehindTheSun({day,month,year},RA);
    // printf("%f %f\n",RAcorrige,ADcorrioge);
    // HourToDegree(0, 25,0);
    // float Polaris_RA,Polaris_DA;
    // angleFormating(2,31,49.09,89,15,50.8,&Polaris_RA,&Polaris_DA);
    // printf("Polaris RA: %f DA: %f\n",angleBehindTheSun({day,month,year},Polaris_RA),Polaris_DA);
    return 0;
}
