#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "../include/data_types.h"
#include "../include/work_flow.h"
/** \brief Function to find the minimum positive float number among 5 inputs. \n
 * This function is used to find the time interval from the current time to the event. If the output is not satisfied the function's purpose the error message will appear
 * \param[in] the 5 float inputs.
 * \return the minimum positive float number of 5 inputs.
 */
float clockfcn(float input_1, float input_2, float input_3, float input_4, float input_5){
    float internal_process_time=FLT_MAX;

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
/** black box testing */
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
 * \param[in] the internal process time of every subunit to check if they are keeping any component and number of components in the buffers.
 * \return the number of components of each in the system.
 */
int *counters(float internal_process_time_insp1,float internal_process_time_insp2,float internal_process_time_ws1,float internal_process_time_ws2,float internal_process_time_ws3,int c1_in_buffer1, int c1_in_buffer2, int c2_in_buffer2, int c1_in_buffer3,int c3_in_buffer3,int comp_type_kept_by_insp2){
    int static num_of_c_in_sys[]={0,0,0};
    if ((internal_process_time_insp1 > 0) || ((c1_in_buffer1==2) && (c1_in_buffer2==2)&&(c1_in_buffer3==2))){
        num_of_c_in_sys[0]++;
    }
    else if (((internal_process_time_insp2 >0) || (c2_in_buffer2==2))&& (comp_type_kept_by_insp2 == 2)) {
        num_of_c_in_sys[1]++;
    }
    else if(((internal_process_time_insp2 >0) || (c3_in_buffer3==2))&& (comp_type_kept_by_insp2 == 3)) {
        num_of_c_in_sys[2]++;
    } else if (internal_process_time_ws1 > 0) { /* compute number of component being processed by workstations*/
        num_of_c_in_sys[0]++;
    }
    else if(internal_process_time_ws2 > 0) {
        num_of_c_in_sys[0]++;
        num_of_c_in_sys[1]++;
    }
    else if(internal_process_time_ws3 > 0) {
        num_of_c_in_sys[0]++;
        num_of_c_in_sys[2]++;
    }

    num_of_c_in_sys[0]+=c1_in_buffer1+c1_in_buffer2+c1_in_buffer3;
    num_of_c_in_sys[1]+=c2_in_buffer2;
    num_of_c_in_sys[2]+=c3_in_buffer3;

    return num_of_c_in_sys;
}
/** \brief Function to send a fully processed component C1 from inspector 1 to the Buffer in respect of the model type and the current states of the Buffers. \n
 * \param[in] number of components of each type in each Buffer, the type of model.
 * \return the number of component C1 sent to each Buffer (0: if not sent, 1: if sent)
 */
int *buffer1(float c1_in_buffer1,int c1_in_buffer2,int c1_in_buffer3,int c2_in_buffer2, int c3_in_buffer3, int model_type){
    int static buffer[]={0,0,0};
    if (model_type==1){
        if (c1_in_buffer1 < 2) {
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 0;
        } else if (c1_in_buffer2 < 2) { /* if B2, B3 has no C2, C3 ready, the priority goes to B1*/
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 0;
        } else {
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 1;
        }
    }/*End  option 1*/
    else {
        if  (((c1_in_buffer2 < 1) && (c2_in_buffer2 > 0)) || ((c1_in_buffer2<2) && (c1_in_buffer1 == 2))) { /* if B2 has C2 ready then priority goes to B2*/
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 0;
        } else if (((c1_in_buffer3 < 1) && (c3_in_buffer3 > 0)) || ((c1_in_buffer3 < 2) && (c1_in_buffer2 == 2))) { /* if B3 has C3 ready then priority goes to B3*/
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 1;
        } else { /* if B2, B3 has no C2, C3 ready, the priority goes to B1*/
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 0;
        }
    } /*End option 2*/
    return buffer;
}
/** \brief Based on the given configuration and input data, Function to simulate the work flow of the manufacturing facility, and produce the the simulation results. \n
*  The simulation results consists of: the simulation time, the number of components used and not used for the simulation, the number of products assembled,
*the idle time of inspectors. The function also performs the Little's Law verification to check the credibility of the simulation.
 * \param[in] configuration data from read_config function, process time from read_data function, and pointer of my_state to upload the system status to that pointer.
 * \return the function proceed the input and configuration data and produce the result through the pointer my_state. The return value is 0 if the function is executed well and verified,
 and 1 if the function is not executed well and not verified.
 */
int work_flow(struct CONFIG *my_config,struct PTIME *my_ptime, struct STATE *my_state){

    int n = my_config->model_type; /*Variable to know in which pointer we need to save the information*/

    /**Initial variables*/
    float *pointer_proc_time_c1=(my_ptime+n)->comp1; /* address of processing time C1*/
    float *pointer_proc_time_c2=(my_ptime+n)->comp2; /* address of processing time C2*/
    float *pointer_proc_time_c3=(my_ptime+n)->comp3; /* address of processing time C3*/
    float *pointer_proc_time_w1=(my_ptime+n)->ws1; /* address of processing time P1*/
    float *pointer_proc_time_w2=(my_ptime+n)->ws2; /* address of processing time P2*/
    float *pointer_proc_time_w3=(my_ptime+n)->ws3; /* address of processing time P3*/
    int lengthc1=my_config->sim_length; /* number of component C1 supplied for simulation*/
    int lengthc2=my_config->sim_length; /* number of component C2 supplied for simulation*/
    int lengthc3=my_config->sim_length; /* number of component C3 supplied for simulation*/
    int lengthw1=my_config->sim_length; /* number of time intervals for assembling P1 for simulation*/
    int lengthw2=my_config->sim_length; /* number of time intervals for assembling P2 for simulation*/
    int lengthw3=my_config->sim_length; /* number of time intervals for assembling P3 for simulation*/
    int option=my_config->model_type; /* Model choice*/
    /**=================END OF READING DATA================*/
    /*Initial conditions*/
    float *transit_proc_time_ins1; /*storing process time of inspector 1 for verification purpose*/
    float *transit_proc_time_ins2; /*storing process time of inspector 2 for verification purpose*/
    float *transit_proc_time_ws1; /*storing process time of working station 1*/
    float *transit_proc_time_ws2; /*storing process time of working station 2*/
    float *transit_proc_time_ws3; /*storing process time of working station 2*/
    float internal_process_time_insp1=0, internal_process_time_insp2=0, i1idle=0, idle_time_insp2=0, comp_type_kept_by_insp2=0;
    srand(time(0));
    float internal_process_time_ws1=0.0;
    float internal_process_time_ws2=0.0;
    float internal_process_time_ws3=0.0;
    int num_of_used_c1=0; /* number of components C1 used till the current time*/
    int num_of_used_c2=0; /* number of components C2 used till the current time*/
    int nc3=0; /* number of components C3 used till the current time*/
    int num_proc_by_ws1=0; /* number of P1 assembled till the current time*/
    int num_proc_by_ws2=0; /* number of P2 assembled till the current time*/
    int num_proc_by_ws3=0; /* number of P3 assembled till the current time*/
    int num_product1=0; /* number of P1 produced till the current time*/
    int num_product2=0; /* number of P2 assembled till the current time*/
    int num_product3=0; /* number of P3 assembled till the current time*/
    int c1_in_buffer1=0; /* number of components C1 in the buffer 1*/
    int c1_in_buffer2=0; /* number of components C1 in the buffer 2*/
    int c1_in_buffer3=0; /* number of components C1 in the buffer 3*/
    int c2_in_buffer2=0; /* number of components C2 in the buffer 2*/
    int c3_in_buffer3=0; /* number of components C3 in the buffer 3*/
    float internal_proc_time=0.0; /* current time interval*/
    float clock=0.0; /* simulation clock*/
    float clockin1=0.0; /* total of time that C1 enter the system {for verification}*/
    float clockin2=0.0; /* total of time that C2 enter the system {for verification}*/
    float clockin3=0.0; /* total of time that C3 enter the system {for verification}*/
    float clockoutp1=0.0; /* total of time that C1 exit the system {for verification}*/
    float clockoutp2=0.0; /* total of time that C2 exit the system {for verification}*/
    float clockoutp3=0.0; /* total of time that C3 exit the system {for verification}*/
    float inplant1=0.0; /* total time that C1 stay in the system {for verification}*/
    float inplant2=0.0; /* total time that C2 stay in the system {for verification}*/
    float inplant3=0.0; /* total time that C3 stay in the system {for verification}*/
    int *num_comp_in_syst;     /*Pointer for the counter of components in each system at the current time*/
    int *c1_sent_to_buffer;     /*Pointer to save the # of components that Inspector 1 send to the buffers*/

    transit_proc_time_ins1 = pointer_proc_time_c1+num_of_used_c1;
    internal_process_time_insp1= *transit_proc_time_ins1;
    if ((int)rand()%2 == 0){
        comp_type_kept_by_insp2=2;
        transit_proc_time_ins2 = pointer_proc_time_c2+num_of_used_c2;
        internal_process_time_insp2=*transit_proc_time_ins2;
    } else {
        comp_type_kept_by_insp2=3;
        transit_proc_time_ins2 = pointer_proc_time_c3+nc3;
        internal_process_time_insp2=*transit_proc_time_ins2;
    }

    while ((internal_process_time_insp1 >0) || (internal_process_time_insp2 >0) || (internal_process_time_ws1 >0) || (internal_process_time_ws2 >0) || (internal_process_time_ws3 >0)) {
        internal_proc_time =clockfcn(internal_process_time_insp1,internal_process_time_insp2,internal_process_time_ws1,internal_process_time_ws2,internal_process_time_ws3);
        clock+=internal_proc_time; /* simulation time*/
        /* Compute number of components at current time*/
        num_comp_in_syst=counters(internal_process_time_insp1,internal_process_time_insp2,internal_process_time_ws1,internal_process_time_ws2,internal_process_time_ws3,c1_in_buffer1,c1_in_buffer2,c2_in_buffer2,c1_in_buffer3,c3_in_buffer3,comp_type_kept_by_insp2);
        /* Total of component in the plant at the current time*/
        /* Compute the total process time of components at the current time*/
        inplant1=inplant1+num_comp_in_syst[0]*internal_proc_time;
        inplant2=inplant2+num_comp_in_syst[1]*internal_proc_time;
        inplant3=inplant3+num_comp_in_syst[2]*internal_proc_time;
        /* Clock advances to the next event*/
        internal_process_time_insp1 -=internal_proc_time;
        internal_process_time_insp2 -=internal_proc_time;
        internal_process_time_ws1 -= internal_proc_time;
        internal_process_time_ws2 -= internal_proc_time;
        internal_process_time_ws3 -= internal_proc_time;
        /* The time moment when components are received by inspectors:  ** for verification */
        if ((internal_process_time_insp1 == 0) && (num_of_used_c1 > 0)){ /* total time of the component 1 entering the black box*/
        clockin1+=clock-*transit_proc_time_ins1;
        }
        if ((internal_process_time_insp2 == 0) && (comp_type_kept_by_insp2 == 2) && (num_of_used_c2>0)){ /*total time of the component 2 entering the black box*/
        clockin2+=clock-*transit_proc_time_ins2;
        }
        if ((internal_process_time_insp2 == 0) && (comp_type_kept_by_insp2 == 3) && (nc3>0)) { /*/total time of the component 3 entering the black box*/
        clockin3+=clock-*transit_proc_time_ins2;
        }
        /** When an event Triggers:*/

        /** Event Ins1 triggers:*/
        if ((internal_process_time_insp1 <= 0) && ((c1_in_buffer1 < 2) || (c1_in_buffer2 < 2) || (c1_in_buffer3 < 2)) && (num_of_used_c1 <= (lengthc1-1)) ){ /*if the inspector 1 finishes C1 and there is a space in buffers for C1*/
            c1_sent_to_buffer = buffer1(c1_in_buffer1,c1_in_buffer2,c1_in_buffer3,c2_in_buffer2,c3_in_buffer3,option);
            c1_in_buffer1+=c1_sent_to_buffer[0];
            c1_in_buffer2+=c1_sent_to_buffer[1];
            c1_in_buffer3+=c1_sent_to_buffer[2];
            num_of_used_c1++;   /* number of loaded components C1*/
            if (internal_process_time_insp1 < 0) { /* compute idle time*/
                i1idle-= internal_process_time_insp1;
            }
            transit_proc_time_ins1 = pointer_proc_time_c1+num_of_used_c1;
            internal_process_time_insp1= *transit_proc_time_ins1;
        }/*End if case for inspector 1*/

    /** Event Ins2 can trigger:*/
        int type; /* Identifier for type of component*/
        if ((comp_type_kept_by_insp2 == 2) && (c2_in_buffer2 < 2) && (num_of_used_c2 <= (lengthc2-1))){
            type=2;
        } else if((comp_type_kept_by_insp2 == 3) && (c3_in_buffer3 < 2)&& (nc3 <= (lengthc3-1))){
            type=3;
        } else{
            type=0;
        }

        if ((internal_process_time_insp2 <= 0) && (type == 2 || type == 3) && (num_of_used_c2 <= (lengthc2-1)) ){ /* if the component the inspector 2 finishes is 2 or 3*/
            if (type == 2){ /*If it was C2*/
            c2_in_buffer2++;
            } else{
                c3_in_buffer3++;  /*Increase C3*/
            }
            comp_type_kept_by_insp2 = ((int)rand()%2)+2; /* the type of component that inspector 2 receives to process is randomly generated.*/
            if (internal_process_time_insp2 < 0) { /* compute idle time*/
                idle_time_insp2-=internal_process_time_insp2;
            }
            if (comp_type_kept_by_insp2 == 2) {
                num_of_used_c2++;
                transit_proc_time_ins2=(pointer_proc_time_c2+num_of_used_c2); /*loading input from file*/
            } else {
            nc3++;
            transit_proc_time_ins2=(pointer_proc_time_c3+nc3); /*loading input from file*/
            }

        }

        /** Event WS1*/
        if (internal_process_time_ws1 == 0){
            num_product1++;
            clockoutp1+=clock; /* total time of the components C1 when they go out of the black box as completed products*/
        } else if (internal_process_time_ws2 == 0) {
            num_product2++;
            clockoutp1+=clock; /* total time of the components C2 when they go out of the black box as completed products*/
            clockoutp2+=clock; /* total time of the components C3 when they go out of the black box as completed products*/
        } else if (internal_process_time_ws3 == 0) {
            num_product3++;
            clockoutp1+=clock; /* total time of the component 1 outing the black box*/
            clockoutp3+=clock; /* total time of the component 3 outing the black box*/
        }

        if ((internal_process_time_ws1 <=0) && (c1_in_buffer1 > 0) && (num_proc_by_ws1 <= (lengthw1-1))){
            num_proc_by_ws1++;
            c1_in_buffer1--;
            if (num_proc_by_ws1 <= (lengthw1-1)) {
            transit_proc_time_ws1 = pointer_proc_time_w1+num_proc_by_ws1;
            internal_process_time_ws1= *transit_proc_time_ws1;
            }
        } else if ((internal_process_time_ws2 <=0) && (c1_in_buffer2 >0) && (c2_in_buffer2 >0) && (num_proc_by_ws2 <= (lengthw2-1))){
            num_proc_by_ws2++;
            c1_in_buffer2--;
            c2_in_buffer2--;
            if (num_proc_by_ws2 <= (lengthw2-1)) {
            transit_proc_time_ws2 = pointer_proc_time_w2+num_proc_by_ws2;
            internal_process_time_ws2= *transit_proc_time_ws2;
            }
        } else if ((internal_process_time_ws3 <=0) && (c1_in_buffer3 >0) && (c3_in_buffer3 >0) && (num_proc_by_ws3 <= (lengthw3-1))) {
            num_proc_by_ws3++;
            c1_in_buffer3--;
            c3_in_buffer3--;
            if (num_proc_by_ws3 <= (lengthw3-1)) {
                transit_proc_time_ws3 = pointer_proc_time_w3+num_proc_by_ws3;
                internal_process_time_ws3= *transit_proc_time_ws3;
            }
        }

    } /* End of the main part of the program*/

    /** Verification computing operation for General Black Box*/
    /* Number of components at the moment*/
    num_comp_in_syst=counters(internal_process_time_insp1,internal_process_time_insp2,internal_process_time_ws1,internal_process_time_ws2,internal_process_time_ws3,c1_in_buffer1,c1_in_buffer2,c2_in_buffer2,c1_in_buffer3,c3_in_buffer3,comp_type_kept_by_insp2);
    /* Total of component in the plant at the current time*/
    /* Total time of components being the black box*/
    float clock1=clockoutp1+num_comp_in_syst[0]*clock-clockin1;
    float clock2=clockoutp2+num_comp_in_syst[1]*clock-clockin2;
    float clock3=clockoutp3+num_comp_in_syst[2]*clock-clockin3;
    /* Parameters of Little's Law*/
    /* average number of components in the plant*/
    float L1=inplant1/clock;
    float L2=inplant2/clock;
    float L3=inplant3/clock;
    /* average time of component in the plant:*/
    float W1=clock1/num_of_used_c1;
    float W2=clock2/num_of_used_c2;
    float W3=clock3/nc3;
    /* Effective arrival rate */
    float lambda1=num_of_used_c1/clock;
    float lambda2=num_of_used_c2/clock;
    float lambda3=nc3/clock;
    /* Expected L_hat: */
    float lambda_hat1=L1/W1;
    float lambda_hat2=L2/W2;
    float lambda_hat3=L3/W3;

    /** Upload the simulation result to my_state pointer*/
    (my_state+n)->model=my_config->model_type;
    (my_state+n)->sim_length=my_config->sim_length;
    (my_state+n)->clock=clock;
    (my_state+n)->produced_prod[0]=num_product1;
    (my_state+n)->produced_prod[1]=num_product2;
    (my_state+n)->produced_prod[2]=num_product3;
    (my_state+n)->used_component[0]=num_of_used_c1;
    (my_state+n)->used_component[1]=num_of_used_c2;
    (my_state+n)->used_component[2]=nc3;
    (my_state+n)->unused_component[0]=my_config->sim_length-num_product1;
    (my_state+n)->unused_component[1]=my_config->sim_length-num_product2;
    (my_state+n)->unused_component[2]=my_config->sim_length-num_product3;
    (my_state+n)->inspector1.idle_time=i1idle;
    (my_state+n)->inspector2.idle_time=idle_time_insp2;
/** Check the verification by Little's Law*/
    if (((abs(lambda1-lambda_hat1)) < 0.001) && ((abs(lambda2-lambda_hat2)) < 0.001) && ((abs(lambda3-lambda_hat3)) < 0.001)) {
        return 0;
    }
    else {
        return 1;
    }
}
