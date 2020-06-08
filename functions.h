#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

struct inspector1 {
        float ta, idle;
};
struct inspector2 {
        float ta, idle;
        int type;
        };
struct My_ptime{
    float *c1, *c2, *c3, *w1, *w2, *w3;
    };
typedef struct My_ptime My_ptime;
struct Sub_state {
    struct inspector1 *i1;
    struct inspector2 *i2;
    float w1ta, w2ta, w3ta;
};
typedef struct Sub_state Sub_state;
struct Config {
    int Model_type, read_generator;
    float lo_limit, up_limit;
};
typedef struct Config Config;
struct State{
    int b11, b21, b22, b31, b33; // number of components in buffers
    int nc1,nc2,nc3; // number of component used at the current time
    int np1,np2,np3; // number of products assembled at the current time
    float clock,itime; // simulation time
    int iteration;
    int sim_length;
    };
typedef struct State State;


//void Display(i1 *);

float *data(float *c, char STR[20], int *length);
float clockfcn(float i1ta, float i2ta, float w1ta, float w2ta, float w3ta);
int *counters(float i1ta,float i2ta,float w1ta,float w2ta,float w3ta,int b11, int b21, int b22, int b31,int b33,int i2type);
int *buffer1(float b11,int b21,int b31,int b22, int b33, int opt);
float *timing (float *c, int opt2, int nc, float lolimit, float range);

#endif // FUNCTIONS_H_INCLUDED
