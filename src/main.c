/*! \mainpage Simulator of a Manufacturing Facility
 *
 * This is the introduction. \n
 * \n
 * The code is divided into the following functions: \n
 *
 * - \ref main function
 * - \ref export_files function
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/main.h"

/*!
 * \section main
 */

//Run Simulator
int run_simulator(struct CONFIG *my_config, char* input_directory, char* output_directory) {

    int data_var;
    int flow_var;
    int export_var;

    struct STATE *my_state=malloc(SIM_STATES*sizeof(struct STATE));
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    struct INSPECTOR my_inspector1={.id="1234",.name="PersonOne",.idle_time=0.00};
    struct INSPECTOR my_inspector2={.id="4321",.name="PersonTwo",.idle_time=0.00};

    for (int i=0; i<SIM_STATES; ++i){ //Initialize inspectors in my_state
        (my_state+i)->inspector1=my_inspector1;
        (my_state+i)->inspector2=my_inspector2;
    }

    data_var = read_data(input_directory, my_config, my_ptime);

    //print_ptime(my_config, my_ptime);

    flow_var = work_flow(my_config,my_ptime,my_state);

    //print_state(my_state+my_config->model_type);

    export_var= export_files(my_config, my_state, output_directory);

    free(my_state);
    free(my_ptime);
    return 0;
}

//Main Function
int main(int argc, char* argv[]) {
    char* config_name=      "./data/config.cfg";    // The output directory
    char* input_directory=  "./data/input/";        // The output directory
    char* output_directory= "./data/output/";       // The output directory
    struct CONFIG my_config={.both_models=0,.model_type=2,.read_generate='r',.sim_length=MAX_SIMULATION_LENGTH,.lower_limit=10.0,.upper_limit=15.0};
    struct CONFIG *config = &my_config;
    //struct CONFIG *my_config=malloc(sizeof(struct CONFIG));
    //struct CONFIG *config = &my_config;
    //read_config(config_name,my_config);
    int actual_arg=1;   //Initialize the actual argument at 1
    while(actual_arg<argc) {
        if(*argv[actual_arg]=='-') { //If the argument starts with -
            if(strcmp(argv[actual_arg],"-v")==0) {
                printf("Manufacturing Facility Simulator V 1.0\n");
                printf("Options:\n");
                printf("-v : Display the version of the program and its options\n");
                printf("-m : Allows to enter the initial values of the simulator manually\n");
                printf("-c (filename)  : Allows to set the name of the configuration file. Default is %s\n",config_name);
                printf("-i (directory) : Allows to set the input directory.                Default is %s\n",input_directory);
                printf("-o (directory) : Allows to set the output directory.               Default is %s\n",output_directory);
                break;
            } else if(strcmp(argv[actual_arg],"-m")==0){
                config->model_type=0;
                config->read_generate='\0';
                config->upper_limit=0;
                config->lower_limit=0;
                while ((config->model_type != 1) && (config->model_type != 2)){
                    puts("Please enter the choice of model you want for the simulation:\n");
                    puts("1: The current/old model\n");
                    puts("2: The proposed model\n");
                    scanf("%d",&config->model_type);
                if ((config->model_type != 1) && (config->model_type != 2)) {
                    puts("please type 1 or 2\n");
                }
                }

                while ((config->read_generate != 'r') && (config->read_generate != 'g')){
                    puts("Please enter the choice of input method you want for the simulation:\n");
                    puts("r: Import processing times from your file\n");
                    puts("g: Generate processing times randomly \n");
                    scanf(" %c",&config->read_generate);
                    if ((config->read_generate != 'r') && (config->read_generate != 'g')) {
                        puts("please type r or g\n");
                    }
                    if (config->read_generate=='g'){
                        while (config->upper_limit <= config->lower_limit) {
                            printf("please insert the lower limit of process time: ");
                            scanf("%f",&config->lower_limit);
                            printf("please insert the upper limit of process time: ");
                            scanf("%f",&config->upper_limit);
                        }
                    printf("please enter the number of components of each type for simulation:");
                    scanf("%d",&config->sim_length);
                    }else{
                    config->sim_length=MAX_SIMULATION_LENGTH;
                }
                }
                actual_arg++;
            }else if(strcmp(argv[actual_arg],"-c")==0) {
                actual_arg++;
                if(*argv[actual_arg]!='-') {
                    config_name=argv[actual_arg];
                    printf("The configuration file was set to: %s\n",config_name);
                    break;
                }
            }else if(strcmp(argv[actual_arg],"-i")==0) {
                actual_arg++;
                if(*argv[actual_arg]!='-') {
                    input_directory=argv[actual_arg];
                    printf("The input directory was set to: %s\n",input_directory);
                    break;
                }
            }else if(strcmp(argv[actual_arg],"-o")==0) {
                actual_arg++;
                if(*argv[actual_arg]!='-') {
                    output_directory=argv[actual_arg];
                    printf("The output directory was set to: %s\n",output_directory);
                    break;
                }
            }else {
                printf("Invalid option: %s\n",argv[actual_arg]);
                break;
            }
        }else {
            printf("The argument '%s' is not valid it must start with '-'\n",argv[actual_arg]);
            break;
        }
    }
    return run_simulator(config, input_directory, output_directory);
}
