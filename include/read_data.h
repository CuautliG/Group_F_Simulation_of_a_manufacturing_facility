#ifndef READ_DATA_H_INCLUDED
#define READ_DATA_H_INCLUDED

int read_data(char *input_directory, struct CONFIG *my_config, struct PTIME *my_ptime);
float *data(float *times, char STR[20], int *length);
float *generate_random(struct CONFIG *my_config,float *rand_numb);
int read_client_files(char *input_directory, struct PTIME* my_ptime,int length_files);
int generate_random_time (char *input_directory, struct CONFIG *my_config, struct PTIME* my_ptime);

#endif // READ_DATA_H_INCLUDED
