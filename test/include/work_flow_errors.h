#ifndef WORK_FLOW_ERRORS_H_INCLUDED
#define WORK_FLOW_ERRORS_H_INCLUDED
/*data types*/
 struct CLOCKFCN_TEST {
    float input_1;
    float input_2;
    float input_3;
    float input_4;
    float input_5;
 };

 struct COUNTERS_TEST {
    float *internal_process_time;
    int c1_in_buffer[3],c2_in_buffer2, c3_in_buffer3, comp_type_kept_by_insp2;
 };
 struct BUFFER1_TEST {
    int c1_in_buffer[3];
    int c2_in_buffer2;
    int c3_in_buffer3;
    int model_type;
};

struct WORK_FLOW_TEST {
    struct CONFIG my_config;
    struct PTIME my_ptime;
    struct STATE my_state;
};
struct WORK_FLOW_TEST work_flow_error0();
struct WORK_FLOW_TEST work_flow_error1();
struct WORK_FLOW_TEST work_flow_error2();
struct CLOCKFCN_TEST work_flow_error3();
struct COUNTERS_TEST work_flow_error4();
struct BUFFER1_TEST work_flow_error5();

#endif
