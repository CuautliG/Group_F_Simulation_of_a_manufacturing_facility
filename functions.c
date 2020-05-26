#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float *data(float *c, char STR[20], int *length){
FILE *ins= fopen(STR,"r");
int i =0;
char oneline[8];
while (!feof(ins)) {
    fscanf(ins,"%8s",oneline);
    c[i]=strtof(oneline,NULL);
    i++;
}
*length=i-1;
fclose(ins);
return c;
}

float clockfcn(float i1ta, float i2ta, float w1ta, float w2ta, float w3ta)
{
    float itime=1000;
    if (i1ta >0){
        itime=i1ta;
    }
    if ((i2ta > 0) && (itime > i2ta)){
        itime=i2ta;
    }
    if ((w1ta  > 0) && (itime > w1ta)) {
        itime=w1ta;
    }
    if ((w2ta  > 0) && (itime > w2ta)){
        itime=w2ta;
    }
    if ((w3ta  > 0) && (itime > w3ta)){
        itime=w3ta;
    }
    return itime;
}

int *counters(float i1ta,float i2ta,float w1ta,float w2ta,float w3ta,int b11, int b21, int b22, int b31,int b33,int i2type)
{
    int static s[]={0,0,0};
    if ((i1ta > 0) || ((b11==2) && (b21==2)&&(b31==2))){
        s[0]++;
    }
    else if (((i2ta >0) || (b22==2))&& (i2type == 2)) {
        s[1]++;
    }
    else if(((i2ta >0) || (b33==2))&& (i2type == 3)) {
        s[2]++;
    } else if (w1ta > 0) { // compute number of component being processed by workstations
        s[0]++;
    }
    else if(w2ta > 0) {
        s[0]++;
        s[1]++;
    }
    else if(w3ta > 0) {
        s[0]++;
        s[2]++;
    }else{
        s[0]=s[0];
        s[1]=s[1];
        s[2]=s[2];
    }

    s[0]+=b11+b21+b31;
    s[1]+=b22;
    s[2]+=b33;

    return s;
}

int *buffer1(float b11,int b21,int b31,int b22, int b33, int opt)
{
    int static b[]={0,0,0};
    if (opt==1){
        if (b21 < 2) {
            b[0] = 0;
            b[1] = 1;
            b[2] = 0;
        } else if (b31 < 2) { // if B2, B3 has no C2, C3 ready, the priority goes to B1
            b[0] = 0;
            b[1] = 0;
            b[2] = 1;
        } else {
            b[0] = 1;
            b[1] = 0;
            b[2] = 0;
        }
    }//End if option 1
    else {
        if  (((b21 < 1) && (b22 > 0)) || ((b21<2) && (b11 == 2))) { // if B2 has C2 ready then priority goes to B2
            b[0] = 0;
            b[1] = 1;
            b[2] = 0;
        } else if (((b31 < 1) && (b33 > 0)) || ((b31 < 2) && (b21 == 2))) { // if B3 has C3 ready then priority goes to B3
            b[0] = 0;
            b[1] = 0;
            b[2] = 1;
        } else { // if B2, B3 has no C2, C3 ready, the priority goes to B1
            b[0] = 1;
            b[1] = 0;
            b[2] = 0;
        }
    } //End option 2
    return b;
}

float *timingp (float *c, int opt2, int nc, float lolimit, float range){
    float *ptime;
    if (opt2 == 1){
        ptime=c+nc;
    } else {
        float r=(lolimit+((float)rand()/(float)RAND_MAX)*range);
        ptime=&r;
    }
    return ptime;
}

float *timingw (float *c, int opt2, int nc, float range){
    float *ptime;
    if (opt2 == 1){
        ptime=c+nc;
    } else {
        float r=(((float)rand()/(float)RAND_MAX)*range);
        ptime=&r;
    }
    return ptime;
}

