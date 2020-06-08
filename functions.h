#ifndef DATA_TYPES_H_INCLUDED
#define DATA_TYPES_H_INCLUDED

#define MAX_SIMULATION_LENGTH 500

struct CONFIG{              //Temporal function to provide the initial values
    int both_models;        //If the simulator will run once or twice - 1:once / 2:twice
    int model_type;         //Model type of the simulator - 1:old /2:new
    char read_generate;     //Read data or generate data
    int sim_length;          //Simulation length
    float lolimit;          //Lower limit
    float uplimit;          //Upper limit
};
typedef struct CONFIG Config;
struct INSPECTOR{           //Inspector instructor
    char *id;               //Id of inspector
    char *name;             //Name of the inspector
    float *idle_time;        //Idle time of the inspector
};
typedef struct INSPECTOR Inspector;
struct STATE{                   //State of simulator
    int model;                  //Simulation model ** not necessary ** since *state= old model , *(state+1)=new model //fixed
    float *simulation_time;             //Simulation length *simulation_time
    int *produced_prod;       //Produced products
    int *used_component;      //Used components - *not necessary* *suggest removal*
    int *unused_component;    //Unused components
    struct INSPECTOR *inspector1;//Inspector one
    struct INSPECTOR *inspector2;//Inspector two
};
typedef struct STATE State;
struct PTIME{               //Processing time function
    float *comp1;           //Processing time of the component 1
    float *comp2;           //Processing time of the component 2
    float *comp3;           //Processing time of the component 3
    float *ws1;             //Processing time of the working station 1
    float *ws2;             //Processing time of the working station 2
    float *ws3;             //Processing time of the working station 3
};
typedef struct PTIME Ptime;
#endif // FUNCTIONS_H_INCLUDED
