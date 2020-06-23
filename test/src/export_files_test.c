#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../include/data_types.h"
#include "../../include/export_files.h"
#include "../../include/common_functions.h"
#include "../include/export_files_test.h"
#include "../include/common_functions_test.h"

/**
 * The function test all the functions inside export_files and shows the results
 */

int export_files_test(){
    int return_var = 0;                         /* Initialize return variable of the function */
    char* file_name_short = "./test/data/output/testing.csv";          /* Root of the file to create */
    char* empty = '\0';
    char* file_name_long = "./test/data/output/testingxxxxxxx.csv";/* Root of the file to create */
    char* output_directory= "./test/data/output/";       // The output directory
    FILE *csv_file = NULL;

    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    struct STATE *my_state=malloc(SIM_STATES*sizeof(struct STATE));

    printf("Error -1 :\n"); //My config
    printf("Return value from export_files() was %d\n\n",export_files(my_config,my_state,output_directory));

    set_state_test1(my_config,my_state); //Good config not state
    printf("Error -2 :\n"); //My state
    printf("Return value from export_files() was %d\n\n",export_files(my_config,my_state,output_directory));

    set_state_test2(my_config,my_state); //Good config and state
    printf("Error -3 :\n"); //Longer file name
    printf("Return value from export_csv() was %d\n\n",export_csv(my_state+my_config->model_type ,file_name_long,0));

    printf("Error -3 :\n"); //Longer file name
    printf("Return value from export_analysis() was %d\n\n",export_analysis(my_state ,file_name_long));

    printf("Error -4 :\n"); //NULL csv file
    printf("Return value from write_file() was %d\n\n",write_file(my_state+my_config->model_type,csv_file));

    printf("No errors: \n");
    printf("Return value from export_files() was %d\n\n",export_csv(my_state+my_config->model_type ,file_name_short,0));

    free(my_config);
    free(my_state);

    return return_var;                                      /* Return the value of the return variable*/
}

