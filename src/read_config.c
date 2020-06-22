//  read_config
//
//  Created by Charles Emesobum on 2020-06-02.
//  Copyright © 2020 Charles Emesobum. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/data_types.h"
#include "./include/read_config.h"

/** \brief Function to split the .cfg file. \n
* The function is used for tokenization, it splits each line by a delimiter "="
* @param[in] input_line of the configuration file
* @param[in] key_value[] which is used to call the delimiter
* @return -2 if an error occurred during the execution or 0 if the tokenization was done successfully.
*/
int split_key_value(char* input_line, char* key_value[]){
    char* token = strtok(input_line, "=");
    int rtn_val =0;

    key_value[0]=token;
    if(token!=NULL) {
        token = strtok(NULL, " ");
        key_value[1]=token;
    }else{
        printf("The function split_key_value was unable to parse the key value %s\n",token);
        printf("->The function split_key_value uses = as a token\n");
        return rtn_val = -2;
    }
    return rtn_val;
}
/**
* The function passes the .cfg file and reads it into a struct
* @param[in] *config_file which is the config file to be read in
* @param[in] *my_config is the empty struct set as NULL where the config file is read into
* @return -1 if the file did not exist, -2 if the input is not recognized or 0 if the struct was created successfully.
*/
int parse_config(char *config_file, struct CONFIG *my_config){

    FILE *curr_config_file = NULL;
    curr_config_file = fopen(config_file, "r");

    char* key_value[2];
    int rtn_val =0;
    char curr_line[MAX_LINE_LENGTH];

    if (curr_config_file == NULL){ /* If the file does not exist */
        printf("The function parse_config did not find the file %s\n",config_file);
        printf("->The function parse_config needs an existent configuration file\n");
        return rtn_val = -1;
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
            else if(strcmp(key_value[0], "up_limit") ==0){
                my_config->upper_limit= atoi(key_value[1]);
            }else{
                printf("The function parse_config detected an invalid input %s\n",atoi(key_value[0]));
                printf("->The function parse_config cannot read inputs that were not defined in the CONFIG structure\n");
                return rtn_val = -2;
            }
        }

    }
    return rtn_val;
}

/**
* The function prints out the elements of the Struct *my_config
* @param[in] *config_file which is the config file to be read in
* @param[in] *my_config is the empty struct set as NULL where the config file is read into
* @return -1 if the file did not exist, -2 if the input is not recognized, -3 if the input are not valid for the execution
*     or 0 if the struct was created successfully.
*/
int read_config(char* config_file, struct CONFIG *my_config){

    int result = parse_config(config_file, my_config);

    if(result == 0){
            if( (my_config->both_models != 0) && (my_config->both_models != 1) ){
                printf("The function read_config detected an invalid input in both_models=%d\n",my_config->both_models);
                printf("->The function read_config in the variable both_models can just accept 0 or 1\n");
                return result=-3;
            }else if((my_config->model_type != 1) && (my_config->model_type != 2)){
                printf("The function read_config detected an invalid input in model_type=%d\n",my_config->model_type);
                printf("->The function read_config in the variable model_type can just accept 1 or 2\n");
                return result=-3;
            }else if((my_config->read_generate != 'r') && (my_config->read_generate != 'g')){
                printf("The function read_config detected an invalid input in read_generate=%c\n",my_config->read_generate);
                printf("->The function read_config in the variable read_generate can just accept 'r' or 'g'\n");
                return result=-3;
            }else if(my_config->upper_limit <= my_config->lower_limit){
                printf("The function read_config detected that the upper limit is %f ",my_config->upper_limit);
                printf("and the lower limit is %f \n",my_config->lower_limit);
                printf("->The upper limit must be greater than the lower limit\n");
                return result=-3;
            }else if((my_config->sim_length < 1) || (my_config->sim_length > MAX_SIMULATION_LENGTH)){
                printf("The function read_config detected an invalid input in sim_length=%d\n",my_config->sim_length);
                printf("->The function read_config in the variable sim_length must be positive integer no greater than 5000\n");
                return result=-3;
            }else{
                return result=0;
            }
    }else{
        return result;
    }
}
