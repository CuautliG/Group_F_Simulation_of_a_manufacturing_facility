Group F - Simulation of a Manufacturing Facility
================================================

The simulator of a manufacturing facility was developed to model the assembling process of three different products. The simulator can simulate the actual working flow model or it can run a new proposed model.
The user is able to choose which model he/she wants to simulate and the initial values of the process. If the user does not provide initial values the program uses the default values saved in a configuration file. By default the simulator needs inputs files that contains the processing times of each stage of the working process. However, the program can also generate random files in case the user specified it in the configuration file.
At the end of each simulation the program will display the main results and it will also create report file(s) with those results. For more information about the initial values, input files or the report files of the simulator, please refer to user documentation.

Group Information
=======
## Authors

1. **Charles Emesobum** 
   * GitHub:  **_charlesemesobum_**
2. **Cuautli Garcia**
   * GitHub:  **_cuautilG_**  
3. **Hai Ngoc Nguyen**
   * GitHub:  **_ngochai1604_**
4. **Imbie David Nku**
   * GitHub:  **_panakou_**

Usage
=====

To run this program, you will need to download all its files and then follow the instructions mentioned in
[User\_Manual.md](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/wiki/User-Documentation#user-documentation)

File Structure
================================================
 
* LICENSE  
* Makefile  
* README.md   
* data
  * input
    * ser1.dat
    * ser2.dat
    * ser3.dat
    * ws1.dat
    * ws2.dat
    * ws3.dat
  * output
  * config.cfg
* doc
  * doxygen_config.cfg
* include
  * common_functions.h
  * data_types.h
  * export_files.h
  * main.h
  * read_config.h
  * read_data.h
  * work_flow.h
* src
  * common_functions.c
  * export_files.c
  * main.c
  * read_config.c
  * read_data.c
  * work_flow.c
* Test
  * data
    * input
      * ser1.dat
      * ser2.dat
      * ser3.dat
      * ws1.dat
      * ws2.dat
      * ws3.dat
    * output
    * config.cfg
  * include
    * common_functions_test.h
    * data_types_test.h
    * export_files_test.h
    * main_test.h
    * read_config_test.h
    * read_data_test.h
    * work_flow_test.h
  * src
    * common_functions_test.c
    * data_types_test.c
    * export_files_test.c
    * main_test.c
    * read_config_test.c
    * read_data_test.c
    * work_flow_test.c

Documentation
=============

The User manual is available [here](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/wiki/User-Documentation#user-documentation)
The developer manual is available [here](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/wiki/Developer-Documentation#developer-documentation)

License
=======

This project is licensed under the GPL 3.0 License - see the LICENSE.md file for details

Acknowledgements
================

We would like to thank our professor Cristina Ruiz Martin for all the guidance through the entire project
