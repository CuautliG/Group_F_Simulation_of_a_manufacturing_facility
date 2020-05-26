#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Import data function

float *data(float *c, char STR[20]){
FILE *ins= fopen(STR,"r");
int i =0;
char oneline[8];
while (!feof(ins)) {
    fscanf(ins,"%8s",oneline);
    c[i]=strtof(oneline,NULL);
    i++;
}
fclose(ins);
return c;
}
// Create type of inspectors to calculate store the time processing, the idle/blocked time, and the type of component that inspector 2 currently works on
struct inspector1 {
    float ta;
    float idle;
    };
struct inspector2{
    float ta;
    float idle;
    int type;
    };


int main()
{
//Loading inputs
float array1[300]; // process time of inspector 1
float array2[300]; // process time of inspector 2 for C2
float array3[300]; // process time of inspector 2 for C3
float array4[300]; // process time of workstation 1
float array5[300]; // process time of workstation 2
float array6[300]; // process time of workstation 3
    // retrieve data from files
float *c1=data(array1,"servinsp1.dat");
float *c2=data(array2,"servinsp22.dat");
float *c3=data(array3,"servinsp23.dat");
float *w1=data(array4,"ws1.dat");
float *w2=data(array5,"ws2.dat");
float *w3=data(array6,"ws3.dat");
//Initial conditions

struct inspector1 i1 = {.ta=0, .idle=0};
struct inspector2 i2 = {.ta=0, .idle=0};

i1.ta=*c1;
i2.ta=*c2;
srand(time(0));
if (rand()%2 == 0){
    i2.type=2;
}
else {
    i2.type=3;
}
float w1ta=0.0;
float w2ta=0.0;
float w3ta=0.0;
int simlength=sizeof(array1)/sizeof(array1[0]);
int nc1=0;
int nc2=0;
int nc3=0;
int nw1=0;
int nw2=0;
int nw3=0;
int np1=0;
int np2=0;
int np3=0;
int s1=0;
int s2=0;
int s3=0;
int b11=0;
int b21=0;
int b31=0;
int b22=0;
int b33=0;
float itime=0.0;
float clock=0.0;
float clockin1=0.0; // for verification
float clockin2=0.0; // for verification
float clockin3=0.0; // for verification
float clockoutp1=0.0; // for verification
float clockoutp2=0.0; // for verification
float clockoutp3=0.0; // for verification
float inplant1=0.0; // for verification
float inplant2=0.0; // for verification
float inplant3=0.0; // for verification
int b1=0;
int b2=0;
int b3=0;

// Main Part of Program
while ((i1.ta >0) || (i2.ta >0) || (w1ta >0) || (w2ta >0) || (w3ta >0)) {
    if (i1.ta >0){
        itime=i1.ta;
    }
    if ((i2.ta > 0) && (itime > i2.ta)){
        itime=i2.ta;
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
    clock+=itime; // simulation time
// Compute number of components at current time

    // compute number of components being processed or kept by inspectors
    s1=0;
    s2=0;
    s3=0;
    if ((i1.ta > 0) || ((b11==2) && (b21==2)&&(b31==2))){
    s1++;
    }
    if (((i2.ta >0) || (b22==2))&& (i2.type == 2)) {
     s2++;
    }
    if (((i2.ta >0) || (b33==2))&& (i2.type == 3)) {
     s3++;
    }
    // compute number of component being processed by workstations
    if (w1ta > 0) {
     s1++;
    }
    if (w2ta > 0) {
     s1++;
     s2++;
    }
    if (w3ta > 0) {
    s1++;
    s3++;
    }
    // Total of component in the plant at the current time
    s1+=b11+b21+b31;
    s2+=b22;
    s3+=b33;
  // Compute the total process time of components at the current time
 inplant1=inplant1+s1*itime;
 inplant2=inplant2+s2*itime;
 inplant3=inplant3+s3*itime;
// Clock advances to the next event
 i1.ta -=itime;
 i2.ta -=itime;
 w1ta -= itime;
 w2ta -= itime;
 w3ta -= itime;
    // The time moment when components are recieved by inspectors:  // for verification
 if ((i1.ta == 0) && (nc1 > 0)){ // total time of the component 1 entering the black box
   clockin1+=clock-*(c1+nc1);
 }
 if ((i2.ta == 0) && (i2.type == 2) && (nc2>0)){ //total time of the component 2 entering the black box
   clockin2+=clock-*(c2+nc2);
 }
 if ((i2.ta == 0) && (i2.type == 3) && (nc3>0)) { //total time of the component 3 entering the black box
   clockin3+=clock-*(c3+nc3);
 }
    // When an event Triggers:
    // Event Ins1 triggers:

if ((i1.ta <= 0) && ((b11 < 2) || (b21 < 2) || (b31 < 2)) && (nc1 <= (simlength-1))){ //if the inspector 1 finishes C1 and there is a space in buffers for C1
   if  (((b21 < 1) && (b22 > 0)) || ((b21<2) && (b11 == 2))) { // if B2 has C2 ready then priority goes to B2
       b1 = 0;
       b2 = 1;
       b3 = 0;
       }
    else if (((b31 < 1) && (b33 > 0)) || ((b31 < 2) && (b21 == 2))) { // if B3 has C3 ready then priority goes to B3
           b1 = 0;
           b2 = 0;
           b3 = 1;
           }
          else { // if B2, B3 has no C2, C3 ready, the priority goes to B1
           b1 = 1; b2 = 0; b3 = 0;
          }
   b11=b11+b1;
   b21=b21+b2;
   b31=b31+b3;
   b1=0;
   b2=0;
   b3=0;
   if (i1.ta < 0) { // compute idle time
       i1.idle-= i1.ta;
   }
   nc1++; // number of loaded components C1
   if (nc1 <= (simlength-1)) {
       i1.ta=*(c1+nc1);
   }
}
    // Event Ins2 triggers:
 if ((i2.ta <= 0) && (i2.type == 2) && (b22 < 2)){ // if the component the inspector 2 finishes processing is C2
    b22++;
    if (i2.ta < 0) {
        i2.idle-=i2.ta;
    }
    i2.type = rand()%2+2; // the type of component that inspector 2 receives to process is randomly generated.
    if (i2.type == 2) {
        nc2++;
        i2.ta=*(c2+nc2);
    }
    if (i2.type == 3) {
        nc3++;
        i2.ta=*(c3+nc3);
    }
 }

 if ((i2.ta <= 0) && (i2.type == 3) && (b33 < 2)) { // if the component the inspector 2 finishes processing is C3
    b33++;
    if (i2.ta < 0) {
        i2.idle= i2.idle-i2.ta;
    }

    i2.type = (rand()%2)+2;
    if (i2.type == 2) {
        nc2++ ;
        i2.ta=*(c2+nc2);
    }
    if (i2.type == 3) {
        nc3++;
        i2.ta=*(c3+nc3);
    }
 }

 // Event WS1
 if (w1ta == 0){
    np1++;
    clockoutp1+=clock; // total time of the components C1 when they go out of the black box as completed products
    }
 if (w2ta == 0) {
    np2++;
    clockoutp1+=clock; // total time of the components C2 when they go out of the black box as completed products
    clockoutp2+=clock; // total time of the components C3 when they go out of the black box as completed products
    }
 if (w3ta == 0) {
    np3++;
    clockoutp1+=clock; // total time of the component 1 outing the black box
    clockoutp3+=clock; // total time of the component 3 outing the black box
    }
 if ((w1ta <=0) && (b11 > 0)){
    nw1++;
    b11--;
    w1ta = *(w1+nw1);
    }
 if ((w2ta <=0) && (b21 >0) && (b22 >0)){
    nw2++;
    b21--;
    b22--;
    w2ta=*(w2+nw2);
    }
 if ((w3ta <=0) && (b31 >0) && (b33 >0)) {
    nw3++;
    b31--;
    b33--;
    w3ta = *(w3+nw3);
    }
 }
// Verification for General Black Box
  // Number of components at the moment
 s1=0;
 s2=0;
 s3=0;
 if ((i1.ta > 0) || ((b11==2) && (b21==2)&&(b31==2))){
    s1++;
    }
 if (((i2.ta >0) || (b22==2))&& (i2.type == 2)) {
     s2++;
    }
 if (((i2.ta >0) || (b33==2))&& (i2.type == 3)) {
     s3++;
    }
    // compute number of component being processed by workstations
 if (w1ta > 0) {
     s1++;
    }
 if (w2ta > 0) {
     s1++;
     s2++;
    }
 if (w3ta > 0) {
    s1++;
    s3++;
    }
    // Total of component in the plant at the current time
 s1+=b11+b21+b31;
 s2+=b22;
 s3+=b33;
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
// Print out the results
if ((abs(lambda1-lambda_hat1)) < 0.001) {
    printf("since lambda1 %4f = lambda_hat1 %4f The process of C1 through the black box is verified by Little's Law\n", lambda1, lambda_hat1);
}
else {
    printf("system is not verified for C1\n");
}
if ((abs(lambda2-lambda_hat2)) < 0.001) {
    printf("since lambda2 %4f = lambda_hat2 %4f The process of C2 through the black box is verified by Little's Law\n", lambda2, lambda_hat2);
}
else {
    printf("system is not verified for C2\n");
}
if ((abs(lambda3-lambda_hat3)) < 0.001) {
    printf("since lambda3 %4f = lambda_hat3 %4f The process of C3 through the black box is verified by Little's Law\n", lambda3, lambda_hat3);
}
else {
    printf("system is not verified for C3\n");
}
printf("Number of components of each types ready for the simulation: %d\n",simlength);
printf("simulation time: %f\n",clock);
printf("number of C1 used for simulation: %d\n",nc1);
printf("number of C2 used for simulation: %d\n",nc2);
printf("number of C3 used for simulation: %d\n",nc3);
printf("number of P1: %d\n",np1);
printf("number of P2: %d\n",np2);
printf("number of P3: %d\n",np3);
printf("average number of P1 per minute: %f\n",np1/clock);
printf("average number of P2 per minute: %f\n",np2/clock);
printf("average number of P3 per minute: %f\n",np3/clock);
float idleness1=i1.idle/clock;
float idleness2=i2.idle/clock;
printf("idleness of inspector 1: %f\n",idleness1);
printf("idleness of inspector 2: %f\n",idleness2);
FILE *f;
f=fopen("results.csv","w");
if ((abs(lambda1-lambda_hat1)) < 0.001) {
    fprintf(f,"since lambda1 %4f = lambda_hat1 %4f The process of C1 through the black box is verified by Little's Law\n", lambda1, lambda_hat1);
}
else {
    fprintf(f,"system is not verified for C1\n");
}
if ((abs(lambda2-lambda_hat2)) < 0.001) {
    fprintf(f,"since lambda2 %4f = lambda_hat2 %4f The process of C2 through the black box is verified by Little's Law\n", lambda2, lambda_hat2);
}
else {
    fprintf(f,"system is not verified for C2\n");
}
if ((abs(lambda3-lambda_hat3)) < 0.001) {
    fprintf(f,"since lambda3 %4f = lambda_hat3 %4f The process of C3 through the black box is verified by Little's Law\n", lambda3, lambda_hat3);
}
else {
    fprintf(f,"system is not verified for C3\n");
}
fprintf(f,"Number of components of each types ready for the simulation: %d\n",simlength);
fprintf(f,"simulation time: %f\n",clock);
fprintf(f,"Number of C1 used for simulation: %d\n",nc1);
fprintf(f,"number of C2 used for simulation: %d\n",nc2);
fprintf(f,"number of C3 used for simulation: %d\n",nc3);
fprintf(f,"number of P1: %d\n",np1);
fprintf(f,"number of P2: %d\n",np2);
fprintf(f,"number of P3: %d\n",np3);
fprintf(f,"average number of P1 per minute: %f\n",np1/clock);
fprintf(f,"average number of P2 per minute: %f\n",np2/clock);
fprintf(f,"average number of P3 per minute: %f\n",np3/clock);
fprintf(f,"idleness of inspector 1: %f\n", idleness1);
fprintf(f,"idleness of inspector 2: %f\n", idleness2);
fclose(f);
return 0;
    // your code here
}

