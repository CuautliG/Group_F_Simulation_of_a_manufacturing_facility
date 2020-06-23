#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/data_types.h"
#include "../../include/read_data.h"
#include "../include/read_data_test.h"


int return_var = 0;                 /* Variable of the returns value */
float *test;
float array[MAX_SIMULATION_LENGTH]; /* Array to store the values of the input files */

/**
 * The function test all the functions inside read_data and shows the results
 */
int read_data_test(){
    printf("Error -1 :\n");
    printf("Return value from data() was %d\n\n",test_error_1());

    printf("Error -2 :\n");
    printf("Return value from generate_random() was %d\n\n",test_error_2());

    printf("Error -3 :\n");         /* Function to test the error 3 */
    printf("Return value from generate_random() was %d\n\n",test_error_3());

    printf("Error -4 :\n");         /* Function to test the error 4 */
    printf("Return value from read_data() was %d\n\n",test_error_4());

    printf("No errors : \n");       /* Function to test the no errors */
    printf("Return value from read_data() was %d\n\n",test_no_error());
}

int test_error_1() {  /* File does not exist */
    int length = 0;                 /* the amount of values that will be read from the files */
    char wrong_char[] = "./data/input/ser12.dat";           /* Array that contains the input file name */
    test = data(array, wrong_char, &length);   /* Function that read the input files */
    return return_var=(int)test[0];
}

int test_error_2(){
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    my_config->lower_limit = 10;                     /* Lower limit of the randomly generated number */
    my_config->upper_limit = 6;                      /* Upper limit of the randomly generated number */
    test = generate_random(my_config, array);               /* Function to generate random values */
    free(my_config);
    return return_var=(int)test[0];
}

int test_error_3(){
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    my_config->lower_limit = 10;                    /* Lower limit of the randomly generated number */
    my_config->upper_limit = 15;                    /* Upper limit of the randomly generated number */
    my_config->sim_length = -1;                     /* Number of component choose by the user */
    test = generate_random(my_config, array);              /* Function to generate random values */
    free(my_config);
    return return_var=(int)test[0];
}

int test_error_4(){
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    my_config->read_generate = 'd';                     /* Choice to read from files or generate random numbers */
    return_var = read_data("./data/input/", my_config, my_ptime);    /* Function to decide whether to read from file or generate randomly */
    free(my_config);
    free(my_ptime);
    return return_var;
}

int test_no_error(){
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    my_config->read_generate = 'r';                     /* Choice to read from files or generate random numbers */
    return_var = read_data("./data/input/", my_config, my_ptime);    /* Function to decide whether to read from file or generate randomly */
    free(my_config);
    free(my_ptime);
    return return_var;
}
