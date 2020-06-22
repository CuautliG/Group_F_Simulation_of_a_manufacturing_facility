#ifndef WORK_FLOW_H_INCLUDED
#define WORK_FLOW_H_INCLUDED

int work_flow(struct CONFIG *my_config,struct PTIME *my_ptime, struct STATE *my_state);
float clockfcn(float input_1, float input_2, float input_3, float input_4, float input_5);
int *counters(float *internal_process_time, int *c1_in_buffer, int c2_in_buffer2, int c3_in_buffer3,int comp_type_kept_by_insp2);
int *buffer1(int *c1_in_buffer,int c2_in_buffer2, int c3_in_buffer3, int model_type);

#endif // WORK_FLOW_H_INCLUDED
