#ifndef COMMON_FUNCTIONS_TEST_H_INCLUDED
#define COMMON_FUNCTIONS_TEST_H_INCLUDED

void set_state_test1(struct CONFIG *my_config,struct STATE *my_state);
void set_state_test2(struct CONFIG *my_config,struct STATE *my_state);
struct WORK_FLOW_TEST work_flow_error0(void);
struct WORK_FLOW_TEST work_flow_error1(void);
struct WORK_FLOW_TEST work_flow_error2(void);
struct CLOCKFCN_TEST work_flow_error3(void);
struct COUNTERS_TEST work_flow_error4(void);
struct BUFFER1_TEST work_flow_error5(void);

#endif // COMMON_FUNCTIONS_TEST_H_INCLUDED
