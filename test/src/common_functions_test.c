#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_types.h"
#include "../../include/read_config.h"

/*struct CONFIG* set_config_test(){

    struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    //struct CONFIG *config = &my_config;
    //read_config(config_name,my_config);




}*/

void set_state_test(struct CONFIG *my_config,struct STATE *my_state){
    char* config_name=      "./data/config.cfg";    // The output directory
    char* input_directory=  "./data/input/";    // The output directory
    read_config(config_name,my_config);
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    struct INSPECTOR my_inspector1={.id="1234",.name="PersonOne",.idle_time=0.00};
    struct INSPECTOR my_inspector2={.id="4321",.name="PersonTwo",.idle_time=0.00};

    for (int i=0; i<SIM_STATES; ++i){ //Initialize inspectors in my_state
        (my_state+i)->inspector1=my_inspector1;
        (my_state+i)->inspector2=my_inspector2;
    }

    read_data(input_directory, my_config, my_ptime);
    work_flow(my_config,my_ptime,my_state);


};
