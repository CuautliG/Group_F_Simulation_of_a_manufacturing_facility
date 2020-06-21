#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/data_types.h"
#include "../include/read_data.h"

/** \brief Function to read the user input files \n
 * This function read a file and copy it values into an array.
 * \param c the variable that will store the inputs files
 * \param STR The name of the files that need to be opened
 * \param length the path where the input files are located
 * \return An array containing the user input files
 */
float *data(float *c, char STR[MAX_INPUT_SIZE], int *length){
        int return_var = 0;
        FILE *ins= fopen(STR,"r");                          /* Open the file containing the input values */
        if (ins == NULL)
        {
            printf("-->File %s not found in the directory \n", STR);
            return return_var = -1;
        }
        int i =0;                                           /* initialize counter */
        char oneline[MAX_CHAR_SIZE];                        /* initialize variable to copy the files */

        while (!feof(ins)) {                                /* while there is value that haven't been copied */
            fscanf(ins,"%8s",oneline);                      /*  Read the value and store it in the variable */
            c[i]=strtof(oneline,NULL);                      /* Store the value into a new array */
            i++;                                            /* Increment the counter */
        }
        *length=i-1;                                        /* Store the number of the values that have been copied */
        fclose(ins);                                        /* Close the file */

        return c;                                           /* Return the array containing the input files values */
}

/** \brief Function to save the read input files into the structure \n
 * This function initialize all the necessary components to read the files
 * \param input_directory the path where the input files are located
 * \param my_ptime the variable that will store the processing times
 * \param length_files the amount of values read from the files
 * \return length_files the amount of values read from the files
 */
int read_client_files(char *input_directory, struct PTIME *my_ptime,int length_files){
    int return_var = 0;
    float array[MAX_SIMULATION_LENGTH] = {'\0'};                                                         /* Array to store the values of the input files */
    char* components[] = {"ser1.dat", "ser2.dat", "ser3.dat", "ws1.dat", "ws2.dat", "ws3.dat"}; /* Array containing the name of the files to open */
    char long_str[NUMB_INPUT_FILES][MAX_INPUT_SIZE] = {'\0'};                                   /* Array containing the full path of the files to open */

    for (int i=0; i<NUMB_INPUT_FILES; i++)                              /* While all the name of the input files haven't been read */
    {
        strncat(long_str[i], input_directory, INPUT_DIRECTORY_SIZE);    /* Copy the files path in the array */
        strncat(long_str[i], components[i], MAX_ARRAY_SIZE);            /* Copy the files names in the array after the path */
    }

    my_ptime->comp1=data(array,long_str[0], &length_files);             /* Store the values of the input files into the structure */
    my_ptime->comp2=data(array,long_str[1], &length_files);             /* Store the values of the input files into the structure */
    my_ptime->comp3=data(array,long_str[2], &length_files);             /* Store the values of the input files into the structure */
    my_ptime->ws1=data(array,long_str[3], &length_files);               /* Store the values of the input files into the structure */
    my_ptime->ws2=data(array,long_str[4], &length_files);               /* Store the values of the input files into the structure */
    my_ptime->ws3=data(array,long_str[5], &length_files);               /* Store the values of the input files into the structure */
 /*   if (length_files < 0)
    {
      printf("-->The files do not contains any values");
      return return_var = -2;
    }*/

    return length_files;                                                /* Return the number of values retrieved */
}

/** \brief Function to initialize the necessary parameters to generate random values \n
 *
 * \param input_directory the path where the input files are located
 * \param my_config the user choices that will decide if the function will read from files or generate random inputs
 * \param my_ptime the variable that will store the processing times
 * \return 0 if an error occurs during the execution or 1 the files were properly read or generated.
 */
void generate_random_time (char *input_directory, struct CONFIG *my_config, struct PTIME* my_ptime){
    float array[MAX_SIMULATION_LENGTH] = {'\0'}; /* Array to store the values of the input files */

    my_ptime->comp1 = generate_random(array,  my_config);          /* Store the values that were randomly generated into the structure */
    my_ptime->comp2 = generate_random(array,  my_config);          /* Store the values that were randomly generated into the structure */
    my_ptime->comp3 = generate_random(array,  my_config);          /* Store the values that were randomly generated into the structure */
    my_ptime->ws1 = generate_random(array,  my_config);            /* Store the values that were randomly generated into the structure */
    my_ptime->ws2 = generate_random(array,  my_config);            /* Store the values that were randomly generated into the structure */
    my_ptime->ws3 = generate_random(array,  my_config);            /* Store the values that were randomly generated into the structure */
}

/** \brief Function to generate random number \n
 *
 * \param rand_numb the variable that will store the inputs files
 * \param my_config the user choices that will decide if the function will read from files or generate random inputs
 * \return rand_numb the array that contains the randomly generated values
 */

float *generate_random(float *rand_numb, struct CONFIG *my_config){
    int return_var = 0;
    float upper = my_config->upper_limit;                           /* Variable of the upper limit of the processing time */
    float lower = my_config->lower_limit;                           /* Variable of the lower limit of the processing time */
    if (lower > upper)
    {
        printf("-->The upper value need to be higher than the lower value\n");
        return return_var = -2;
    }

    if (my_config->sim_length < 0)
    {
        printf("-->The number of components need to be a positif number\n");
        return return_var = -3;
    }
    float ran_num_generator = 0;                                        /* Variable to store the generated number */
    printf("%d\n", my_config->sim_length);
    for(int i = 0; i<my_config->sim_length; i++)                    /* While the last value of the simulation length haven't been reached */
    {
    ran_num_generator = lower + (float)rand() / (RAND_MAX / (upper - lower ) + 1); /* Function to generate random values */
    rand_numb[i] = ran_num_generator;                               /* Store the generated random values in an array */
    }
    return rand_numb;                                               /* Return the array containing the generated values */
}

/** \brief Function to read or generate the inputs of the program \n
 * This function accept the user input and either read values from .dat files or generate random number between a range give by the user
 * \param input_directory the path where the input files are located
 * \param my_config the user choices that will decide if the function will read from files or generate random inputs
 * \param my_ptime the variable that will store the processing times
 * \return 0 if an error occurs during the execution or 1 the files were properly read or generated.
*/
int read_data(char *input_directory, struct CONFIG *my_config, struct PTIME *my_ptime){
    int return_var = 0;
    int length_files = 0;                                               /* the amount of values that will be read from the files */
    if (my_config->read_generate == 'r')                            /* If the choice is to read from user files */
        {
            if(read_client_files(input_directory, my_ptime,length_files)<=0){ /* If the function can't be called  */
                puts("Error reading the files\n");
            }else{
                my_config->sim_length=read_client_files(input_directory, my_ptime,length_files); /* Call the function to read user input files */
            }
        }
    else if (my_config->read_generate == 'g')                       /* If the choice is to generate random values */
        {
        generate_random_time (input_directory, my_config, my_ptime);/* Call the function to generate random values */
        }
    else
    {
        printf("-->The user choice is not valid\n");
        return return_var = -4;
    }

    }
