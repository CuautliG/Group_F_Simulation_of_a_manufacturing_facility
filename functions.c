#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

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

char clockfcn(float i1ta, float i2ta, float w1ta, float w2ta, float w3ta, float *clock)
{
    char error=0; // code runs perfect
    float itime=FLT_MAX;
    if ((i1ta==NULL) || (i2ta==NULL) || (w1ta==NULL) || (w2ta==NULL) || (w3==NULL))) {  // precondition testing
        error=1; // error "invalid input"
        puts("Error C1 in clockfcn: one or more inputs are null\n");
    }
    else {

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
    }
    if ((itime > i1ta) || (itime >i2ta) || (itime >w1ta) || (itime >w2ta) || (itime >w3ta)||(itime==FLT_MAX)) // postcondition testing
    {
        error=3;
        puts("Error 2 in clockfcn: the function doesn't work properly \n");
    }
    else { clock=&itime; }
    return error;
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
        if (b11 < 2) {
            b[0] = 1;
            b[1] = 0;
            b[2] = 0;
        } else if (b21 < 2) { // if B2, B3 has no C2, C3 ready, the priority goes to B1
            b[0] = 0;
            b[1] = 1;
            b[2] = 0;
        } else {
            b[0] = 0;
            b[1] = 0;
            b[2] = 1;
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

//====================WORK FLOW===================
int internal_work_flow(Config config, State *state, PTIME *ptime)
{
//=================READ DATA================
float *c1=ptime->c1; // address of processing time C1
float *c2=ptime->c2; // address of processing time C2
float *c3=ptime->c3; // address of processing time C3
float *w1=ptime->w1; // address of processing time P1
float *w2=ptime->w2; // address of processing time P2
float *w3=ptime->w3; // address of processing time P3
int lengthc1=config.sim_length; // number of component C1 supplied for simulation
int lengthc2=config.sim_length; // number of component C2 supplied for simulation
int lengthc3=config.sim_length; // number of component C3 supplied for simulation
int lengthw1=config.sim_length; // number of time intervals for assembling P1 for simulation
int lengthw2=config.sim_length; // number of time intervals for assembling P2 for simulation
int lengthw3=config.sim_length; // number of time intervals for assembling P3 for simulation
int option=config.model_type; // Model choice
//=================END OF READING DATA================
//Initial conditions
float ptimei1=0.0; //storing process time of inspector 1 for verification purpose
float ptimei2=0.0; //storing process time of inspector 2 for verification purpose
float *ptime1; //storing process time of inspector 1 for verification purpose
float *ptime2; //storing process time of inspector 2 for verification purpose
float *w1_ta; //storing process time of working station 1
float *w2_ta; //storing process time of working station 2
float *w3_ta; //storing process time of working station 2
float i1ta=0, i2ta=0, i1idle=0, i2idle=0, i2type=0;
srand(time(0));
float w1ta=0.0;
float w2ta=0.0;
float w3ta=0.0;
int nc1=0; // number of components C1 used till the current time
int nc2=0; // number of components C2 used till the current time
int nc3=0; // number of components C3 used till the current time
int nw1=0; // number of P1 assembled till the current time
int nw2=0; // number of P2 assembled till the current time
int nw3=0; // number of P3 assembled till the current time
int np1=0; // number of P1 produced till the current time
int np2=0; // number of P2 assembled till the current time
int np3=0; // number of P3 assembled till the current time
int s1=0;  // number of components C1 in the system in the current time
int s2=0;  // number of components C2 in the system in the current time
int s3=0;  // number of components C3 in the system in the current time
int b11=0; // number of components C1 in the buffer 1
int b21=0; // number of components C1 in the buffer 2
int b31=0; // number of components C1 in the buffer 3
int b22=0; // number of components C2 in the buffer 2
int b33=0; // number of components C3 in the buffer 3
float *itime=0.0; // current time interval
float clock=0.0; // simulation clock
float clockin1=0.0; // total of time that C1 enter the system {for verification}
float clockin2=0.0; // total of time that C2 enter the system {for verification}
float clockin3=0.0; // total of time that C3 enter the system {for verification}
float clockoutp1=0.0; // total of time that C1 exit the system {for verification}
float clockoutp2=0.0; // total of time that C2 exit the system {for verification}
float clockoutp3=0.0; // total of time that C3 exit the system {for verification}
float inplant1=0.0; // total time that C1 stay in the system {for verification}
float inplant2=0.0; // total time that C2 stay in the system {for verification}
float inplant3=0.0; // total time that C3 stay in the system {for verification}
int *s;     //Pointer for the counter of components in each system at the current time
int *b;     //Pointer to save the # of components that Inspector 1 send to the buffers
int verification=0;
/*--------------------------------FUNCTION--------------------------------*/
ptime1 = c1+nc1;
i1ta= *ptime1;

if ((int)rand()%2 == 0){
    i2type=2;
/*--------------------------------FUNCTION--------------------------------*/
    ptime2 = c2+nc2;
    i2ta=*ptime2;

} else {
    i2type=3;
/*--------------------------------FUNCTION--------------------------------*/
    ptime2 = c3+nc3;
    i2ta=*ptime2;
}
// Main Part of Program
while ((i1ta >0) || (i2ta >0) || (w1ta >0) || (w2ta >0) || (w3ta >0)) {
/*--------------------------------FUNCTION--------------------------------*/
    clockfcn(i1ta,i2ta,w1ta,w2ta,w3ta,&itime);
    clock+=*itime; // simulation time
    // Compute number of components at current time
/*--------------------------------FUNCTION--------------------------------*/
    s=counters(i1ta,i2ta,w1ta,w2ta,w3ta,b11,b21,b22,b31,b33,i2type);
    // Total of component in the plant at the current time
    s1=s[0];
    s2=s[1];
    s3=s[2];
  // Compute the total process time of components at the current time
    inplant1=inplant1+s1*(*itime);
    inplant2=inplant2+s2*(*itime);
    inplant3=inplant3+s3*(*itime);
// Clock advances to the next event
    i1ta -=*itime;
    i2ta -=*itime;
    w1ta -= *itime;
    w2ta -= *itime;
    w3ta -= *itime;
// The time moment when components are received by inspectors:  // for verification
 if ((i1ta == 0) && (nc1 > 0)){ // total time of the component 1 entering the black box
    clockin1+=clock-ptimei1;
 }
 if ((i2ta == 0) && (i2type == 2) && (nc2>0)){ //total time of the component 2 entering the black box
    clockin2+=clock-ptimei2;
 }
 if ((i2ta == 0) && (i2type == 3) && (nc3>0)) { //total time of the component 3 entering the black box
    clockin3+=clock-ptimei2;
 }
    // When an event Triggers:

    // Event Ins1 triggers:
if ((i1ta <= 0) && ((b11 < 2) || (b21 < 2) || (b31 < 2)) && (nc1 <= (lengthc1-1)) ){ //if the inspector 1 finishes C1 and there is a space in buffers for C1
    b = buffer1(b11,b21,b31,b22,b33,option);
    b11+=b[0];
    b21+=b[1];
    b31+=b[2];
    nc1++; // number of loaded components C1
    if (i1ta < 0) { // compute idle time
        i1idle-= i1ta;
    }
    ptime1 = c1+nc1;
    i1ta= *ptime1;
}//End if case for inspector 1
//This is not a function but it was good to reduce the code
// Event Ins2 can trigger:
int t; // Identifier for type of component
if ((i2type == 2) && (b22 < 2) && (nc2 <= (lengthc2-1))){
    t=2;
} else if((i2type == 3) && (b33 < 2)&& (nc3 <= (lengthc3-1))){
    t=3;
} else{
    t=0;
}

 if ((i2ta <= 0) && (t == 2 || t == 3) && (nc2 <= (lengthc2-1)) ){ // if the component the inspector 2 finishes is 2 or 3
    if (t == 2){ //If it was C2
        b22++;  //Increase C2
    } else{     //If not
        b33++;  //Increase C3
    }
    i2type = ((int)rand()%2)+2; // the type of component that inspector 2 receives to process is randomly generated.
    if (i2ta < 0) { // compute idle time
        i2idle-=i2ta;
    }
    if (i2type == 2) {
        nc2++;
        ptimei2=*(c2+nc2); //loading input from file
        i2ta=ptimei2;
    } else {
        nc3++;
        ptimei2=*(c3+nc3); //loading input from file
        i2ta=ptimei2;
    }

 }

 // Event WS1((float)rand()/(float)RAND_MAX)*range
if (w1ta == 0){
    np1++;
    clockoutp1+=clock; // total time of the components C1 when they go out of the black box as completed products
} else if (w2ta == 0) {
    np2++;
    clockoutp1+=clock; // total time of the components C2 when they go out of the black box as completed products
    clockoutp2+=clock; // total time of the components C3 when they go out of the black box as completed products
} else if (w3ta == 0) {
    np3++;
    clockoutp1+=clock; // total time of the component 1 outing the black box
    clockoutp3+=clock; // total time of the component 3 outing the black box
}

if ((w1ta <=0) && (b11 > 0) && (nw1 <= (lengthw1-1))){
    nw1++;
    b11--;
    if (nw1 <= (lengthw1-1)) {
/*--------------------------------FUNCTION--------------------------------*/
        w1_ta = w1+nw1;
        w1ta= *w1_ta;
    }
} else if ((w2ta <=0) && (b21 >0) && (b22 >0) && (nw2 <= (lengthw2-1))){
    nw2++;
    b21--;
    b22--;
    if (nw2 <= (lengthw2-1)) {
/*--------------------------------FUNCTION--------------------------------*/
        w2_ta = w2+nw2;
        w2ta= *w2_ta;
    }
} else if ((w3ta <=0) && (b31 >0) && (b33 >0) && (nw3 <= (lengthw3-1))) {
    nw3++;
    b31--;
    b33--;
    if (nw3 <= (lengthw3-1)) {
/*--------------------------------FUNCTION--------------------------------*/
        w3_ta = w3+nw3;
        w3ta= *w3_ta;
    }
}

} // End of the main part of the program

// Verification for General Black Box
  // Number of components at the moment
// s1=0;
// s2=0;
// s3=0;
 s=counters(i1ta,i2ta,w1ta,w2ta,w3ta,b11,b21,b22,b31,b33,i2type);
    // Total of component in the plant at the current time
 s1=s[0];
 s2=s[1];
 s3=s[2];
// Total time of components being the black box
float clock1=clockoutp1+s1*clock-clockin1;
float clock2=clockoutp2+s2*clock-clockin2;
float clock3=clockoutp3+s3*clock-clockin3;
// Parameters of Little's Law
// average number of components in the plant
float L1=inplant1/clock;
float L2=inplant2/clock;
float L3=inplant3/clock;
// average time of component in the plant:
float W1=clock1/nc1;
float W2=clock2/nc2;
float W3=clock3/nc3;
// Effective arrival rate
float lambda1=nc1/clock;
float lambda2=nc2/clock;
float lambda3=nc3/clock;
// Expected L_hat:;
float lambda_hat1=L1/W1;
float lambda_hat2=L2/W2;
float lambda_hat3=L3/W3;
// EXPORT the results
// inspector idle time
state->inspector1->idle_time=i1dle;
state->inspector2->idle_time=i2idle;
// number of products
*(state->produced_prod)=np1;
*(state->produced_prod+1)=np2;
*(state->produced_prod+2)=np3;
// number of unused components
*(state->unused_component)=s1;
*(state->unused_component+1)=s2;
*(state->unused_component+2)=s3;
// number of used components:
*(state->used_component)=nc1;
*(state->used_component+1)=nc2;
*(state->used_component+2)=nc3;
// simulation time
*(state->simulation_time)=clock;
// verification
if (((abs(lambda1-lambda_hat1)) < 0.001) && ((abs(lambda2-lambda_hat2)) < 0.001) && ((abs(lambda3-lambda_hat3)) < 0.001)) {
*(state->verification)=1;
}
else {
*(state->verification)=0;
}

if (((abs(lambda1-lambda_hat1)) < 0.001) && ((abs(lambda2-lambda_hat2)) < 0.001) && ((abs(lambda3-lambda_hat3)) < 0.001)) {
verification=1;
}
else {
verification=0;
}

return verification;

}

int work_flow(Config config, State *state, Ptime *ptime){
int verification=1;
for (int loop=1;loop<config.both_models+1;loop++){
    if (config.both_models==2)
    {
        config.model_type=loop;
    }
verification = verification*internal_work_flow(config, &(state+config.model_type-1), &ptime); //fixed
}
return verification;
}
