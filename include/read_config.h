#ifndef READ_CONFIG_H_INCLUDED
#define READ_CONFIG_H_INCLUDED


/**
* The function is used for tokenization, it split each line by a delimiter "="
* @param[in] input_line of config file
* @param[in] key_value[] which is used to call the delimiter
* @return -1 if an error occurred during the execution or 0 if the tokenization was done successfully.
*/
int split_key_value(char *input_line, char *key_value[]);

/**
* The function passes the .cfg file and reads it into a struct
* @param[in] *config_file, which is the config file to be read in
* @param[in] *my_config is the empty struct set as NULL where the config file is read into
* @return -1 if an error occurred during the execution or 0 if the struct was created successfully.
*/

int parse_config(char *config_file, struct CONFIG *my_config);


/**
* The function prints out the elements of the Struct *my_config
* @param[in] *config_file, which is the config file to be read in
* @param[in] *my_config is the empty struct set as NULL where the config file is read into
* @return -1 if an error occurred during the execution or 0 if the elements of the struct are printed successfully.
*/

int read_config(char *config_file, struct CONFIG *my_config);


#endif // READ_CONFIG_H_INCLUDED
