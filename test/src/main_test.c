#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_types.h"

//Run Simulator
int main() {
//struct CONFIG *my_config, char* input_directory, char* output_directory
    int data_var;
    int flow_var;
    int export_var;

    struct STATE *my_state=malloc(SIM_STATES*sizeof(struct STATE));
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    struct INSPECTOR my_inspector1={.id="1234",.name="PersonOne",.idle_time=0.00};
    struct INSPECTOR my_inspector2={.id="4321",.name="PersonTwo",.idle_time=0.00};

    printf("------------- Testing export_files -------------\n");
    export_var= export_files_test();


    free(my_state);
    free(my_ptime);
    return 0;
}
