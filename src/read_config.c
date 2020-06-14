//
//  main.c
//  Parse_config
//
//  Created by Charles Emesobum on 2020-06-02.
//  Copyright © 2020 Charles Emesobum. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/read_config.h"

int split_key_value(char* input_line, char* key_value[]){
    // this is to create a delimiter "="
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

int parse_config(char *config_file, struct CONFIG *my_config){

    FILE *curr_config_file;
    curr_config_file = fopen(config_file, "r");//opens the config file

    char* key_value[2];
    int rtn_val =0;
    char curr_line[MAX_LINE_LENGTH];

    if (curr_config_file == NULL){
        printf("Failed to open config file: %s.\n", config_file);
        rtn_val=-1;
    }
    
    // reads each line and gets the element of my_config
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
                my_config->lolimit= atoi(key_value[1]);
            }
            else{
                my_config->uplimit= atoi(key_value[1]);
            }
        }

    }
    return rtn_val;
}
/**
* param[in]
*
*/
int read_config(char* config_file, struct CONFIG *my_config){

    int result = parse_config(config_file, my_config);//calls the parse_config function

    printf("both_models, %d\n", my_config->both_models);
    printf("model_type, %d\n", my_config->model_type);
    printf("read_generate, %c\n",my_config->read_generate);
    printf("sim_length, %d\n",my_config->sim_length);
    printf("lo_limit, %f\n", my_config->lolimit);
    printf("up_limit, %f\n", my_config->uplimit);
    return 0;
}
