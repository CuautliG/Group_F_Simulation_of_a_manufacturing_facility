#declare the variable
CC = gcc

CFLAGS=
ifeq ($(DEBUG),1)
	CFLAGS=-DDEBUG_ENABLED
endif

#Creates bin, build, and output folders required to compile and execute the program.
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)

#Default command
all: app

app: main.o read_config.o read_data.o work_flow.o export_files.o common_functions.o
	$(CC) -g -o bin/Group_F_Simulation_of_a_manufacturing_facility build/main.o build/read_config.o build/read_data.o build/work_flow.o build/export_files.o build/common_functions.o

#Command of the program	

main.o: src/main.c
	$(CC) -g -c $(CFLAGS) src/main.c -o build/main.o

read_config.o: src/read_config.c
	$(CC) -g -c $(CFLAGS) src/read_config.c -o build/read_config.o

read_data.o: src/read_data.c
	$(CC) -g -c $(CFLAGS) src/read_data.c -o build/read_data.o

work_flow.o: src/work_flow.c
	$(CC) -g -c $(CFLAGS) src/work_flow.c -o build/work_flow.o

export_files.o: src/export_files.c
	$(CC) -g -c $(CFLAGS) src/export_files.c -o build/export_files.o

common_functions.o : src/common_functions.c
	$(CC) -g -c $(CFLAGS) src/common_functions.c -o build/common_functions.o


#This command run the program
run:
	bin/Group_F_Simulation_of_a_manufacturing_facility 

doxygen:
	rm -f -r ./doc/detailed
	doxygen ./doc/doxyfile.cfg
clean:
	rm -f bin/* build/*
