#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/read_config.h"
#include "../include/read_config_test.h"

 int read_config_test(){
    char* config_name = "./test/data/config.cfg";    /* Default configuration file */
    char* config_no_exist = "./test/data/confi.cfg";    /* Default configuration file */
    char* config_no_input_valid = "./test/data/config1.cfg";    /* Default configuration file */
    char* config_no_token = "./test/data/config2.cfg";    /* Default configuration file */
    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    int value=0;

    printf("Error -1 :\n");
    printf("Return value from data() was %d\n\n",read_config(config_no_exist,my_config));

    printf("Error -2 :\n");
    printf("Return value from data() was %d\n\n",read_config(config_no_input_valid,my_config));

    printf("Error -3 :\n");
    printf("Return value from data() was %d\n\n",read_config(config_no_token,my_config));

    printf("No errors :\n");
    printf("Return value from data() was %d\n\n",read_config(config_name,my_config));

    free(my_config);
    return 0;
 }
