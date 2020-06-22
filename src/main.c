#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/data_types.h"
#include "./include/main.h"
#include "./include/read_data.h"
#include "./include/work_flow.h"
#include "./include/export_files.h"
#include "./include/common_functions.h"

/** \brief Function to run the simulator. \n
 * This function calls all the necessary function in order to simulate the manufacturing facility.
 * \param[in] my_config is the configuration that the simulator uses to run
 * \param[in] input_directory is the directory where the input files are saved
 * \param[in] output_directory is the directory where the simulator saves the generated files
 * \return 0 if the simulator was correctly executed, -1 if an error happened in read_data,
 *     -2 if an error happened in work_flow, -3 if an error happened in export_files.
 */
int run_simulator(struct CONFIG *my_config, char* input_directory, char* output_directory) {
    int return_var = 0;         /* Initialize return variable of the function */
    int data_var = 0;           /* Initialize a variable save the value from read_data function  */
    int flow_var = 0;           /* Initialize a variable save the value from work_flow function  */
    int export_var = 0;         /* Initialize a variable save the value from export_files function  */
    /* Initialize array of structures for my_state and my_ptime */
    struct STATE *my_state=malloc(SIM_STATES*sizeof(struct STATE));
    struct PTIME *my_ptime=malloc(sizeof(struct STATE));
    /* Initialize an inspector 1 and 2*/
    struct INSPECTOR my_inspector1={.id="1234",.name="PersonOne",.idle_time=0.00};
    struct INSPECTOR my_inspector2={.id="4321",.name="PersonTwo",.idle_time=0.00};
    /* Addition of inspector 1 and 2 into the structure my_state*/
    for (int i=1; i<SIM_STATES; ++i){
        (my_state+i)->inspector1=my_inspector1;
        (my_state+i)->inspector2=my_inspector2;
    }

    data_var = read_data(input_directory, my_config, my_ptime); /* Call read_data and save its return value */
    if(data_var<0){                                             /* If the function retrieves a number smaller than 0*/
        printf("Error %d in read_data function",data_var);      /* Print the error of the function */
        return_var = -1;                                        /* Assign -1 to the main error */
    }
    #ifdef DEBUG_ENABLED
        print_ptime(my_config,my_ptime);
    #endif

    flow_var = work_flow(my_config,my_ptime,my_state);          /* Call work_flow and save its return value */
    if(flow_var<0){                                             /* If the function retrieves a number smaller than 0*/
        printf("Error %d in flow_var function",flow_var);       /* Print the error of the function */
        return_var = -2;                                        /* Assign -2 to the main error */
    }

    #ifdef DEBUG_ENABLED
        print_state(my_state);
    #endif

    export_var= export_files(my_config, my_state, output_directory);/* Call export_files and save its return value */
    if(export_var<0){                                               /* If the function retrieves a number smaller than 0*/
        printf("Error %d in export_var function\n",export_var);     /* Print the error of the function */
        return_var = -3;                                            /* Assign -3 to the main error */
    }
    /* Free the memory use for the simulator */
    free(my_state);
    free(my_ptime);


    if(return_var!=0){                                              /* If an error happened during the execution*/
        printf("Error in one or more functions, please see below the errors");
    }else{                                                          /* If everything run well */
        printf("The simulator modeled the manufacturing facility correctly");
        return return_var;
    }

}

/** \brief Main function of the simulator. \n
 * This function read the program arguments if any is given. It also starts the run_simulator function.
 * The following are valid command line arguments:
 * -v for users to know the version of the program
 * -m for users to enter manually the values of the simulator
 * -c for users to specify the configuration file name
 * -i for users to specify the input directory
 * -o for users to specify the output directory
 * @return 0 if the application executed successfully.  Any other number if their was an error during the execution.
 */
int main(int argc, char* argv[]) {

    char* config_name=      "./data/config.cfg";    /* Default configuration file */
    char* input_directory=  "./data/input/";        /* Default input directory */
    char* output_directory= "./data/output/";       /* Default output directory */
    /* Initialize a configuration structure with the default values*/
    struct CONFIG my_config={.both_models=0,.model_type=2,.read_generate='r',
        .sim_length=MAX_SIMULATION_LENGTH,.lower_limit=10.0,.upper_limit=15.0};
    struct CONFIG *config = &my_config;
    int actual_arg=1;               /*Initialize the actual argument at 1*/
    while(actual_arg<argc) {        /*While there is an argument*/
        if(*argv[actual_arg]=='-') {/*If the argument starts with -*/
            if(strcmp(argv[actual_arg],"-v")==0) {  /*If the argument is -v*/
                /* Print the actual version and its options */
                printf("Manufacturing Facility Simulator V 1.1\n");
                printf("Options:\n");
                printf("-v : Display the version of the program and its options\n");
                printf("-m : Allows to enter the initial values of the simulator manually\n");
                printf("-c (filename)  : Allows to set the name of the configuration file. Default is %s\n",config_name);
                printf("-i (directory) : Allows to set the input directory.                Default is %s\n",input_directory);
                printf("-o (directory) : Allows to set the output directory.               Default is %s\n",output_directory);
                break;

            } else if(strcmp(argv[actual_arg],"-m")==0){ /* If the argument is -m */
                /* Restart the values from the config structure */
                config->model_type=0;
                config->read_generate='\0';
                config->upper_limit=0;
                config->lower_limit=0;
                config->sim_length=0;
                 /* The user does not provide for a model type equal 1 or 2 */
                while ((config->model_type != 1) && (config->model_type != 2)){
                    /* Print the instructions to the user */
                    puts("Please enter the choice of model you want for the simulation:\n");
                    puts("1: The current/old model\n");
                    puts("2: The proposed model\n");
                    scanf("%d",&config->model_type);/* Save the input into the configuration */
                if ((config->model_type != 1) && (config->model_type != 2)) { /* If the input is not valid */
                    puts("please type 1 or 2\n");   /* Show error message */
                }
                }
                /* The user does not provide for a read or generate equal to r or g */
                while ((config->read_generate != 'r') && (config->read_generate != 'g')){
                    /* Print the instructions to the user */
                    puts("Please enter the choice of input method you want for the simulation:\n");
                    puts("r: Import processing times from your file\n");
                    puts("g: Generate processing times randomly \n");
                    scanf(" %c",&config->read_generate);/* Save the input into the configuration */
                    if ((config->read_generate != 'r') && (config->read_generate != 'g')) { /* If the input is not valid */
                        puts("please type r or g\n");   /* Show error message */
                    }
                    if (config->read_generate=='g'){    /* If the option is g for generate*/
                        /* While the user does not provide for an upper limit bigger than the lower limit */
                        while (config->upper_limit <= config->lower_limit) {
                            /* Print the instructions to the user */
                            printf("please insert the lower limit of process time: ");
                            scanf("%f",&config->lower_limit); /* Save the input into the configuration */
                            printf("please insert the upper limit of process time: ");
                            scanf("%f",&config->upper_limit); /* Save the input into the configuration */
                            if(config->upper_limit <= config->lower_limit){ /* If upper limit is not bigger than lower limit */
                                puts("The upper limit must be bigger than the lower limit");    /* Show error message */
                            }
                        }
                        /* While the user does not provide for an simulation length bigger than 0 */
                        while (config->sim_length < 1){
                            /* Print the instructions to the user */
                            printf("please enter the number of components of each type for simulation:");
                            scanf(" %d",&config->sim_length);/* Save the input into the configuration */
                            if(config->sim_length < 1){     /* If the simulation length is not bigger than 0*/
                                puts("please chose a simulation length bigger than 0"); /* Show error message */
                            }
                        }
                    }else{ /* If the user decides to read the files */
                        config->sim_length=MAX_SIMULATION_LENGTH; /* The simulation length equal to the constant */
                    }
                }
                actual_arg++;   /* Increase the read argument */
                break;
            }else if(strcmp(argv[actual_arg],"-c")==0) { /* If the argument is -c */
                actual_arg++;               /* Increase the read argument */
                if(*argv[actual_arg]!='-') {/* Seek for identifier - */
                    config_name=argv[actual_arg]; /* Save configuration file */
                    /* User message about the input */
                    printf("The configuration file was set to: %s\n",config_name);
                    break;
                }
            }else if(strcmp(argv[actual_arg],"-i")==0) {
                actual_arg++;               /* Increase the read argument */
                if(*argv[actual_arg]!='-') {/* Seek for identifier - */
                    input_directory=argv[actual_arg];/* Save the input path */
                    /* User message about the input */
                    printf("The input directory was set to: %s\n",input_directory);
                    break;
                }
            }else if(strcmp(argv[actual_arg],"-o")==0) {
                actual_arg++;               /* Increase the read argument */
                if(*argv[actual_arg]!='-') {/* Seek for identifier - */
                    output_directory=argv[actual_arg];/* Save the output path */
                    /* User message about the input */
                    printf("The output directory was set to: %s\n",output_directory);
                    break;
                }
            }else { /* Any other inputs is an invalid argument */
                printf("Invalid option: %s\n",argv[actual_arg]); /* Error message */
                break;
            }
        }else { /* If the argument does not start with - */
            printf("The argument '%s' is not valid it must start with '-'\n",argv[actual_arg]); /* Error message */
            break;
        }
    }
    printf("\n\n\n\n\n\n");                                         /* Print clear line for easy understanding on the results */
    return run_simulator(config, input_directory, output_directory);/* Call the function to run the simulator */
}

/*! \mainpage Simulator of a Manufacturing Facility
 *
 * The simulator of a manufacturing facility was developed to model the assembling process of three
 * different products. The simulator can simulate the actual working flow model or it can run a new
 * proposed model. The user is able to choose which model he/she wants to simulate and the initial
 * values of the process. If the user does not provide initial values the program uses the default
 * values saved in a configuration file. By default the simulator needs inputs files that contains
 * the processing times of each stage of the working process. However, the program can also generate
 * random files in case the user specified it in the configuration file. At the end of each simulation
 * the program will display the main results and it will also create report file(s) with those results.
 * For more information about the initial values, input files or the report files of the simulator,
 * please refer to user documentation.. \n
 * \n
 * The code is divided into the following functions: \n
 *
 * - \ref main function
 * - \ref read_data function
 * - \ref work_flow function
 * - \ref export_files function
 */

