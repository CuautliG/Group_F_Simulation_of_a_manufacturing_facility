#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "../../include/data_types.h"
#include "../../include/work_flow.h"
#include "../include/data_types_test.h"
#include "../include/common_functions_test.h"
#include "../include/work_flow_test.h"

int work_flow_test(){
    /*error 1 simulation*/
    struct WORK_FLOW_TEST error1_sim;
    error1_sim=work_flow_error1();
    printf("Error -1 :\n");
    int error1=work_flow(&(error1_sim.my_config),&(error1_sim.my_ptime),&(error1_sim.my_state));
    printf("Return value from work_flow() was %d\n\n",error1);

    /*error 2 simulation*/
    struct WORK_FLOW_TEST error2_sim;
    error2_sim=work_flow_error2();
    printf("Error -2 :\n");
    int error2=work_flow(&(error2_sim.my_config),&(error2_sim.my_ptime),&(error2_sim.my_state));
    printf("Return value from work_flow() was %d\n\n",error2);

    /*error 3 simulation*/
    struct CLOCKFCN_TEST error3_sim;
    error3_sim=work_flow_error3();
    printf("Error -3 :\n");
    float error3=clockfcn(error3_sim.input_1,error3_sim.input_2,error3_sim.input_3,error3_sim.input_4,error3_sim.input_5);
    if (error3==0) {
        printf("Return value from clockfcn() was NULL but work_flow() returns -3 \n\n");
    }
    /*error 4 simulation*/
    struct COUNTERS_TEST error4_sim;
    error4_sim=work_flow_error4();
    printf("Error -4 :\n");
    int *error4=counters(error4_sim.internal_process_time,error4_sim.c1_in_buffer,error4_sim.c2_in_buffer2,error4_sim.c3_in_buffer3,error4_sim.comp_type_kept_by_insp2);
    if (error4==NULL) {
        printf("Return value from counters() was NULL but work_flow() returns -4 \n\n");
    }
    /*error 5 simulation*/
    struct BUFFER1_TEST error5_sim;
    error5_sim=work_flow_error5();
    printf("Error -5 :\n");
    int *error5=buffer1(error5_sim.c1_in_buffer,error5_sim.c2_in_buffer2,error5_sim.c3_in_buffer3,error5_sim.model_type);
    if (error5==NULL) {
        printf("Return value from buffer1() was NULL but work_flow() returns -5 \n\n");
    }
    /*error 0 simulation*/
    struct WORK_FLOW_TEST error0_sim;
    error0_sim=work_flow_error0();
    printf("No errors : \n");
    int error0=work_flow(&(error0_sim.my_config),&(error0_sim.my_ptime),&(error0_sim.my_state));
    printf("Return value from work_flow() was %d\n\n",error0);

    return 0;
}
