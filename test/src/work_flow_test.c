#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "../include/data_types_test.h"
#include "../include/work_flow_test.h"

/** \brief Function to find the minimum positive float number among 5 inputs. \n
 * This function is used to find the time interval from the current time to the event. If the output is not satisfied the function's purpose the error message will appear
 * \param[in] input_1 - float number.
 * \param[in] input_2 - float number.
 * \param[in] input_3 - float number.
 * \param[in] input_4 - float number.
 * \param[in] input_5 - float number.
 * \return the minimum positive float number of 5 inputs.
 */
float clockfcn(float input_1, float input_2, float input_3, float input_4, float input_5){
    float internal_process_time=FLT_MAX;
    if ((input_1<=0)&&(input_2<=0)&&(input_3<=0)&&(input_4<=0)&&(input_5<=0)){ /*precondition test - every input must positive)*/
        return 0;
    }
    if (input_1 >0){
        internal_process_time=input_1;
    }
    if ((input_2 > 0) && (internal_process_time > input_2)){
        internal_process_time=input_2;
    }
    if ((input_3  > 0) && (internal_process_time > input_3)) {
        internal_process_time=input_3;
    }
    if ((input_4  > 0) && (internal_process_time > input_4)){
        internal_process_time=input_4;
    }
    if ((input_5 > 0) && (internal_process_time > input_5)){
        internal_process_time=input_5;

    }
/* postcondition testing - test if the output is truly the minimum positive number*/
if (((input_1>0)&&(internal_process_time > input_1)) || ((input_2>0)&&(internal_process_time > input_2)) || ((input_3>0)&&(internal_process_time > input_3)) || ((input_4>0)&&(internal_process_time > input_4)) || ((input_5>0)&&(internal_process_time > input_5)) )
    {
        puts("Error 2 in clockfcn: the function doesn't work properly \n");
        return 0;
    }
    else {
        return internal_process_time;
    }

}
/** \brief Function to find the number of components of each type currently in the system. \n
 * This result of this function is used to calculate the total time of components staying in the system for verification purpose.
 * \param[in] internal_process_time - array of 5: the internal process time of inspector 1, inspector 2, workstation 1,workstation 2,workstation 3
 * \param[in] c1_in_buffer - array of 3: number of component c1 in buffer 1, buffer 2, buffer 3
 * \param[in] c2_in_buffer2 - number of component c2 in buffer 2
 * \param[in] c3_in_buffer3 - number of component c3 in buffer 3
 * \param[in] comp_type_kept_by_insp2 - type of component kept by inspector 2
 * \return num_of_c_in_sys - the number of components of each in the system.
 */
int *counters(float *internal_process_time,int *c1_in_buffer, int c2_in_buffer2,int c3_in_buffer3,int comp_type_kept_by_insp2){
    /*precondition test: the pointer address must be valid; there is no negative value in components; the component type kept by inspector 2 is irrelevant*/
    if ((internal_process_time==NULL) ||  (c1_in_buffer==NULL)){
        return NULL;
    }
    if ((c1_in_buffer[0]<0) || (c1_in_buffer[1]<0) || (c1_in_buffer[2]<0) || (c2_in_buffer2<0) || (c3_in_buffer3<0) || (comp_type_kept_by_insp2<2)||(comp_type_kept_by_insp2>3)){
        return NULL;
    }

    int static num_of_c_in_sys[]={0,0,0};
    /* number of components kept by inspectors*/
    if ((internal_process_time[0] > 0) || ((c1_in_buffer[0]==2) && (c1_in_buffer[1]==2)&&(c1_in_buffer[2]==2))){
        num_of_c_in_sys[0]++;
    }
    if ((internal_process_time[1] >0) || ((c2_in_buffer2==2)&& (comp_type_kept_by_insp2 == 2))) {
        num_of_c_in_sys[1]++;
    }
    if((internal_process_time[1] >0) || ((c3_in_buffer3==2)&& (comp_type_kept_by_insp2 == 3))) {
        num_of_c_in_sys[2]++;
    }
    /* number of components being processed by workstations*/
    if (internal_process_time[2] > 0) {
        num_of_c_in_sys[0]++;
    }
    if(internal_process_time[3] > 0) {
        num_of_c_in_sys[0]++;
        num_of_c_in_sys[1]++;
    }
    if(internal_process_time[4] > 0) {
        num_of_c_in_sys[0]++;
        num_of_c_in_sys[2]++;
    }
    /*number of components in buffer*/
    num_of_c_in_sys[0]+=c1_in_buffer[0]+c1_in_buffer[1]+c1_in_buffer[2];
    num_of_c_in_sys[1]+=c2_in_buffer2;
    num_of_c_in_sys[2]+=c3_in_buffer3;

    /*post condition test - output must be non-negative and less than MAX_SIMULATION_LENGTH*/
    if ((num_of_c_in_sys[0] <0)||(num_of_c_in_sys[1] <0)||(num_of_c_in_sys[2] <0)||(num_of_c_in_sys[0] >MAX_SIMULATION_LENGTH)||(num_of_c_in_sys[1] >MAX_SIMULATION_LENGTH)||(num_of_c_in_sys[2] >MAX_SIMULATION_LENGTH))
    {
        return NULL;
    }
    else {
        return num_of_c_in_sys;
    }
}
/** \brief Function to send a fully processed component C1 from inspector 1 to the Buffer in respect of the model type and the current states of the Buffers. \n
 * \param[in] c1_in_buffer - array of 5: the internal process time of inspector 1, inspector 2, workstation 1,workstation 2,workstation 3
 * \param[in] c2_in_buffer2 - number of components C2 in Buffer 2.
 * \param[in] c3_in_buffer3 - number of components C3 in Buffer 3.
 * \param[in] model_type - model type.
 * \return buffer - the number of component C1 sent to each Buffer (0: if not sent, 1: if sent)
 */
int *buffer1(int *c1_in_buffer,int c2_in_buffer2, int c3_in_buffer3, int model_type){
    /* precondition test: the input must be non-negative, the number of component in buffer is not higher than 2, the model_type is either 1 or 2*/
    if (c1_in_buffer==NULL) {
        return NULL;
    }
    if ((c1_in_buffer[0]<0)||(c1_in_buffer[1]<0)||(c1_in_buffer[2]<0)||(c2_in_buffer2<0)||(c3_in_buffer3<0)){
        return NULL;
    }
    if ((c1_in_buffer[0]>2)||(c1_in_buffer[1]>2)||(c1_in_buffer[2]>2)||(c2_in_buffer2>2)||(c3_in_buffer3>2)){
        return NULL;
    }
    if ((model_type<0) ||(model_type>2)){
        return NULL;
    }

    int static buffer[]={0,0,0};
    /* transfer the C1 from inspector 1 to Buffer in respect of model type 1 - the old model*/
    if (model_type==1){
        if (c1_in_buffer[0] < 2) {
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 0;
        } else if (c1_in_buffer[1] < 2) { /* if B2, B3 has no C2, C3 ready, the priority goes to B1*/
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 0;
        } else {
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 1;
        }
    }/*End  mod_type 1*/
    /* transfer the C1 from inspector 1 to Buffer in respect of model type 2 - the proposed model*/
    else {
        if  (((c1_in_buffer[1] < 1) && (c2_in_buffer2 > 0)) || ((c1_in_buffer[1]<2) && (c1_in_buffer[0] == 2))) { /* if B2 has C2 ready then priority goes to B2*/
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 0;
        } else if (((c1_in_buffer[2] < 1) && (c3_in_buffer3 > 0)) || ((c1_in_buffer[2] < 2) && (c1_in_buffer[1] == 2))) { /* if B3 has C3 ready then priority goes to B3*/
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 1;
        } else { /* if B2, B3 has no C2, C3 ready, the priority goes to B1*/
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 0;
        }
    } /*End mod_type 2*/
    /*postcondition test: output must be either 0 or 1*/
    if ((buffer[0]<0)||(buffer[1]<0)||(buffer[2]<0)){
        return NULL;
    }
    if ((buffer[0]>1)||(buffer[1]>1)||(buffer[2]>1)){
        return NULL;
    }
    return buffer;
}
/** \brief Based on the given configuration and input data, Function to simulate the work flow of the manufacturing facility, and produce the the simulation results. \n
*  The simulation results consists of: the simulation time, the number of components used and not used for the simulation, the number of products assembled,
*the idle time of inspectors. The function also performs the Little's Law verification to check the credibility of the simulation.
*the function proceed the input and configuration data and produce the result through the pointer my_state. The return value is 0 if the function is executed well and verified,
 and 1 if the function is not executed well and not verified.
 * \param[in] my_config system configuration
 * \param[in] my_ptime process time of inspectors
 * \param[in] my_state states of the system
 * \return 0 if an error occurred during the execution, 1 if the function works properly.
 */
int work_flow(struct CONFIG *my_config,struct PTIME *my_ptime, struct STATE *my_state){
    /*precondition test all address pointers must be valid*/
    if (my_config==NULL)
    {
        return 1;
    }

    if ((my_config->sim_length<=0)||(my_config->sim_length>MAX_SIMULATION_LENGTH))
    {
        return 1;
    }
    if ((my_config->both_models<0)||(my_config->both_models>1))
    {
        return 1;
    }
    if ((my_config->model_type<1)||(my_config->both_models>2))
    {
        return 1;
    }
    if ((my_config->sim_length<0)||(my_config->sim_length>MAX_SIMULATION_LENGTH))
    {
        return 1;
    }
    if (my_ptime==NULL)
    {
        return 2;
    }
    for (int i=0;i<(my_config->sim_length);i++){
        if ((*(my_ptime->comp1+i)<=0)||(*(my_ptime->comp2+i)<=0)||(*(my_ptime->comp3+i)<=0)||(*(my_ptime->ws1+i)<=0)||(*(my_ptime->ws2+i)<=0)||(*(my_ptime->ws3+i)<=0)){

            return 2;
        }
    }

    srand(time(0));

    /**===========READING THE DATA FROM FUNCTION INPUTS============*/


    int lengthc1=my_config->sim_length; /* number of component C1 supplied for simulation*/
    int lengthc2=my_config->sim_length; /* number of component C2 supplied for simulation*/
    int lengthc3=my_config->sim_length; /* number of component C3 supplied for simulation*/
    int lengthw1=my_config->sim_length; /* number of time intervals for assembling P1 for simulation*/
    int lengthw2=my_config->sim_length; /* number of time intervals for assembling P2 for simulation*/
    int lengthw3=my_config->sim_length; /* number of time intervals for assembling P3 for simulation*/
    int mod_type=my_config->model_type; /* Model choice*/
    float *pointer_proc_time_c1=my_ptime->comp1; /* address of processing time C1*/

    float *pointer_proc_time_c2=my_ptime->comp2; /* address of processing time C2*/
    float *pointer_proc_time_c3=my_ptime->comp3; /* address of processing time C3*/
    float *pointer_proc_time_w1=my_ptime->ws1; /* address of processing time P1*/
    float *pointer_proc_time_w2=my_ptime->ws2; /* address of processing time P2*/
    float *pointer_proc_time_w3=my_ptime->ws3; /* address of processing time P3*/
    /**=================END OF READING DATA=======================*/
    /**==================Initial conditions====================*/
    float internal_process_time[5]={0.0,0.0,0.0,0.0,0.0};
    float idle_time_insp1=0.0, idle_time_insp2=0.0;
    int comp_type_kept_by_insp2=0;
    int num_of_used_c1=0; /* number of components C1 used till the current time*/
    int num_of_used_c2=0; /* number of components C2 used till the current time*/
    int num_of_used_c3=0; /* number of components C3 used till the current time*/
    int num_product[3]={0,0,0}; /* number of products of each type produced till the current time*/
    int c1_in_buffer[3]={0,0,0}; /* number of components C1 in the buffers*/
    int c2_in_buffer2=0; /* number of components C2 in the buffer 2*/
    int c3_in_buffer3=0; /* number of components C3 in the buffer 3*/
    float internal_proc_time=0.0; /* current time interval*/
    float clock=0.0; /* simulation clock*/
    float clockin[3]={0.0,0.0,0.0}; /* total of time of components of each type staying inside the system {for verification}*/
    float clockout[3]={0.0,0.0,0.0}; /* total of time components of each type exiting the system {for verification}*/
    float inplant[3]={0.0,0.0,0.0}; /* total time that C1 stay in the system {for verification}*/
    int *num_comp_in_syst;     /*Pointer for the counter of components in each system at the current time*/
    int *c1_sent_to_buffer;    /*Pointer to save the # of components that Inspector 1 send to the buffers*/
    internal_process_time[0]= *(pointer_proc_time_c1+num_of_used_c1);
    if ((int)rand()%2 == 0){
        comp_type_kept_by_insp2=2;
        internal_process_time[1] = *(pointer_proc_time_c2+num_of_used_c2);
    } else {
        comp_type_kept_by_insp2=3;
        internal_process_time[1]=*(pointer_proc_time_c3+num_of_used_c3);
    }
    /**==================End of Initial conditions====================*/
    /**==================The simulation starts====================*/
    while ((internal_process_time[0] >0) || (internal_process_time[1] >0) || (internal_process_time[2] >0) || (internal_process_time[3] >0) || (internal_process_time[4] >0)) {
        internal_proc_time =clockfcn(internal_process_time[0],internal_process_time[1],internal_process_time[2],internal_process_time[3],internal_process_time[4]);
        /*error test*/
        if (internal_proc_time==0) {
            return 3;
        }
        clock+=internal_proc_time; /* simulation time*/
        /* Compute number of components at current time*/
        num_comp_in_syst=counters(internal_process_time,c1_in_buffer,c2_in_buffer2,c3_in_buffer3,comp_type_kept_by_insp2);
        /*error test*/
        if (num_comp_in_syst==NULL){
            return 4;
        }
        /* Total of component in the plant at the current time*/
        /* Compute the total process time of components at the current time*/
        inplant[0]=inplant[0]+num_comp_in_syst[0]*internal_proc_time;
        inplant[1]=inplant[1]+num_comp_in_syst[1]*internal_proc_time;
        inplant[2]=inplant[2]+num_comp_in_syst[2]*internal_proc_time;
        /* reset the num_comp_in_syst */
        num_comp_in_syst[0]=0; num_comp_in_syst[1]=0; num_comp_in_syst[2]=0;
        /* Clock advances to the next event*/
        internal_process_time[0] -=internal_proc_time;
        internal_process_time[1] -=internal_proc_time;
        internal_process_time[2] -= internal_proc_time;
        internal_process_time[3] -= internal_proc_time;
        internal_process_time[4] -= internal_proc_time;
        /* Calculate the moment when the components starting to enter the black box  ** for verification */
        if ((internal_process_time[0] == 0) && (num_of_used_c1 > 0)){ /* total time of the component 1 entering the black box*/
        clockin[0]+=clock-*(pointer_proc_time_c1+num_of_used_c1);
        }
        if ((internal_process_time[1] == 0) && (comp_type_kept_by_insp2 == 2) && (num_of_used_c2>0)){ /*total time of the component 2 entering the black box*/
        clockin[1]+=clock-*(pointer_proc_time_c2+num_of_used_c2);
        }
        if ((internal_process_time[1] == 0) && (comp_type_kept_by_insp2 == 3) && (num_of_used_c3>0)) { /*/total time of the component 3 entering the black box*/
        clockin[2]+=clock-*(pointer_proc_time_c3+num_of_used_c3);
        }
        /** When an event Triggers - the process internal time elapse to 0*/

        /** Event Ins1 triggers: the internal process time of inspector 1 is 0 or negative and there is an available space in buffers for him to send C1 */
        if ((internal_process_time[0] <= 0) && ((c1_in_buffer[0] < 2) || (c1_in_buffer[1] < 2) || (c1_in_buffer[2] < 2)) && (num_of_used_c1 <= (lengthc1-1)) ){ /*if the inspector 1 finishes C1 and there is a space in buffers for C1*/
            c1_sent_to_buffer = buffer1(c1_in_buffer,c2_in_buffer2,c3_in_buffer3,mod_type);
            /*error test*/
            if (c1_sent_to_buffer==NULL)
            {
                return 5;
            }
            c1_in_buffer[0]+=c1_sent_to_buffer[0];
            c1_in_buffer[1]+=c1_sent_to_buffer[1];
            c1_in_buffer[2]+=c1_sent_to_buffer[2];
            num_of_used_c1++;   /* number of loaded components C1*/
            if (internal_process_time[0] < 0) { /* compute idle time*/
                idle_time_insp1-= internal_process_time[0];
            }
            internal_process_time[0]= *(pointer_proc_time_c1+num_of_used_c1);
        }/*End if case for inspector 1*/

    /** Event Ins2 can trigger: the internal process time of inspector 2 is 0 or negative and there is an available space in buffers for him to send C2/C3*/
        int type; /* Identifier for type of component*/
        if ((comp_type_kept_by_insp2 == 2) && (c2_in_buffer2 < 2) && (num_of_used_c2 <= (lengthc2-1))){
            type=2;
        } else if((comp_type_kept_by_insp2 == 3) && (c3_in_buffer3 < 2)&& (num_of_used_c3 <= (lengthc3-1))){
            type=3;
        } else{
            type=0;
        }

        if ((internal_process_time[1] <= 0) && (type == 2 || type == 3) && (num_of_used_c2 <= (lengthc2-1)) ){ /* if the component the inspector 2 finishes is 2 or 3*/
            if (type == 2){ /*If it was C2*/
            c2_in_buffer2++;
            } else{
                c3_in_buffer3++;  /*Increase C3*/
            }
            comp_type_kept_by_insp2 = ((int)rand()%2)+2; /* the type of component that inspector 2 receives to process is randomly generated.*/
            if (internal_process_time[1] < 0) { /* compute idle time*/
                idle_time_insp2-=internal_process_time[1];
            }
            if (comp_type_kept_by_insp2 == 2) {
                num_of_used_c2++;
                internal_process_time[1]=*(pointer_proc_time_c2+num_of_used_c2); /*loading input from file*/
            } else {
            num_of_used_c3++;
            internal_process_time[2]=*(pointer_proc_time_c3+num_of_used_c3); /*loading input from file*/
            }

        }

        /** Event Workstations */

        /** the internal process time of one of workstations is 0, a product is fully assembled*/
        if (internal_process_time[2] == 0){
            num_product[0]++;
            clockout[0]+=clock; /* total time of the components C1 when they go out of the black box as completed products*/
        } else if (internal_process_time[3] == 0) {
            num_product[1]++;
            clockout[0]+=clock; /* total time of the components C2 when they go out of the black box as completed products*/
            clockout[1]+=clock; /* total time of the components C3 when they go out of the black box as completed products*/
        } else if (internal_process_time[4] == 0) {
            num_product[2]++;
            clockout[0]+=clock; /* total time of the component 1 outing the black box*/
            clockout[2]+=clock; /* total time of the component 3 outing the black box*/
        }
        /** one of workstation and the components in its buffer is ready to proceed assembling*/
        if ((internal_process_time[2] <=0) && (c1_in_buffer[0] > 0) && (num_product[0] <= (lengthw1))){
            c1_in_buffer[0]--;
            if (num_product[0] <= (lengthw1)) {
                internal_process_time[2] = *(pointer_proc_time_w1+num_product[0]);
            }
        } else if ((internal_process_time[3] <=0) && (c1_in_buffer[1] >0) && (c2_in_buffer2 >0) && (num_product[1] <= (lengthw2-1))){
            c1_in_buffer[1]--;
            c2_in_buffer2--;
            if (num_product[1] <= (lengthw2-1)) {
                internal_process_time[3] = *(pointer_proc_time_w2+num_product[1]);

            }
        } else if ((internal_process_time[4] <=0) && (c1_in_buffer[2] >0) && (c3_in_buffer3 >0) && (num_product[2] <= (lengthw3-1))) {
            c1_in_buffer[2]--;
            c3_in_buffer3--;
            if (num_product[2] <= (lengthw3-1)) {
                internal_process_time[4] = *(pointer_proc_time_w3+num_product[2]);
            }
        }

    }
    /**==================End of simulation ====================*/
    /** Verification computing operation for General Black Box*/
    /* Number of components at the moment*/
    num_comp_in_syst=counters(internal_process_time,c1_in_buffer,c2_in_buffer2,c3_in_buffer3,comp_type_kept_by_insp2);
    if (num_comp_in_syst==NULL){
        return 4;
    }
    /* Total of component in the plant at the current time*/
    /* Total time of components being the black box*/
    float clock1=clockout[0]+num_comp_in_syst[0]*clock-clockin[0];
    float clock2=clockout[1]+num_comp_in_syst[1]*clock-clockin[1];
    float clock3=clockout[2]+num_comp_in_syst[2]*clock-clockin[2];
    /* Parameters of Little's Law*/
    /* average number of components in the plant*/
    float L1=inplant[0]/clock;
    float L2=inplant[1]/clock;
    float L3=inplant[2]/clock;
    /* average time of component in the plant:*/
    float W1=clock1/num_of_used_c1;
    float W2=clock2/num_of_used_c2;
    float W3=clock3/num_of_used_c3;
    /* Effective arrival rate */
    float lambda1=num_of_used_c1/clock;
    float lambda2=num_of_used_c2/clock;
    float lambda3=num_of_used_c3/clock;
    /* Expected L_hat: */
    float lambda_hat1=L1/W1;
    float lambda_hat2=L2/W2;
    float lambda_hat3=L3/W3;
    /** Upload the simulation result to my_state pointer*/
    (my_state+mod_type)->sim_length=my_config->sim_length;
    (my_state+mod_type)->clock=clock;
    (my_state+mod_type)->produced_prod[0]=num_product[0];
    (my_state+mod_type)->produced_prod[1]=num_product[1];
    (my_state+mod_type)->produced_prod[2]=num_product[2];
    (my_state+mod_type)->used_component[0]=num_of_used_c1;
    (my_state+mod_type)->used_component[1]=num_of_used_c2;
    (my_state+mod_type)->used_component[2]=num_of_used_c3;
    (my_state+mod_type)->unused_component[0]=my_config->sim_length-num_product[0];
    (my_state+mod_type)->unused_component[1]=my_config->sim_length-num_product[1];
    (my_state+mod_type)->unused_component[2]=my_config->sim_length-num_product[2];
    (my_state+mod_type)->inspector1.idle_time=idle_time_insp1;
    (my_state+mod_type)->inspector2.idle_time=idle_time_insp2;

    /** Check the verification by Little's Law*/
    if (((abs(lambda1-lambda_hat1)) < 0.001) && ((abs(lambda2-lambda_hat2)) < 0.001) && ((abs(lambda3-lambda_hat3)) < 0.001)){
        return 0; /*the function runs successfully*/

    }
    else {
        return 6; /*the function runs unsuccessfully*/
    }

}
