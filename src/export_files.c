#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/data_types.h"
#include "../include/export_files.h"
#include "../include/common_functions.h"

/** \brief Function to export the analysis of the simulator. \n
 * This function reads the states of the simulators and analyze both model to determinate which model is better.
 * The analysis is based on the produced products, used components and idleness of the inspectors. It creates a csv file called analysis
 * \param[in] my_state is the state of the simulator on a specific model
 * \param[in] file_name is the name of the csv file to create
 * \return 1 if the file was successfully created, -3 if there was an error with the size of the file_name,
 *     -4 if there was an error while writing the file
 */
int export_analysis(struct STATE *my_state , char *file_name){
    int return_var = 0;                                     /* Initialize return variable of the function */
    int max_size_filename = MAX_SIZE_FILENAME;              /* Maximum size of the file name */
    int new_model = 0;                                      /* Variable to save points for the new model*/
    int old_model =0;                                       /* Variable to save points for the old model*/
    int sim_lenght=(my_state+2)->sim_length;                /* Simulation length*/
    float idle_inspector_new= 0.0;                          /* Idleness of the inspector in the new model*/
    float idle_inspector_old= 0.0;                          /* Idleness of the inspector in the old model*/
    int used_component[3]={0,0,0};                          /* To save the used components of the new and old model*/
    int produced_prod[3]={0,0,0};                           /* To save the produces products of the new and old model*/

    if (strlen(file_name)>max_size_filename){               /* If the file name is bigger than 30 character */
        printf("The function export_analysis received file_name=%s\n",file_name);
        printf("->The function export_analysis needs a file_name smaller than 30 characters\n"); /* Display an error message */
        return return_var = -3;                             /* Return the variable with a value of -3 */
    }

    FILE *csv_file = NULL;                                  /* Pointer to reference the output file */
    csv_file=fopen(file_name,"w");                          /* Open the file in write mode */

    if (csv_file == NULL){                                  /* If the file cannot be opened*/
        printf("The function export_analysis received a NULL file\n");
        printf("->Most probable the file is opened and the program cannot write\n"); /* Display an error message */
        return return_var = -4;                             /* Return the variable with a value of -4 */
    }
    /* Addition of the idleness of both inspectors */
    idle_inspector_new= ((my_state+2)->inspector1.idle_time/(my_state+2)->clock)+((my_state+2)->inspector2.idle_time/(my_state+2)->clock);
    idle_inspector_old= ((my_state+1)->inspector1.idle_time/(my_state+1)->clock)+((my_state+1)->inspector2.idle_time/(my_state+1)->clock);
    /* Addition of old the components of products produced in each model*/
    for (int comp=0;comp<PRODUCTS;comp++){
        used_component[1]+=(my_state+1)->used_component[comp];
        used_component[2]+=(my_state+2)->used_component[comp];
        produced_prod[1]+=(my_state+1)->produced_prod[comp];
        produced_prod[2]+=(my_state+2)->produced_prod[comp];
    }

    /* Print Analysis */
    fprintf(csv_file,"------------- ANALYSIS REPORT FOR SIMULATOR -------------\n");
    printf("\n------------- ANALYSIS REPORT FOR SIMULATOR -------------\n");
    fprintf(csv_file,"Number of components of each types ready for the simulations was: %d\n",sim_lenght);
    printf("Number of components of each types ready for the simulations was: %d\n",sim_lenght);
    /* Comparative between produces products */
    for (int comp=0;comp<PRODUCTS;comp++){
          fprintf(csv_file,"The proposed model produced %d ",(my_state+2)->produced_prod[comp]);
          fprintf(csv_file,"products %d while the old model produced %d products %d\n",comp+1,(my_state+1)->produced_prod[comp],comp+1);
          printf("The proposed model produced %d ",(my_state+2)->produced_prod[comp]);
          printf("products %d while the old model produced %d products %d\n",comp+1,(my_state+1)->produced_prod[comp],comp+1);
    }
    /* Comparative total of produced products */
    fprintf(csv_file,"In total the proposed model produced %d ", produced_prod[2]);
    printf("In total the proposed model produced %d ", produced_prod[2]);
    fprintf(csv_file,"while the old model produced %d \n", produced_prod[1]);
    printf("while the old model produced %d \n", produced_prod[1]);
    /* Comparative total of used products */
    fprintf(csv_file,"In total the proposed model used %d components ", used_component[2]);
    printf("In total the proposed model used %d components ", used_component[2]);
    fprintf(csv_file,"while the old model used %d components\n", used_component[1]);
    printf("while the old model used %d components\n", used_component[1]);
    /* Comparative total of idleness average per model */
    fprintf(csv_file,"The idleness of inspectors in the proposed model was of %f\n", idle_inspector_new/2);
    printf("The average idleness of inspectors in the proposed model was of %f\n", idle_inspector_new/2);
    fprintf(csv_file,"The idleness of inspectors in the proposed model was of %f\n", idle_inspector_old/2);
    printf("The average idleness of inspectors in the proposed model was of %f\n", idle_inspector_old/2);

    if(idle_inspector_new<idle_inspector_old){  /* If the new model is better*/
        new_model++;
    }else{                                      /* If the old model is better */
        old_model++;
    }
    if(produced_prod[2]>=produced_prod[1]){      /* If the new model is better*/
        new_model++;
    }else{                                      /* If the old model is better */
        old_model++;
    }
    if(used_component[2]>used_component[1]){    /* If the new model is better*/
        new_model++;
    }else{                                      /* If the old model is better */
        old_model++;
    }
    if(new_model>old_model){                    /* If the new model got more points */
        fprintf(csv_file,"Thus the proposed model is better than the old model\n\n");
        printf("Thus, the proposed model is better than the old model\n\n");
    }else{                                      /* If the old model got more points */
        fprintf(csv_file,"Thus the old model is better than the proposed model\n\n");
        printf("Thus, the old model is better than the proposed model\n\n");
    }

    if (fclose(csv_file) == 0){                             /* If the created file was closed without problem */
        return_var++;                                       /* Increment the return variable */
    } else{                                                 /* If there was a problem to close the file */
        printf("The file %s was created but it was not closed correctly",file_name); /* Display an error message */
        return return_var;                                  /* Return the variable with a value of zero */
    }

    return return_var;

}

/** \brief Function to export the main results of the simulator. \n
 * This function reads the state structure and displays the main results of the simulator. These results are also exported into
 * a file called results1.csv or results2.csv depending of the model type that the simulator run.
 * \param[in] my_state is the state of the simulator on a specific model
 * \param[in] file_name is the name of the csv file to create
 * \return 1 if the file was successfully created, -3 if there was an error with the size of the file_name,
 *     -4 if there was an error while writing the file
 */
int export_csv(struct STATE *my_state , char *file_name, int both_models){
    int return_var = 0;                                     /* Initialize return variable of the function */
    int max_size_filename = MAX_SIZE_FILENAME;              /* Maximum size of the file name */

    if (strlen(file_name)>max_size_filename){                       /* If the file name is bigger than 20 character */
        printf("The function export_csv received file_name=%s\n",file_name);
        printf("->The function export_csv needs a file_name smaller than 30 characters\n"); /* Display an error message */
        return return_var = -3;                                          /* Return the variable with a value of zero */
    }

    FILE *csv_file = NULL;                                  /* Pointer to reference the output file */
    csv_file=fopen(file_name,"w");                          /* Open the file in write mode */
    int var_write=write_file(my_state,csv_file);            /* Try to write the main results in the csv file */
    if(var_write==0){                                       /* If the function wrote the info correctly */
        if(both_models==0){
            print_state(my_state);                          /* Display the main results of the simulator state */
        }else{
            printf("The report %s was correctly saved \n",file_name);
        }
    }else{                                                  /* If there was an error with the file */
        return return_var = var_write;                      /* Return the error into the function */
    }

    if (fclose(csv_file) == 0){                             /* If the created file was closed without problem */
        return_var++;                                       /* Increment the return variable */
    } else{                                                 /* If there was a problem to close the file */
        printf("The file %s was created but it was not closed correctly",file_name); /* Display an error message */
        return return_var;                                  /* Return the variable with a value of zero */
    }

    return return_var;                                      /* Return the value of the return variable*/
}

/** \brief Function that writes the values of my_state. \n
 * This function takes the information in each filed inside the my_state and it writes the information in the given FILE
 * \param[in] file is a pointer to the file to create
 * \param[in] my_state is the state of the simulator on a specific model
 * \return 0 if the file was successfully created, -4 if the pointer to the file was NULL
 */
int write_file(struct STATE *my_state, FILE *file){
    int return_var = 0;                                     /* Initialize return variable of the function */
    if (file == NULL){
        printf("The function write_file received a NULL file\n");
        printf("->The function write_file needs a FILE pointer of an opened file\n"); /* Display an error message */
        return return_var = -4;
    }
    fprintf(file,"------------- SIMULATION REPORT FOR MODEL %d -------------\n",my_state->model_type);
    fprintf(file,"Number of components of each types ready for the simulation: %d\n",my_state->sim_length);
    fprintf(file,"Simulation time: %f\n",my_state->clock);
    fprintf(file,"Number of C1 used for simulation: %d\n",my_state->used_component[0]);
    fprintf(file,"Number of C2 used for simulation: %d\n",my_state->used_component[1]);
    fprintf(file,"Number of C3 used for simulation: %d\n",my_state->used_component[2]);
    fprintf(file,"Number of C1 unused for simulation: %d\n",my_state->unused_component[0]);
    fprintf(file,"Number of C2 unused for simulation: %d\n",my_state->unused_component[1]);
    fprintf(file,"Number of C3 unused for simulation: %d\n",my_state->unused_component[2]);
    fprintf(file,"Number of produced P1: %d\n",my_state->produced_prod[0]);
    fprintf(file,"Number of produced P2: %d\n",my_state->produced_prod[1]);
    fprintf(file,"Number of produced P3: %d\n",my_state->produced_prod[2]);
    fprintf(file,"Average number of P1 per minute: %f\n",my_state->produced_prod[0]/my_state->clock);
    fprintf(file,"Average number of P2 per minute: %f\n",my_state->produced_prod[1]/my_state->clock);
    fprintf(file,"Average number of P3 per minute: %f\n",my_state->produced_prod[2]/my_state->clock);
    fprintf(file,"Idleness of inspector 1: %f\n", my_state->inspector1.idle_time/my_state->clock);
    fprintf(file,"Idleness of inspector 2: %f\n", my_state->inspector2.idle_time/my_state->clock);
    return return_var;
}

/** \brief This function that creates reports. \n
 * The function calls another functions to create individual reports and the analyzes of the simulator based on my_state
 * \param[in] my_config is the configuration that the simulator uses to run
 * \param[in] my_state is the states of the simulator
 * \param[in] output_directory is the directory where the simulator saves the generated files
 * \return -1 if there was an error in my_config, -2 if there was an error in my_state, -3 if there was an error with the size of the file_name,
 *     -4 if there was an error while writing the file
 */
int export_files(struct CONFIG *my_config, struct STATE *my_state, char *output_directory){
    int return_var = 0;                  /* Initialize return variable of the function */
    char* file_name = "results";         /* Root of the file to create */
    char* file_name_analysis = "analysis.csv";/* Root of the file to create */
    char* extension = ".csv";            /* Extension of the file to create */
    char* full_filename = NULL;          /* Empty string*/
    struct stat folder_status = {0};     /* Initialize structure to save the output folder status */
    int model_type=0;                    /* Variable to initialize the model type */
    int both_models=my_config->both_models;/* Variable to save if both models or not will be simulated */
    int times;

    if(both_models==1){ /* If both models are required */
        times=2;        /* It will run two times*/
    }else{
        times=1;        /* It will run one time */
    }

    for(int act_model=0;act_model<times;act_model++){
        if(times==1){ /* one time read the config file */
            model_type=my_config->model_type; /* Choice from configuration file */
        }else{
            model_type=act_model+1; /* Run old and new model that are saved in position 1 and 2 of the array */
        }

    if ((both_models!=0 && both_models!=1) || (model_type!=1 && model_type!=2) ){
        printf("The function export_files received ");
        printf("both_models=%d and model_type=%d\n",both_models,model_type);
        printf("->The function export_files needs 0 or 1 for both_models and 1 or 2 for model_type\n");
        return return_var = -1;
    }

    if((my_state+model_type)->sim_length<=0 || (my_state+model_type)->clock<=0){      /* If the simulation length or clock are smaller or equal than zero */
        printf("The function export_files received ");
        printf("sim_length=%d and clock=%d\n",(my_state+model_type)->sim_length,(my_state+model_type)->clock);/* Display an error message */
        printf("->The function export_files needs positive integers bigger than 0 to work properly\n");
        return return_var = -2;                      /* Return the variable with a value of zero */
    }

    if (stat(output_directory, &folder_status)== -1 ){  /* If the output directory does not exist stat returns -1 */
            mkdir(output_directory,0777);               /* Create directory with read, write, & execute for everyone */
    }

    //Assign a memory for the full directory name
    full_filename = malloc(strlen(output_directory)+MAX_SIZE_FILENAME); /* Allocate memory to save the the output path */
    strcpy(full_filename,output_directory);                             /* Copy output_directory string into full_filename */
    strcat(full_filename,file_name);                                    /* Concatenate the file_name string into full_filename */
    char model_type_char[]={'0' + model_type, '\0'};                    /* Convert model_type integer into char */
    strcat(full_filename,model_type_char);                              /* Concatenate the model_type into the full_filename */
    strcat(full_filename,extension);                                    /* Concatenate the extension into the full_filename */

    /* Create and display the main results by calling the function export_csv*/
    if(export_csv((my_state+model_type),full_filename,both_models)>0){  /* If the value is bigger than 0 it means that the function created a file */
        return_var++;                                       /* Increment the return variable */
    }else{                                                  /* If a file was not successfully created */
        return return_var;                                  /* Return the variable with a value of zero */
    }
    free(full_filename);
    } /* End of the for */

    if(both_models==1){ /* If the simulator run twice */
        //Assign a memory for the full directory name
        full_filename = malloc(strlen(output_directory)+MAX_SIZE_FILENAME); /* Allocate memory to save the the output path */
        strcpy(full_filename,output_directory);                             /* Copy output_directory string into full_filename */
        strcat(full_filename,file_name_analysis);                           /* Concatenate the file_name_analysis string into full_filename */

        if(export_analysis(my_state,full_filename)>0){  /* If the value is bigger than 0 it means that the function created a file */
            return_var++;                               /* Increment the return variable */
        }else{                                          /* If a file was not successfully created */
            return return_var;                          /* Return the variable with a value of zero */
        }
    }else{
        return return_var;                              /* Return the value of the return variable*/
    }
}
