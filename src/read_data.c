#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/read_data.h"

int read_data(char *input_directory, struct CONFIG my_config, struct PTIME *my_ptime){
    printf("Input directory: %s\n",input_directory);
    printf("Model type: %d\n",my_config.model_type);

int lengthc1; // number of component C1 supplied for simulation
int lengthc2; // number of component C2 supplied for simulation
int lengthc3; // number of component C3 supplied for simulation
int lengthw1; // number of time intervals for assembling P1 for simulation
int lengthw2; // number of time intervals for assembling P2 for simulation
int lengthw3; // number of time intervals for assembling P3 for simulation

int simlength = my_config.sim_length;
if (my_config.read_generate == 'r')
{

    float array1[5000]; // process time of inspector 1
    float array2[5000]; // process time of inspector 2 for C2
    float array3[5000]; // process time of inspector 2 for C3
    float array4[5000]; // process time of workstation 1
    float array5[5000]; // process time of workstation 2
    float array6[5000]; // process time of workstation 3

    char long_str[6][23];
    char* input_directory=  "./data/input/";
    char* components[] = {"ser1.dat", "ser2.dat", "ser3.dat", "ws1.dat", "ws2.dat", "ws3.dat"};

    for (int i=0; i<6; i++)
    {
    strncat(long_str[i], input_directory, 13);
    strncat(long_str[i], components[i], 20);
    }
    // retrieve data from files
    my_ptime.comp1=data(array1,long_str[0], &lengthc1);
    my_ptime.comp2=data(array2,long_str[1], &lengthc2);
    my_ptime.comp3=data(array3,long_str[2], &lengthc3);
    my_ptime.ws1=data(array4,long_str[3], &lengthw1);
    my_ptime.ws2=data(array5,long_str[4], &lengthw2);
    my_ptime.ws3=data(array6,long_str[5], &lengthw3);
}

else if (my_config.read_generate == 'g')
        {
        my_ptime.comp1 = generate_random;
        my_ptime.comp2 = generate_random;
        my_ptime.comp3 = generate_random;
        my_ptime.ws1 = generate_random;
        my_ptime.ws2 = generate_random;
        my_ptime.ws3 = generate_random;
    }
}

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

float generate_random()
{
    float upper = my_config.uplimit;
    float lower = my_config.lolimit;
    float ran_num_generator;
    float rand_numb [simlength];
    for(int i = 0; i<simlength; i++)
    {
    ran_num_generator = lower + (float)rand() / (RAND_MAX / (upper - lower + 1) + 1);
    rand_numb[i] = ran_num_generator;
    }
}
