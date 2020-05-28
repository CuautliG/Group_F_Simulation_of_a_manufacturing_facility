#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/main.h"

//Run Simulator
int run_simulator(struct CONFIG my_config) {
    printf("Model type: %d",my_config.option1);
    return 0;
}

//Main Function
int main(int argc, char* argv[]) {
    char* config_name=      "./data/config.cfg";    // The output directory
    char* input_directory=  "./data/input/";        // The output directory
    char* output_directory= "./data/output/";       // The output directory
    struct CONFIG config={.option1=2,.option2=1,.simlength=5000,.lolimit=10,.uplimit=15};
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
            config.option1=0;
            while ((config.option1 != 1) && (config.option1 != 2)){
                puts("Please enter the choice of model you want for the simulation:\n");
                puts("1: The current/old model\n");
                puts("2: The proposed model\n");
                scanf("%d",&config.option1);
                if ((config.option1 != 1) && (config.option1 != 2)) {
                    puts("please type 1 or 2\n");
                }
                printf("You chose %d\n",config.option1);
                }
            while ((config.option2 != 1) && (config.option2 != 2)){
                puts("Please enter the choice of input method you want for the simulation:\n");
                puts("1: Import processing times from your file\n");
                puts("2: Generate processing times randomly \n");
                scanf("%d",&config.option2);
                if ((config.option2 != 1) && (config.option2 != 2)) {
                    puts("please type 1 or 2\n");
                }
                if (config.option2==2){
                while (config.uplimit < config.lolimit) {
                    printf("please insert the lower limit of process time: ");
                    scanf("%f",&config.lolimit);
                    printf("please insert the upper limit of process time: ");
                    scanf("%f",&config.uplimit);
                }
                printf("please enter the number of components of each type for simulation:");
                scanf("%d",&config.simlength);
                }else{
                    config.simlength=5000;
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
