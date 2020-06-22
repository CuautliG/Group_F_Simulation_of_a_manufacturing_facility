#ifndef READ_CONFIG_H_INCLUDED
#define READ_CONFIG_H_INCLUDED


int split_key_value(char *input_line, char *key_value[]);
int parse_config(char *config_file, struct CONFIG *my_config);
int read_config(char *config_file, struct CONFIG *my_config);


#endif // READ_CONFIG_H_INCLUDED
