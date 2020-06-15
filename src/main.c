#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/main.h"

//Run Simulator
int run_simulator(struct CONFIG my_config) {
    printf("Model type: %d",my_config.model_type);

    struct STATE *my_state=malloc(MAX_SIMULATION_LENGTH*sizeof(struct STATE));
    struct INSPECTOR inspector1={.id="2351",.name="Cuau",.type=2};
    struct PTIME *my_ptime=malloc(MAX_SIMULATION_LENGTH*sizeof(struct STATE));

    for (int i=0; i<my_config.simlength; i++){
        (my_state+i)->model = my_config.model_type;
        (my_state+i)->sim_length = my_config.simlength;
        (my_state+i)->iteration = i;
        (my_state+i)->produced_prod = i%2;
        (my_state+i)->inspectors =inspector1;
        (my_ptime+i)->comp1=i*i;
    }

    for (int i=0; i<my_config.simlength; i++){
        printf("iteration is: %d\n",(my_state+i)->iteration);
        //printf("sdf: %s\n",(my_state+i)->inspectors.id);
        printf("ptime is: %d\n",(my_ptime+i)->comp1);
    }


        //printf("inspector name: %s",my_state->inspectors);
    //printf("pointer iteration is: %d\n",(my_state+100)->iteration);
    //printf("pointer iteration is: %d\n",(my_state+47)->iteration);


    /*int functiondavid = 0;
    int functionhai = 0;

    functiondavid = int read_data(input_directory, struct CONFIG my_config, struct **my_ptime);
    if (functiondavid==0){
        break;
    }

    functionhai=int work_flow(char *config_file, struct **my_ptime, struct STATE *my_state, struct SUB_STATE **subsystem);
    if (functionhai==0){
        break;
    }*/

    return 0;
}

//Main Function
int main(int argc, char* argv[]) {
    char* config_name=      "./data/config.cfg";    // The output directory
    char* input_directory=  "./data/input/";        // The output directory
    char* output_directory= "./data/output/";       // The output directory
    struct CONFIG config={.both_models=0,.model_type=2,.read_generate='r',.simlength=MAX_SIMULATION_LENGTH,.lolimit=10,.uplimit=15};
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
            config.model_type=0;
            config.read_generate='\0';
                while ((config.model_type != 1) && (config.model_type != 2)){
                    puts("Please enter the choice of model you want for the simulation:\n");
                    puts("1: The current/old model\n");
                    puts("2: The proposed model\n");
                    scanf("%d",&config.model_type);
                if ((config.model_type != 1) && (config.model_type != 2)) {
                    puts("please type 1 or 2\n");
                }
                }
                while ((config.read_generate != 'r') && (config.read_generate != 'g')){
                    puts("Please enter the choice of input method you want for the simulation:\n");
                    puts("r: Import processing times from your file\n");
                    puts("d: Generate processing times randomly \n");
                    scanf("%c",&config.read_generate);
                if ((config.read_generate != 'r') && (config.read_generate != 'g')) {
                    puts("please type r or g\n");
                }
                if (config.read_generate=='g'){
                    while (config.uplimit < config.lolimit) {
                    printf("please insert the lower limit of process time: ");
                    scanf("%f",&config.lolimit);
                    printf("please insert the upper limit of process time: ");
                    scanf("%f",&config.uplimit);
                    }
                printf("please enter the number of components of each type for simulation:");
                scanf("%d",&config.simlength);
                }else{
                    config.simlength=MAX_SIMULATION_LENGTH;
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
    return run_simulator(config);
}
