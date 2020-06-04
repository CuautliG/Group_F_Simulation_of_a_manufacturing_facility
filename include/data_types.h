#ifndef DATA_TYPES_H_INCLUDED
#define DATA_TYPES_H_INCLUDED

#define MAX_SIMULATION_LENGTH 500

struct CONFIG{              //Temporal function to provide the initial values
    int both_models;        //If the simulator will run once or twice
    int model_type;         //Model type of the simulator
    char read_generate;     //Read data or generate data
    int sim_length;          //Simulation length
    float lolimit;          //Lower limit
    float uplimit;          //Upper limit
};

struct INSPECTOR{           //Inspector instructor
    char *id;               //Id of inspector
    char *name;             //Name of the inspector
    float idle_time;        //Idle time of the inspector
};

struct STATE{                   //State of simulator
    int model;                  //Simulation model
    int sim_length;             //Simulation length
    float clock;                //Simulation clock
    int produced_prod[3];       //Produced products
    int used_component[3];      //Used components
    int unused_component[3];    //Unused components
    struct INSPECTOR inspector1;//Inspector one
    struct INSPECTOR inspector2;//Inspector two
};

struct PTIME{               //Processing time function
    float *comp1;           //Processing time of the component 1
    float *comp2;           //Processing time of the component 2
    float *comp3;           //Processing time of the component 3
    float *ws1;             //Processing time of the working station 1
    float *ws2;             //Processing time of the working station 2
    float *ws3;             //Processing time of the working station 3
};

#endif // DATA_TYPES_H_INCLUDED
