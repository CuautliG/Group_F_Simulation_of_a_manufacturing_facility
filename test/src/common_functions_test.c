#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../include/data_types.h"
#include "../../include/read_config.h"
#include "../../include/read_data.h"
#include "../../include/work_flow.h"
#include "../include/data_types_test.h"
#include "../include/common_functions_test.h"

/* An scenario give you back my_state */
void set_state_test1(struct CONFIG *my_config,struct STATE *my_state){
    char* config_name=      "./data/config.cfg";    // The output directory
    char* input_directory=  "./data/input/";    // The output directory
    read_config(config_name,my_config);
}

void set_state_test2(struct CONFIG *my_config,struct STATE *my_state){
    char* config_name=      "./data/config.cfg";    // The output directory
    char* input_directory=  "./data/input/";    // The output directory
    read_config(config_name,my_config);
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    struct INSPECTOR my_inspector1={.id="1234",.name="PersonOne",.idle_time=0.00};
    struct INSPECTOR my_inspector2={.id="4321",.name="PersonTwo",.idle_time=0.00};
    for (int i=0; i<SIM_STATES; ++i){ //Initialize inspectors in my_state
        (my_state+i)->inspector1=my_inspector1;
        (my_state+i)->inspector2=my_inspector2;
    }
    read_data(input_directory, my_config, my_ptime);
    work_flow(my_config,my_ptime,my_state);
}


struct WORK_FLOW_TEST work_flow_error0(){
    srand(time(0));
    struct WORK_FLOW_TEST work_flow_e0;
/* CONFIG set up*/
    work_flow_e0.my_config.both_models=0;
    work_flow_e0.my_config.lower_limit=10;
    work_flow_e0.my_config.model_type=1;
    work_flow_e0.my_config.read_generate='r';
    work_flow_e0.my_config.sim_length=300;
    work_flow_e0.my_config.upper_limit=20;

/* PTTIME set up*/
    work_flow_e0.my_ptime.comp1=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e0.my_ptime.comp2=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e0.my_ptime.comp3=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e0.my_ptime.ws1=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e0.my_ptime.ws2=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e0.my_ptime.ws3=(float*) malloc(TEST_LENGTH*sizeof(float));
    for (int i=0; i<300;i++)
    {
    *(work_flow_e0.my_ptime.comp1+i)=work_flow_e0.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e0.my_config.upper_limit-work_flow_e0.my_config.lower_limit);
    *(work_flow_e0.my_ptime.comp2+i)=work_flow_e0.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e0.my_config.upper_limit-work_flow_e0.my_config.lower_limit);
    *(work_flow_e0.my_ptime.comp3+i)=work_flow_e0.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e0.my_config.upper_limit-work_flow_e0.my_config.lower_limit);
    *(work_flow_e0.my_ptime.ws1+i)=work_flow_e0.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e0.my_config.upper_limit-work_flow_e0.my_config.lower_limit);
    *(work_flow_e0.my_ptime.ws2+i)=work_flow_e0.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e0.my_config.upper_limit-work_flow_e0.my_config.lower_limit);
    *(work_flow_e0.my_ptime.ws3+i)=work_flow_e0.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e0.my_config.upper_limit-work_flow_e0.my_config.lower_limit);
    }
    return work_flow_e0;
}

struct WORK_FLOW_TEST work_flow_error1(){
    srand(time(0));
    struct WORK_FLOW_TEST work_flow_e1;
/* CONFIG set up*/
    work_flow_e1.my_config.both_models=0;
    work_flow_e1.my_config.lower_limit=10;
    work_flow_e1.my_config.model_type=5;    /*error*/
    work_flow_e1.my_config.read_generate='r';
    work_flow_e1.my_config.sim_length=-100; /*error*/
    work_flow_e1.my_config.upper_limit=20;

/* PTTIME set up*/
    work_flow_e1.my_ptime.comp1=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e1.my_ptime.comp2=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e1.my_ptime.comp3=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e1.my_ptime.ws1=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e1.my_ptime.ws2=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e1.my_ptime.ws3=(float*) malloc(TEST_LENGTH*sizeof(float));
    for (int i=0; i<300;i++)
    {
    *(work_flow_e1.my_ptime.comp1+i)=work_flow_e1.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e1.my_config.upper_limit-work_flow_e1.my_config.lower_limit);
    *(work_flow_e1.my_ptime.comp2+i)=work_flow_e1.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e1.my_config.upper_limit-work_flow_e1.my_config.lower_limit);
    *(work_flow_e1.my_ptime.comp3+i)=work_flow_e1.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e1.my_config.upper_limit-work_flow_e1.my_config.lower_limit);
    *(work_flow_e1.my_ptime.ws1+i)=work_flow_e1.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e1.my_config.upper_limit-work_flow_e1.my_config.lower_limit);
    *(work_flow_e1.my_ptime.ws2+i)=work_flow_e1.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e1.my_config.upper_limit-work_flow_e1.my_config.lower_limit);
    *(work_flow_e1.my_ptime.ws3+i)=work_flow_e1.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e1.my_config.upper_limit-work_flow_e1.my_config.lower_limit);
    }
    return work_flow_e1;
}

struct WORK_FLOW_TEST work_flow_error2(){
    srand(time(0));
    struct WORK_FLOW_TEST work_flow_e2;
/* CONFIG set up*/
    work_flow_e2.my_config.both_models=0;
    work_flow_e2.my_config.lower_limit=10;
    work_flow_e2.my_config.model_type=1;
    work_flow_e2.my_config.read_generate='r';
    work_flow_e2.my_config.sim_length=300;
    work_flow_e2.my_config.upper_limit=20;

/* PTTIME set up*/
    work_flow_e2.my_ptime.comp1=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e2.my_ptime.comp2=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e2.my_ptime.comp3=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e2.my_ptime.ws1=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e2.my_ptime.ws2=(float*) malloc(TEST_LENGTH*sizeof(float));
    work_flow_e2.my_ptime.ws3=(float*) malloc(TEST_LENGTH*sizeof(float));
    for (int i=0; i<300;i++){
    *(work_flow_e2.my_ptime.comp1+i)=work_flow_e2.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e2.my_config.upper_limit-work_flow_e2.my_config.lower_limit);
    *(work_flow_e2.my_ptime.comp2+i)=work_flow_e2.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e2.my_config.upper_limit-work_flow_e2.my_config.lower_limit);
    *(work_flow_e2.my_ptime.comp3+i)=work_flow_e2.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e2.my_config.upper_limit-work_flow_e2.my_config.lower_limit);
    *(work_flow_e2.my_ptime.ws1+i)=work_flow_e2.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e2.my_config.upper_limit-work_flow_e2.my_config.lower_limit);
    *(work_flow_e2.my_ptime.ws2+i)=work_flow_e2.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e2.my_config.upper_limit-work_flow_e2.my_config.lower_limit);
    *(work_flow_e2.my_ptime.ws3+i)=work_flow_e2.my_config.lower_limit+(float)rand()/(float)RAND_MAX*(work_flow_e2.my_config.upper_limit-work_flow_e2.my_config.lower_limit);
    }
    *(work_flow_e2.my_ptime.comp1+10)=0; /*error*/
    return work_flow_e2;
}

struct CLOCKFCN_TEST work_flow_error3(){
    struct CLOCKFCN_TEST work_flow_e3;
    work_flow_e3.input_1=0.0;
    work_flow_e3.input_2=-1.0;
    work_flow_e3.input_3=-1.0;
    work_flow_e3.input_4=-1.0;
    work_flow_e3.input_5=-1.0;
    return work_flow_e3;
}

struct COUNTERS_TEST work_flow_error4(){
    struct COUNTERS_TEST work_flow_e4;
    work_flow_e4.internal_process_time=NULL; /*error*/
    work_flow_e4.c1_in_buffer[0]=0;
    work_flow_e4.c1_in_buffer[1]=-1; /*error*/
    work_flow_e4.c1_in_buffer[2]=-2; /*error*/
    work_flow_e4.c2_in_buffer2=0;
    work_flow_e4.c3_in_buffer3=0;
    work_flow_e4.comp_type_kept_by_insp2=0; /*error*/
    return work_flow_e4;
}

struct BUFFER1_TEST work_flow_error5(){
    struct BUFFER1_TEST work_flow_e5;
    work_flow_e5.c1_in_buffer[0]=1;
    work_flow_e5.c1_in_buffer[1]=-1; /*error*/
    work_flow_e5.c1_in_buffer[2]=-1; /*error*/
    work_flow_e5.c2_in_buffer2=0;
    work_flow_e5.c3_in_buffer3=0;
    work_flow_e5.model_type=6; /*error*/
    return work_flow_e5;
}
