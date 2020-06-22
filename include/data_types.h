#ifndef DATA_TYPES_H_INCLUDED
#define DATA_TYPES_H_INCLUDED

#define MAX_SIMULATION_LENGTH 5000
#define SIM_STATES 3
#define MAX_LINE_LENGTH 4096
#define PRODUCTS 3
#define MAX_BUFFER 2
#define MAX_SIZE_FILENAME 30
#define MAX_ARRAY_SIZE 20
#define MAX_CHAR_SIZE 8
#define NUMB_INPUT_FILES 6
#define MAX_INPUT_SIZE 23
#define INPUT_DIRECTORY_SIZE 13

/** \brief Configuration structure. \n
 * It contains all the initial values that the simulator needs to run.
 *
 */
struct CONFIG{
    int both_models;        /**< Variable to save if the simulator runs both model, 1 to run both models and 0 to just run one */
    int model_type;         /**< Model type of the simulator, 1 for old model and 2 for new model*/
    char read_generate;     /**< Read data or generate data variable, 'r' for read data and 'g' for generate data */
    int sim_length;         /**< Simulation length variable */
    float lower_limit;      /**< Lower limit when generate data is chosen */
    float upper_limit;      /**< Upper limit when generate data is chosen */
};

/** \brief Inspector structure. \n
 * It contains the variables to define each inspector.
 *
 */
struct INSPECTOR{
    char *id;                       /**< Id of the inspector */
    char *name;                     /**< Name of the inspector */
    float idle_time;                /**< Idle time of the inspector */
};

/** \brief State structure. \n
 * It contains the produced results after the a model was simulated.
 *
 */
struct STATE{
    int model_type;                 /**< Model type of the state */
    int sim_length;                 /**< Simulation length variable */
    float clock;                    /**< Simulation clock */
    int produced_prod[PRODUCTS];    /**< Produced product after simulation */
    int used_component[PRODUCTS];   /**< Used products after simulation */
    int unused_component[PRODUCTS]; /**< Unused products after simulation */
    struct INSPECTOR inspector1;    /**< structure for inspector one */
    struct INSPECTOR inspector2;    /**< structure for inspector two */
};

/** \brief Processing time structure. \n
 * It contains the processing time of the three components and the three working stations.
 *
 */
struct PTIME{
    float *comp1;                   /**< Processing time of component 1 */
    float *comp2;                   /**< Processing time of component 2 */
    float *comp3;                   /**< Processing time of component 3 */
    float *ws1;                     /**< Processing time of the working station 1 */
    float *ws2;                     /**< Processing time of the working station 2 */
    float *ws3;                     /**< Processing time of the working station 3 */
};

#endif // DATA_TYPES_H_INCLUDED
