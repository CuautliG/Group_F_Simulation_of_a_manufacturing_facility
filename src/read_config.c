//  read_config
//
//  Created by Charles Emesobum on 2020-06-02.
//  Copyright © 2020 Charles Emesobum. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/read_config.h"
/**
* The function is used for tokenization, it split each line by a delimiter "="
* @param[in] input_line of config file
* @param[in] key_value[] which is used to call the delimiter
* @return -1 if an error occurred during the execution or 0 if the tokenization was done successfully.
*/
int split_key_value(char* input_line, char* key_value[]){
    char* token = strtok(input_line, "=");

    key_value[0]=token;
    if(token!=NULL) {
        token = strtok(NULL, " ");
        key_value[1]=token;
    }else{
        printf("CONFIG ERROR: Unable to parse key/value %s\n",token);
        return -1;
    }

    return 0;
}
/**
* The function passes the .cfg file and reads it into a struct
* @param[in] *config_file which is the config file to be read in
* @param[in] *my_config is the empty struct set as NULL where the config file is read into
* @return -1 if an error occurred during the execution or 0 if the struct was created successfully.
*/
int parse_config(char *config_file, struct CONFIG *my_config){

    FILE *curr_config_file;
    curr_config_file = fopen(config_file, "r");

    char* key_value[2];
    int rtn_val =0;
    char curr_line[MAX_LINE_LENGTH];

    if (curr_config_file == NULL){
        printf("Failed to open config file: %s.\n", config_file);
        rtn_val=-1;
    }

    int value_split ;
    while(fgets(curr_line, MAX_LINE_LENGTH, curr_config_file) != NULL){
        value_split = split_key_value(curr_line, key_value);
        if (value_split==0){
            if (strcmp(key_value[0], "both_models") ==0){
                my_config->both_models= atoi(key_value[1]);
            }
            else if(strcmp(key_value[0], "model_type") ==0){
                my_config->model_type= atoi(key_value[1]);
            }
            else if(strcmp(key_value[0], "read_generate")==0) {
                my_config->read_generate = *(key_value[1]+0);
            }
            else if(strcmp(key_value[0], "sim_length") ==0){
                my_config->sim_length= atoi(key_value[1]);
            }
            else if(strcmp(key_value[0], "lo_limit") ==0){
                my_config->lower_limit= atoi(key_value[1]);
            }
            else{
                my_config->upper_limit= atoi(key_value[1]);
            }
        }

    }
    return rtn_val;
}

/**
* The function prints out the elements of the Struct *my_config
* @param[in] *config_file which is the config file to be read in
* @param[in] *my_config is the empty struct set as NULL where the config file is read into
* @return -1 if an error occurred during the execution or 0 if the elements of the struct are printed successfully.
*/
int read_config(char* config_file, struct CONFIG *my_config){

    int result = parse_config(config_file, my_config);

  /*  printf("both_models, %d\n", my_config->both_models);
    printf("model_type, %d\n", my_config->model_type);
    printf("read_generate, %c\n",my_config->read_generate);
    printf("sim_length, %d\n",my_config->sim_length);
    printf("lo_limit, %f\n", my_config->lower_limit);
    printf("up_limit, %f\n", my_config->upper_limit);*/
    return 0;
}
