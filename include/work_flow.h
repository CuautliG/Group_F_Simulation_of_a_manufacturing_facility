#ifndef WORK_FLOW_H_INCLUDED
#define WORK_FLOW_H_INCLUDED

int work_flow(struct CONFIG *my_config,struct PTIME *my_ptime,struct STATE *my_state);
float clockfcn(float i1ta, float i2ta, float w1ta, float w2ta, float w3ta);
int *counters(float i1ta,float i2ta,float w1ta,float w2ta,float w3ta,int b11, int b21, int b22, int b31,int b33,int i2type);
int *buffer1(float b11,int b21,int b31,int b22, int b33, int opt);

#endif // WORK_FLOW_H_INCLUDED
