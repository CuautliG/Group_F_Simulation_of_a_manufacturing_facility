#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/data_types.h"
#include "../../include/read_data.h"

/**
 * The function test all the functions inside read_data and shows the results
 */

int return_var = 0;                 /* Variable of the returns value */
float array[MAX_SIMULATION_LENGTH]; /* Array to store the values of the input files */

int read_data_test()
{
    printf("Error 1\n");
    test_error_1();                 /* Function to test the error 1 */

    printf("Error 2\n");
    test_error_2();                 /* Function to test the error 2 */

    printf("Error 3\n");
    test_error_3();                 /* Function to test the error 3 */

    printf("Error 4\n");
    test_error_4();                 /* Function to test the error 4 */
}

int test_error_1()
{
    int length = 0;                 /* the amount of values that will be read from the files */
    char wrong_char[] = "./data/input/ser12.dat";           /* Array that contains the input file name */
    data(array, wrong_char, &length);   /* Function that read the input files */
    return return_var;
}

int test_error_2()
{
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    my_config->lower_limit = 10;                     /* Lower limit of the randomly generated number */
    my_config->upper_limit = 8;                      /* Upper limit of the randomly generated number */
    generate_random(array, my_config);               /* Function to generate random values */
    return return_var;
}

int test_error_3()
{
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    my_config->lower_limit = 10;                    /* Lower limit of the randomly generated number */
    my_config->upper_limit = 15;                    /* Upper limit of the randomly generated number */
    my_config->sim_length = -1;                     /* Number of component choose by the user */
    generate_random(array, my_config);              /* Function to generate random values */
    return return_var;
}

int test_error_4()
{
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    my_config->read_generate = 'd';                     /* Choice to read from files or generate random numbers */
    read_data("./data/input/", my_config, my_ptime);    /* Function to decide whether to read from file or generate randomly */
    return return_var;
}
