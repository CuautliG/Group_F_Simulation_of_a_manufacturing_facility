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

Installation
============

Installation steps are mentioned in [INSTALL.md](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/tree/master/INSTALL.md)

Usage
=====

To run, you must first install it. Then you can follow instructions mentioned in
[User\_Manual.md](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/tree/master/doc/User_Manual.md).

File Structure
==============

The correct file structure (after installing GSL library should be follow and run the binary)

* INSTALL.md  
* LICENSE  
* Makefile  
* README.md  
* bin  
* doc
* data
  * input
    * ser1.dat
    * ser2.dat
    * ser3.dat
    * ws1.dat
    * ws2.dat
    * ws3.dat

 * output
    * results.csv
* include
  * data\_types.h
  * export.h
  * main.h
  * read\_config.h
  * read\_data.h
  * work\_flow.h
* src
  * export.c
  * main.c
  * read\_config.c
  * read\_data.c
  * work\_flow.c
  * sensor.c
* Test

Documentation
=============

The User manual is available [here](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/wiki)
The developer manual is available [here](https://github.com/CuautliG/Group_F_Simulation_of_a_manufacturing_facility/wiki)

License
=======

This project is licensed under the GPL 2.0 License - see the LICENSE.md file for details

Acknowledgements
================

Thank to Dr. Cristina Ruiz Martin for providing guidance on how to develop the software.
