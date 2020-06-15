#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "../include/read_data.h"

//int read_data(*char input_directory, char *config_file, struct **my_ptime)

int lengthc1; // number of component C1 supplied for simulation
int lengthc2; // number of component C2 supplied for simulation
int lengthc3; // number of component C3 supplied for simulation
int lengthw1; // number of time intervals for assembling P1 for simulation
int lengthw2; // number of time intervals for assembling P2 for simulation
int lengthw3; // number of time intervals for assembling P3 for simulation

int read_client_files()
{
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

    float *c1; // address of processing time C1
    float *c2; // address of processing time C2
    float *c3; // address of processing time C3
    float *w1; // address of processing time P1
    float *w2; // address of processing time P2
    float *w3; // address of processing time P3

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

int main()
{
    read_client_files();
}
