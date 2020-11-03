#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void angleFormating(float RAH,float RAM,float RAS,float ADD,float ADM,float ADS,float* RA,float* AD){
    *RA=RAH*(360/24) + (RAM/60) + (RAS/3600);
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
    printf("%f,%f,%f;%f,%f,%f\n",RAH,RAM,RAS,ADD,ADM,ADS);
    angleFormating(RAH,RAM,RAS,ADD,ADM,ADS,RA,AD);
}

void lineExtraction(int n,char* returnLine){
    char tempLine[255];
    FILE * fPointer;
    fPointer = fopen("ISDB_simplify.TXT","r");
    int i=0;
    while (i!=n+1)
    {
        if(i==n){fgets(returnLine, 255,fPointer);}
        else{fgets(tempLine, 255,fPointer);}
        i++;
    }
    //printf("%s",returnLine);
}

int main(){
    char Line0[255],Line1[255],Line20[255];
    float RA,AD;
    lineExtraction(0,Line0);
    printf("%s",Line0);
    lineSpliting(Line0,&RA,&AD);
    printf("%f,%f\n",RA,AD);


    lineExtraction(20,Line20);
    printf("%s",Line20);
    lineSpliting(Line20,&RA,&AD);
    printf("%f,%f\n",RA,AD);

    //lineSpliting(lineExtraction(20));
    return 0;
}
