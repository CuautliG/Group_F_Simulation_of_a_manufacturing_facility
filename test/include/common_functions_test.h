#ifndef COMMON_FUNCTIONS_TEST_H_INCLUDED
#define COMMON_FUNCTIONS_TEST_H_INCLUDED

void set_state_test1(struct CONFIG *my_config,struct STATE *my_state);
void set_state_test2(struct CONFIG *my_config,struct STATE *my_state);
struct WORK_FLOW_TEST work_flow_error0();
struct WORK_FLOW_TEST work_flow_error1();
struct WORK_FLOW_TEST work_flow_error2();
struct CLOCKFCN_TEST work_flow_error3();
struct COUNTERS_TEST work_flow_error4();
struct BUFFER1_TEST work_flow_error5();

#endif // COMMON_FUNCTIONS_TEST_H_INCLUDED
