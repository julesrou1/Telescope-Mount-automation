#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

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

float declinationAngle(float lattitude, float AD){
    return(AD - lattitude);
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

void lineSpliting(char* extractline,float* RA,float* AD){

    float RAH,RAM,RAS;
    float ADD,ADM,ADS;
    //printf("%s\n",extractline);

    char* piece=strtok(extractline,"	");

    for (int i = 0; i < 8; i++)
    {
        piece=strtok(NULL,"	");
        if (i==2){RAH=strtof(piece,NULL);}
        if (i==3){RAM=strtof(piece,NULL);}
        if (i==4){RAS=strtof(piece,NULL);}
        if (i==5){ADD=strtof(piece,NULL);}
        if (i==6){ADM=strtof(piece,NULL);}
        if (i==7){ADS=strtof(piece,NULL);}
        
    }
    //printf("%f,%f,%f;%f,%f,%f\n",RAH,RAM,RAS,ADD,ADM,ADS);
    angleFormating(RAH,RAM,RAS,ADD,ADM,ADS,RA,AD);
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
    // float Correctionsol=(SoleilDeg-90);
    // printf("Possition du couche de soleil soleil %f\n",SoleilDeg);
    // printf("Ecart entre soleil et couche du soleil %f\n",DegTime-SoleilDeg);
    // printf("ecart en astre observe et couche du soleil %f\n",fmodf((DegTime-SoleilDeg)-objet,360));
    // printf("position astre par rapport a 90 : %f\n",90+fmodf((DegTime-SoleilDeg)-objet,360));
    return 90+fmodf((DegTime-SoleilDeg)-RAcorrige,360);
}
int main(){
    char Line0[255],Line1[255],Line20[255];
    float RA,AD;
    lineExtraction(0,Line0);
    lineSpliting(Line0,&RA,&AD);
    printf("%f,%f\n",RA,AD);
    
    time_t now;
    struct tm *now_tm;
    int hour,min,sec,day,month,year;
    float DegTime;
    getTime(&hour,&min,&sec,&day,&month,&year,&DegTime);

    printf("the hour is %d %d %d date is %d %d %d\n",hour,min,sec,day,month,year);
    
    float Latitude=49.052502;
    int hsol=16;
    int msol=59;
    int ssol=0;
    float SoleilDeg=HourToDegree(hsol,msol,ssol);

    float ADcorrioge=declinationAngle(Latitude,AD);
    float RAcorrige=angleBehindTheSun({day,month,year},RA);
    printf("%f %f\n",RAcorrige,ADcorrioge);

    printf("position astre par rapport a 90 : %f\n",RApositionCalulation(RAcorrige,SoleilDeg,DegTime));

    return 0;


}
