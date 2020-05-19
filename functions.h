#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

struct inspector1 {
    float ta;
    float idle;
    };

struct inspector2{
    float ta;
    float idle;
    int type;
    };

//void Display(i1 *);

float *data(float *c, char STR[20], int *length);
float clockfcn(float i1ta, float i2ta, float w1ta, float w2ta, float w3ta);
int *counters(float i1ta,float i2ta,float w1ta,float w2ta,float w3ta,int b11, int b21, int b22, int b31,int b33,int i2type);
int *buffer1(float b11,int b21,int b31,int b22, int b33, int opt);
float *timingp (float *c, int opt2, int nc, float lolimit, float range);
float *timingw (float *c, int opt2, int nc, float range);

#endif // FUNCTIONS_H_INCLUDED
