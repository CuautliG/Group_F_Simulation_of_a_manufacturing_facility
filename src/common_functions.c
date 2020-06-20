#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data_types.h"
#include "../include/common_functions.h"

void print_state(struct STATE *my_state){
    printf("------------- SIMULATION REPORT FOR MODEL %d -------------\n",my_state->model_type);
    printf("Number of components of each types ready for the simulation: %d\n",my_state->sim_length);
    printf("Simulation time: %f\n",my_state->clock);
    printf("Number of C1 used for simulation: %d\n",my_state->used_component[0]);
    printf("Number of C2 used for simulation: %d\n",my_state->used_component[1]);
    printf("Number of C3 used for simulation: %d\n",my_state->used_component[2]);
    printf("Number of C1 unused for simulation: %d\n",my_state->unused_component[0]);
    printf("Number of C2 unused for simulation: %d\n",my_state->unused_component[1]);
    printf("Number of C3 unused for simulation: %d\n",my_state->unused_component[2]);
    printf("Number of produced P1: %d\n",my_state->produced_prod[0]);
    printf("Number of produced P2: %d\n",my_state->produced_prod[1]);
    printf("Number of produced P3: %d\n",my_state->produced_prod[2]);
    printf("Average number of P1 per minute: %f\n",my_state->produced_prod[0]/my_state->clock);
    printf("Average number of P2 per minute: %f\n",my_state->produced_prod[1]/my_state->clock);
    printf("Average number of P3 per minute: %f\n",my_state->produced_prod[2]/my_state->clock);
    printf("Idleness of inspector 1: %f min\n", my_state->inspector1.idle_time/my_state->clock);
    printf("Idleness of inspector 2: %f min\n", my_state->inspector2.idle_time/my_state->clock);
}

void print_ptime(struct CONFIG *my_config, struct PTIME *my_ptime){
    for (int i=0; i<my_config->sim_length; i++){
        printf("ptime c1 is: %f\n",my_ptime->comp1[i]);
        printf("ptime c2 is: %f\n",my_ptime->comp2[i]);
        printf("ptime c3 is: %f\n",my_ptime->comp3[i]);
        printf("ptime ws1 is: %f\n",my_ptime->ws1[i]);
        printf("ptime ws2 is: %f\n",my_ptime->ws2[i]);
        printf("ptime ws3 is: %f\n",my_ptime->ws3[i]);
    }
}

void print_config(struct CONFIG *my_config){
    printf("both_models, %d\n", my_config->both_models);
    printf("model_type, %d\n", my_config->model_type);
    printf("read_generate, %c\n",my_config->read_generate);
    printf("sim_length, %d\n",my_config->sim_length);
    printf("lo_limit, %f\n", my_config->lower_limit);
    printf("up_limit, %f\n", my_config->upper_limit);
}

