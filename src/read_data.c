#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/data_types.h"
#include "../include/read_data.h"

/** \brief Function to read the user input files \n
 * This function read a file and copy it values into an array.
 * \param[in] times is a pointer where the values from the inputs files are saved
 * \param[in] STR is the name of the file that need to be opened
 * \param[in,out] length is the quantity of processing times that the function read
 * \return An array containing the processing time of the files which are positive
 *     or an array that the only value given is the first element as -1
 */
float *data(float *times, char STR[MAX_INPUT_SIZE], int *length){
        int return_var = 0;
        FILE *ins= fopen(STR,"r");                          /* Open the file containing the input values */
        if (ins == NULL){
            printf("The function data did not find the file %s\n",STR);
            printf("->The function data needs a existent pointer to file\n"); /* Display an error message */
            times[0] = -1.0;                                /* Assign -1.0 for the error to the first element of the array */
            length=0;                                       /* If the error length equal to zero */
            return times;                                   /* Return value */
        }
        int i =0;                                           /* initialize counter */
        char oneline[MAX_CHAR_SIZE];                        /* initialize variable to copy the files */

        while (!feof(ins)) {                                /* while there is value that haven't been copied */
            fscanf(ins,"%8s",oneline);                      /*  Read the value and store it in the variable */
            times[i]=strtof(oneline,NULL);                      /* Store the value into a new array */
            i++;                                            /* Increment the counter */
        }
        *length=i-1;                                        /* Store the number of the values that have been copied */
        fclose(ins);                                        /* Close the file */

        return times;                                       /* Return the array containing the input files values */                                          /* Return the array containing the input files values */
}

/** \brief Function to save the read input files into the structure \n
 * This function initialize all the necessary components to read the files
 * \param[in] input_directory is the directory where the input files are saved
 * \param[in,out] my_ptime is a pointer where the processing times are saved
 * \param[in,out] length_files is the quantity of processing times that the function read
 * \return The length of the files and it updates the values of my_ptime.
 *     If the length of the files is equal 0, it means that there was a problem reading a file
 */
int read_client_files(char *input_directory, struct PTIME *my_ptime,int length_files){
    float array1[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array2[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array3[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array4[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array5[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array6[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    char* components[] = {"ser1.dat", "ser2.dat", "ser3.dat", "ws1.dat", "ws2.dat", "ws3.dat"}; /* Array containing the name of the files to open */
    char long_str[NUMB_INPUT_FILES][MAX_INPUT_SIZE] = {'\0'};                                   /* Array containing the full path of the files to open */

    for (int i=0; i<NUMB_INPUT_FILES; i++)                              /* While all the name of the input files haven't been read */
    {
        strncat(long_str[i], input_directory, INPUT_DIRECTORY_SIZE);    /* Copy the files path in the array */
        strncat(long_str[i], components[i], MAX_ARRAY_SIZE);            /* Copy the files names in the array after the path */
    }

    my_ptime->comp1=data(array1,long_str[0], &length_files);             /* Store the values of the input files into the structure */
    my_ptime->comp2=data(array2,long_str[1], &length_files);             /* Store the values of the input files into the structure */
    my_ptime->comp3=data(array3,long_str[2], &length_files);             /* Store the values of the input files into the structure */
    my_ptime->ws1=data(array4,long_str[3], &length_files);               /* Store the values of the input files into the structure */
    my_ptime->ws2=data(array5,long_str[4], &length_files);               /* Store the values of the input files into the structure */
    my_ptime->ws3=data(array6,long_str[5], &length_files);               /* Store the values of the input files into the structure */

    return length_files;                                                /* Return the number of values retrieved */
}

/** \brief Function saves my_ptime when are random values \n
 * This functions assign the processing time in a specific place in my_ptime
 * \param[in] input_directory the path where the input files are located
 * \param[in] my_config is the configuration that the simulator uses to run
 * \param[in,out] my_ptime is a pointer to array where the processing times are saved
 * \return 0 if my_ptime was update successfully, -2 if there was a problem with the limits in the configuration file,
 *     -3 if there was a problem with the simulation length.
 */
int generate_random_time (char *input_directory, struct CONFIG *my_config, struct PTIME* my_ptime){
    int return_var = 0;
    float array1[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array2[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array3[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array4[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array5[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */
    float array6[MAX_SIMULATION_LENGTH];                                                         /* Array to store the values of the input files */

    my_ptime->comp1 = generate_random(my_config,array1);          /* Store the values that were randomly generated into the structure */
    my_ptime->comp2 = generate_random(my_config,array2);          /* Store the values that were randomly generated into the structure */
    my_ptime->comp3 = generate_random(my_config,array3);          /* Store the values that were randomly generated into the structure */
    my_ptime->ws1 = generate_random(my_config,array4);            /* Store the values that were randomly generated into the structure */
    my_ptime->ws2 = generate_random(my_config,array5);            /* Store the values that were randomly generated into the structure */
    my_ptime->ws3 = generate_random(my_config,array6);            /* Store the values that were randomly generated into the structure */

    /* If the first element of any of the processing times is equal -2 it means there was a problem with the limits*/
    if (my_ptime->comp1[0]==-2.00||my_ptime->comp2[0]==-2.00||my_ptime->comp3[0]==-2.00||my_ptime->ws1[0]==-2.00||my_ptime->ws1[0]==-2.00||my_ptime->ws1[0]==-2.00){
        return return_var = -2;                                 /* Return value */
    }
    /* If the first element of any of the processing times is equal -3 it means there was a problem with the simulation length*/
    if (my_ptime->comp1[0]==-3.00||my_ptime->comp2[0]==-3.00||my_ptime->comp3[0]==-3.00||my_ptime->ws1[0]==-3.00||my_ptime->ws1[0]==-3.00||my_ptime->ws1[0]==-3.00){
        return return_var = -3;                                 /* Return value */
    }
    return return_var;
}

/** \brief Function to generate random number \n
 * This function uses the configuration file to create an array of random values
 * \param[in] my_config is the configuration that the simulator uses to run
 * \param[in] rand_numb is a pointer where the processing times are saved
 * \return An array containing the processing time of the files which are positive or an array that the only
 *     value given is the first element as -2 or -3. -2 for a problems with the limits and -3 for problem with the simulation length
 */
float *generate_random(struct CONFIG *my_config,float *rand_numb){
    float upper = my_config->upper_limit;                           /* Variable of the upper limit of the processing time */
    float lower = my_config->lower_limit;                           /* Variable of the lower limit of the processing time */
    if (lower > upper){
        printf("The function generate_random received upper_limit=%d and lower_limit=%d\n",upper,lower);
        printf("->The function generate_random needs the upper value need to be higher than the lower value\n");
        rand_numb[0] = -2.0;
        return rand_numb;
    }

    if (my_config->sim_length < 0){
        printf("The function generate_random received sim_length=%d\n",my_config->sim_length);
        printf("->The function generate_random needs the number of components need to be a positive number\n");
        rand_numb[0] = -3.0;
        return rand_numb;
    }
    float ran_num_generator = 0;                                        /* Variable to store the generated number */
    for(int i = 0; i<my_config->sim_length; i++)                    /* While the last value of the simulation length haven't been reached */
    {
    ran_num_generator = lower + (float)rand() / (RAND_MAX / (upper - lower ) + 1); /* Function to generate random values */
    rand_numb[i] = ran_num_generator;                               /* Store the generated random values in an array */
    }
    return rand_numb;                                               /* Return the array containing the generated values */
}

/** \brief Function to read or generate the inputs of the program \n
 * This function accept the user input and either read values from .dat files or generate random number between a range give by the user
 * \param[in] input_directory is the directory where the input files are saved
 * \param[in,out] my_config is the configuration that the simulator uses to run
 * \param[in,out] my_ptime is a pointer to array where the processing times are saved
 * \return 1 the files were properly read or generated. -1 If there was a problem reading the data. -2 if there was a problem with
 *     the limits in the configuration file, -3 if there was a problem with the simulation length and -4 if the option for read_generate
 *     is different than 'r' and 'g'.
*/
int read_data(char *input_directory, struct CONFIG *my_config, struct PTIME *my_ptime){
    int generate_var = 0;
    int return_var = 0;
    int length_files = 0;                                               /* the amount of values that will be read from the files */
    if (my_config->read_generate == 'r'){                               /* If the choice is to read from user files */
            if(read_client_files(input_directory, my_ptime,length_files)<=0){ /* If the function can't be called  */
                return return_var = -1; /* Error reading files */
            }else{
                my_config->sim_length=read_client_files(input_directory, my_ptime,length_files); /* Call the function to read user input files */
            }
    } else if (my_config->read_generate == 'g') {                   /* If the choice is to generate random values */
        generate_var = generate_random_time (input_directory, my_config, my_ptime);/* Call the function to generate random values */
        if(generate_var<0){                                         /* If there was an error */
                return return_var = generate_var;
        }
    } else {
        printf("The function read_data received read_generate=%c\n",my_config->read_generate);
        printf("->The function read_data needs that the variable read_generate has the character 'r' or 'g'\n");
        return return_var = -4;
    }
    return return_var=1;
}
