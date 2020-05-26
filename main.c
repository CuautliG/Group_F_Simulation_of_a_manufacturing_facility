#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
// Import data function
int main()
{
float *c1; // address of processing time C1
float *c2; // address of processing time C2
float *c3; // address of processing time C3
float *w1; // address of processing time P1
float *w2; // address of processing time P2
float *w3; // address of processing time P3
int lengthc1; // number of component C1 supplied for simulation
int lengthc2; // number of component C2 supplied for simulation
int lengthc3; // number of component C3 supplied for simulation
int lengthw1; // number of time intervals for assembling P1 for simulation
int lengthw2; // number of time intervals for assembling P2 for simulation
int lengthw3; // number of time intervals for assembling P3 for simulation
 // Client's choice
int option1=0; // Model choice
while ((option1 != 1) && (option1 != 2)){
puts("Please enter the choice of model you want for the simulation:\n");
puts("1: Your current/old model\n");
puts("2: Our proposed model\n");
scanf("%d",&option1);

if ((option1 != 1) && (option1 != 2)) {
    puts("please type 1 or 2\n");
}
}
int option2=0; // Input choice
float range=0.0;
float uplimit=0.0;
float lolimit=1.0;
while ((option2 != 1) && (option2 != 2)){
puts("Please enter the choice of input method you want for the simulation:\n");
puts("1: Import from your file\n");
puts("2: Inputs (process time) will be generated randomly \n");
scanf("%d",&option2);
if ((option2 != 1) && (option2 != 2)) {
    puts("please type 1 or 2\n");
}
if (option2==2){
    while (uplimit < lolimit) {
    printf("please insert the lower limit of process time: ");
    scanf("%f",&lolimit);
    printf("please insert the upper limit of process time: ");
    scanf("%f",&uplimit);
    range=uplimit-lolimit;
    }
    printf("please enter the number of components of each type for simulation: ");
    int simlength;
    scanf("%d",&simlength);
    lengthc1=simlength;
    lengthc2=simlength;
    lengthc3=simlength;
    lengthw1=simlength;
    lengthw2=simlength;
    lengthw3=simlength;

    } else {
    float array1[5000]; // process time of inspector 1
    float array2[5000]; // process time of inspector 2 for C2
    float array3[5000]; // process time of inspector 2 for C3
    float array4[5000]; // process time of workstation 1
    float array5[5000]; // process time of workstation 2
    float array6[5000]; // process time of workstation 3
    // retrieve data from files
    c1=data(array1,"servinsp1.dat", &lengthc1);
    c2=data(array2,"servinsp22.dat", &lengthc2);
    c3=data(array3,"servinsp23.dat", &lengthc3);
    w1=data(array4,"ws1.dat", &lengthw1);
    w2=data(array5,"ws2.dat", &lengthw2);
    w3=data(array6,"ws3.dat", &lengthw3);
    }
}
//Initial conditions
float ptimei1=0.0; //storing process time of inspector 1 for verification purpose
float ptimei2=0.0; //storing process time of inspector 2 for verification purpose
float *ptime1; //storing process time of inspector 1 for verification purpose
float *ptime2; //storing process time of inspector 2 for verification purpose
float *w1_ta; //storing process time of working station 1
float *w2_ta; //storing process time of working station 2
float *w3_ta; //storing process time of working station 2
struct inspector1 i1 = {.ta=0, .idle=0};
struct inspector2 i2 = {.ta=0, .idle=0};
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
float itime=0.0; // current time interval
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
int b1=0;  // number of components C1 inspector 1 send to the buffer 1
int b2=0;  // number of components C1 inspector 1 send to the buffer 2
int b3=0;  // number of components C1 inspector 1 send to the buffer 3
int *s;     //Pointer for the counter of components in each system at the current time
int *b;     //Pointer to save the # of components that Inspector 1 send to the buffers

/*--------------------------------FUNCTION--------------------------------*/
ptime1 = timingp(c1,option2,nc1,lolimit,range);
i1.ta= *ptime1;

if (rand()%2 == 0){
    i2.type=2;
/*--------------------------------FUNCTION--------------------------------*/

} else {
    i2.type=3;
/*--------------------------------FUNCTION--------------------------------*/
   // ptime2 = timingp(c3,option2,nc3,lolimit,range);
    //i2.ta=*ptime2;
}

ptime2 = timingp(c2,option2,nc2,lolimit,range);
    i2.ta=*ptime2;

// Main Part of Program
while ((i1.ta >0) || (i2.ta >0) || (w1ta >0) || (w2ta >0) || (w3ta >0)) {
/*--------------------------------FUNCTION--------------------------------*/
    itime =clockfcn(i1.ta,i2.ta,w1ta,w2ta,w3ta);
    clock+=itime; // simulation time
    // Compute number of components at current time
/*--------------------------------FUNCTION--------------------------------*/
    s=counters(i1.ta,i2.ta,w1ta,w2ta,w3ta,b11,b21,b22,b31,b33,i2.type);
    // Total of component in the plant at the current time
    s1=s[0];
    s2=s[1];
    s3=s[2];
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
// The time moment when components are received by inspectors:  // for verification
 if ((i1.ta == 0) && (nc1 > 0)){ // total time of the component 1 entering the black box
    clockin1+=clock-ptimei1;
 }
 if ((i2.ta == 0) && (i2.type == 2) && (nc2>0)){ //total time of the component 2 entering the black box
    clockin2+=clock-ptimei2;
 }
 if ((i2.ta == 0) && (i2.type == 3) && (nc3>0)) { //total time of the component 3 entering the black box
    clockin3+=clock-ptimei2;
 }
    // When an event Triggers:

    // Event Ins1 triggers:
if ((i1.ta <= 0) && ((b11 < 2) || (b21 < 2) || (b31 < 2)) && (nc1 <= (lengthc1-1)) ){ //if the inspector 1 finishes C1 and there is a space in buffers for C1
/*--------------------------------FUNCTION--------------------------------*/
    b = buffer1(b11,b21,b31,b22,b33,option1);
    b11+=b[0];
    b21+=b[1];
    b31+=b[2];
    nc1++; // number of loaded components C1
    if (i1.ta < 0) { // compute idle time
        i1.idle-= i1.ta;
    }
/*--------------------------------FUNCTION--------------------------------*/
    ptime1 = timingp(c1,option2,nc1,lolimit,range);
    i1.ta= *ptime1;
}//End if case for inspector 1
//This is not a function but it was good to reduce the code
// Event Ins2 can trigger:
int t; // Identifier for type of component
if ((i2.type == 2) && (b22 < 2) && (nc2 <= (lengthc2-1))){
    t=2;
} else if((i2.type == 3) && (b33 < 2)&& (nc3 <= (lengthc3-1))){
    t=3;
} else{
    t=0;
}

 if ((i2.ta <= 0) && (t == 2 || t == 3) && (nc2 <= (lengthc2-1)) ){ // if the component the inspector 2 finishes is 2 or 3
    if (t == 2){ //If it was C2
        b22++;  //Increase C2
    } else{     //If not
        b33++;  //Increase C3
    }
    i2.type = (rand()%2)+2; // the type of component that inspector 2 receives to process is randomly generated.
    if (i2.ta < 0) { // compute idle time
        i2.idle-=i2.ta;
    }
    if (i2.type == 2) {
        nc2++;
        if (option2==1) {
            ptimei2=*(c2+nc2); //loading input from file
        } else {
            ptimei2=lolimit+((float)rand()/(float)RAND_MAX)*range; //generate random input
        }
        i2.ta=ptimei2;
    } else {
        nc3++;
        if (option2==1) {
            ptimei2=*(c3+nc3); //loading input from file
        } else {
            ptimei2=lolimit+((float)rand()/(float)RAND_MAX)*range; //generate random input
        }
        i2.ta=ptimei2;
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
        w1_ta = timingw(w1,option2,nw1,range);
        w1ta= *w1_ta;
    }
} else if ((w2ta <=0) && (b21 >0) && (b22 >0) && (nw2 <= (lengthw2-1))){
    nw2++;
    b21--;
    b22--;
    if (nw2 <= (lengthw2-1)) {
/*--------------------------------FUNCTION--------------------------------*/
        w2_ta = timingw(w2,option2,nw2,range);
        w2ta= *w2_ta;
    }
} else if ((w3ta <=0) && (b31 >0) && (b33 >0) && (nw3 <= (lengthw3-1))) {
    nw3++;
    b31--;
    b33--;
    if (nw3 <= (lengthw3-1)) {
/*--------------------------------FUNCTION--------------------------------*/
        w3_ta = timingw(w3,option2,nw3,range);
        w3ta= *w3_ta;
    }
}

} // End of the main part of the program

// Verification for General Black Box
  // Number of components at the moment
// s1=0;
// s2=0;
// s3=0;
 s=counters(i1.ta,i2.ta,w1ta,w2ta,w3ta,b11,b21,b22,b31,b33,i2.type);
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
// Print out the results
if ((abs(lambda1-lambda_hat1)) < 0.001) {
    printf("since lambda1 %.4f ~ lambda_hat1 %.4f The process of C1 through the black box is verified by Little's Law\n", lambda1, lambda_hat1);
}
else {
    printf("system is not verified for C1\n");
}
if ((abs(lambda2-lambda_hat2)) < 0.001) {
    printf("since lambda2 %.4f ~ lambda_hat2 %.4f The process of C2 through the black box is verified by Little's Law\n", lambda2, lambda_hat2);
}
else {
    printf("system is not verified for C2\n");
}
if ((abs(lambda3-lambda_hat3)) < 0.001) {
    printf("since lambda3 %.4f ~ lambda_hat3 %.4f The process of C3 through the black box is verified by Little's Law\n", lambda3, lambda_hat3);
}
else {
    printf("system is not verified for C3\n");
}
printf("Number of components of each types ready for the simulation: %d\n",lengthc1);
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
    fprintf(f,"since lambda1 %4f ~ lambda_hat1 %4f The process of C1 through the black box is verified by Little's Law\n", lambda1, lambda_hat1);
}
else {
    fprintf(f,"system is not verified for C1\n");
}
if ((abs(lambda2-lambda_hat2)) < 0.001) {
    fprintf(f,"since lambda2 %4f ~ lambda_hat2 %4f The process of C2 through the black box is verified by Little's Law\n", lambda2, lambda_hat2);
}
else {
    fprintf(f,"system is not verified for C2\n");
}
if ((abs(lambda3-lambda_hat3)) < 0.001) {
    fprintf(f,"since lambda3 %4f ~ lambda_hat3 %4f The process of C3 through the black box is verified by Little's Law\n", lambda3, lambda_hat3);
}
else {
    fprintf(f,"system is not verified for C3\n");
}
fprintf(f,"Number of components of each types ready for the simulation: %d\n",lengthc1);
fprintf(f,"simulation time: %f\n",clock);
fprintf(f,"number of C1 used for simulation: %d\n",nc1);
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
}
