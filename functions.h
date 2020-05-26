#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

struct inspector1 { //data file
    float ta;
    float idle;
    float pro_time;
    };

struct inspector2{
    float ta;
    float idle;
    int type;
    };

//void Display(i1 *);

float *data(float *c, char STR[20], int *length);                           //Charles
float clockfcn(float i1ta, float i2ta, float w1ta, float w2ta, float w3ta); //Charles
int *counters(float i1ta,float i2ta,float w1ta,float w2ta,float w3ta,int b11, int b21, int b22, int b31,int b33,int i2type); //Cuautli
int *buffer1(float b11,int b21,int b31,int b22, int b33, int opt);          //Hai
float *timingp (float *c, int opt2, int nc, float lolimit, float range);    //David
float *timingw (float *c, int opt2, int nc, float range);                   //David

#endif // FUNCTIONS_H_INCLUDED
