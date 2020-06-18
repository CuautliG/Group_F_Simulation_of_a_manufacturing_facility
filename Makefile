#declare the variable
CC = gcc

CFLAGS = -c -Wall

#Default command
all: app

#Application command
app : main.o rean_config.o read_data.o work_flow.o export_files.o

#Command of the program	
main.o: src\main.c
	$(CC) $(CFLAGS) -c main.c

read_config.o: src\read_config.c
  $(CC) $(CFLAGS) read_config.c

read_data.o: src\read_data.c
	$(CC) $(CFLAGS) read_data.c

work_flow.o: src\work_flow.c
	$(CC) $(CFLAGS) work_flow.c

export_files.o: src\export_files.c
	$(CC) $(CFLAGS) export_files.c

clean:
	rm -f -r *o
