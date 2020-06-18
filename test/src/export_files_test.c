#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../include/data_types.h"
#include "../../include/export_files.h"
#include "../../include/common_functions.h"

/** \brief The function displays the main results of the simulator and creates .csv files with this information in a specific directory
 *
 * \param[in] my_config           configuration of the simulator
 * \param[in] my_state            state of the simulator
 * \param[in] param[out] output_directory   directory where the files will be saved
 * \return 0 if an error occurred during the execution, any other number represents the number of files created
 *
 */

int export_files_test(){
    int return_var = 0;                         /* Initialize return variable of the function */
    char* file_name = "resultsxxxxxxxxxxx";                /* Root of the file to create */
    char* extension = ".csv";                   /* Extension of the file to create */
    char* full_filename = NULL;                 /* Empty string*/
    char* output_directory= "./data/output/";   // The output directory
    int model_type=2;                           /* Variable to save the model type from the configuration file */


    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    struct STATE *my_state=malloc(SIM_STATES*sizeof(struct STATE));

    //print_state(my_state);
    printf("export_csv test 1 - my_state has zero in sim_length and/or clock \n");
    export_csv(my_state ,file_name);


    full_filename = malloc(strlen(output_directory)+MAX_SIZE_FILENAME); /* Allocate memory to save the the output path */
    strcpy(full_filename,output_directory);                             /* Copy output_directory string into full_filename */
    strcat(full_filename,file_name);                                    /* Concatenate the file_name string into full_filename */
    char model_type_char[]={'0' + model_type, '\0'};                    /* Convert model_type integer into char */
    strcat(full_filename,model_type_char);                              /* Concatenate the model_type into the full_filename */
    strcat(full_filename,extension);                                    /* Concatenate the extension into the full_filename */

    set_state_test(my_config,my_state);

    //print_state(my_state+my_config->model_type);

    printf("export_csv test 2 - filename bigger than 30 characters \n");
    export_csv(my_state+my_config->model_type ,full_filename);


    return return_var;                                      /* Return the value of the return variable*/
}
