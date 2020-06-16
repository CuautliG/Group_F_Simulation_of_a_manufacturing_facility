#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/data_types.h"
#include "../include/export_files.h"

/** \brief Function to exports the main results of the simulator. \n
 * This function reads the state structure and displays the main results of the simulator. These results are also exported into
 * a file called results1.csv or results2.csv depending of the model type that the simulator run.
 * \param[in] my_state  state of the simulator
 * \param[in] file_name name of the .csv file to create
 * \return 0 if an error occurred during the execution or 1 if the file was successfully created.
 */

int export_csv(struct STATE *my_state , char *file_name){
    int return_var = 0;                                     /* Initialize return variable of the function */

    if(my_state->sim_length<=0 || my_state->clock<=0){      /* If the simulation length or clock are smaller or equal than zero */
        printf("Variable sim_length or clock are less or equal to 0\n");    /* Display an error message */
        return return_var;                                  /* Return the variable with a value of zero */
    }
    FILE *csv_file = NULL;                                  /* Pointer to reference the output file */
    csv_file=fopen(file_name,"w");                          /* Open the file in write mode */

    if(csv_file == NULL){                                   /*If there was an error opening the file*/
        printf("Unable to create csv file: %s.\n",file_name);/* Display an error message */
        return return_var;                                  /* Return the variable with a value of zero */
    }

    /* Write the main results in the created file */
    fprintf(csv_file,"Number of components of each types ready for the simulation: %d\n",my_state->sim_length);
    fprintf(csv_file,"Simulation time: %f\n",my_state->clock);
    fprintf(csv_file,"Number of C1 used for simulation: %d\n",my_state->used_component[0]);
    fprintf(csv_file,"Number of C2 used for simulation: %d\n",my_state->used_component[1]);
    fprintf(csv_file,"Number of C3 used for simulation: %d\n",my_state->used_component[2]);
    fprintf(csv_file,"Number of C1 unused for simulation: %d\n",my_state->unused_component[0]);
    fprintf(csv_file,"Number of C2 unused for simulation: %d\n",my_state->unused_component[1]);
    fprintf(csv_file,"Number of C3 unused for simulation: %d\n",my_state->unused_component[2]);
    fprintf(csv_file,"Number of produced P1: %d\n",my_state->produced_prod[0]);
    fprintf(csv_file,"Number of produced P2: %d\n",my_state->produced_prod[1]);
    fprintf(csv_file,"Number of produced P3: %d\n",my_state->produced_prod[2]);
    fprintf(csv_file,"Average number of P1 per minute: %f\n",my_state->produced_prod[0]/my_state->clock);
    fprintf(csv_file,"Average number of P2 per minute: %f\n",my_state->produced_prod[1]/my_state->clock);
    fprintf(csv_file,"Average number of P3 per minute: %f\n",my_state->produced_prod[2]/my_state->clock);
    fprintf(csv_file,"Idleness of inspector 1: %f\n", my_state->inspector1.idle_time/my_state->clock);
    fprintf(csv_file,"Idleness of inspector 2: %f\n", my_state->inspector2.idle_time/my_state->clock);
    /* Display the main results of the simulator */
    printf("Number of components of each types ready for the simulation: %d\n",my_state->sim_length);
    printf("Simulation time: %f\n",my_state->clock);
    printf("Number of C1 used for simulation: %d\n",my_state->used_component[0]);
    printf("Number of C2 used for simulation: %d\n",my_state->used_component[1]);
    printf("Number of C3 used for simulation: %d\n",my_state->used_component[2]);
    printf("Number of C1 unused for simulation: %d\n",my_state->unused_component[0]);
    printf("Number of C2 unused for simulation: %d\n",my_state->unused_component[1]);
    printf("Number of C3 unused for simulation: %d\n",my_state->unused_component[2]);
    printf("Number of produced P1: %d\n",my_state->produced_prod[0]);
    printf("Number of produced P2: %d\n",my_state->produced_prod[1]);
    printf("Number of produced P3: %d\n",my_state->produced_prod[2]);
    printf("Average number of P1 per minute: %f\n",my_state->produced_prod[0]/my_state->clock);
    printf("Average number of P2 per minute: %f\n",my_state->produced_prod[1]/my_state->clock);
    printf("Average number of P3 per minute: %f\n",my_state->produced_prod[2]/my_state->clock);
    printf("Idleness of inspector 1: %f\n", my_state->inspector1.idle_time/my_state->clock);
    printf("Idleness of inspector 2: %f\n", my_state->inspector2.idle_time/my_state->clock);

    if (fclose(csv_file) == 0){                             /* If the created file was closed without problem */
        return_var++;                                       /* Increment the return variable */
    } else{                                                 /* If there was a problem to close the file */
        printf("The file %s was created but it was not closed correctly",file_name); /* Display an error message */
        return return_var;                                  /* Return the variable with a value of zero */
    }

    return return_var;                                      /* Return the value of the return variable*/
}

/** \brief The function displays the main results of the simulator and creates .csv files with this information in a specific directory
 *
 * \param[in] my_config           configuration of the simulator
 * \param[in] my_state            state of the simulator
 * \param[in] param[out] output_directory   directory where the files will be saved
 * \return 0 if an error occurred during the execution, any other number represents the number of files created
 *
 */

int export_files(struct CONFIG my_config, struct STATE *my_state, char *output_directory){
    int return_var = 0;                 /* Initialize return variable of the function */
    char* file_name = "results";        /* Root of the file to create */
    char* extension = ".csv";           /* Extension of the file to create */
    char* full_filename = NULL;         /* Empty string*/
    int max_size_filename = 20;         /* Maximum size of the file name */
    struct stat folder_status = {0};    /* Initialize structure to save the output folder status */
    int model_type=my_config.model_type;/* Variable to save the model type from the configuration file */

    if (strlen(file_name)>max_size_filename){                       /* If the file name is bigger than 20 character */
        puts("The file name contains more than 20 characters\n");   /* Display an error message */
        return return_var;                                          /* Return the variable with a value of zero */
    }

    if (stat(output_directory, &folder_status)== -1 ){  /* If the output directory does not exist stat returns -1 */
        #ifdef __linux__                                /* If the operative system is based on Linux */
            mkdir(output_directory,0777);               /* Create directory with read, write, & execute for everyone */
        #else                                           /* If the operative system is based on Windows */
            mkdir(output_directory);                    /* Create directory with read, write, & execute for everyone */
        #endif
        return return_var;                              /* Return the variable with a value of zero */
    }

    //Assign a memory for the full directory name
    full_filename = malloc(strlen(output_directory)+max_size_filename); /* Allocate memory to save the the output path */
    strcpy(full_filename,output_directory);                             /* Copy output_directory string into full_filename */
    strcat(full_filename,file_name);                                    /* Concatenate the file_name string into full_filename */
    char model_type_char[]={'0' + model_type, '\0'};                    /* Convert model_type integer into char */
    strcat(full_filename,model_type_char);                              /* Concatenate the model_type into the full_filename */
    strcat(full_filename,extension);                                    /* Concatenate the extension into the full_filename */

    /* Print the title of the Simulation that was modeled */
    printf("------------- SIMULATION REPORT FOR MODEL %d -------------\n",model_type);
    /* Create and display the main results by calling the function export_csv*/
    if(export_csv((my_state+model_type),full_filename)>0){  /* If the value is bigger than 0 it means that the function created a file */
        return_var++;                                       /* Increment the return variable */
    }else{                                                  /* If a file was not successfully created */
        return return_var;                                  /* Return the variable with a value of zero */
    }

    return return_var;                                      /* Return the value of the return variable*/
}
