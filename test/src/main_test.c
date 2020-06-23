#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main_test.h"
#include "../include/data_types_test.h"
#include "../include/read_data_test.h"
#include "../include/work_flow_test.h"
#include "../include/export_files_test.h"
#include "../include/common_functions_test.h"

//Run Simulator
int main_test() {

    printf("------------- Testing work_flow -------------\n");
    work_flow_test();

    printf("------------- Testing export_files -------------\n");
    export_files_test();

    return 0;
}
