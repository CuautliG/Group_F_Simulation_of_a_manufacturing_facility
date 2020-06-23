#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../include/main_test.h"
#include "../include/read_config_test.h"
#include "../include/read_data_test.h"
#include "../include/work_flow_test.h"
#include "../include/export_files_test.h"

int main() {

    printf("------------- Testing read_config -------------\n");
    read_config_test();

    printf("------------- Testing read_data -------------\n");
    read_data_test();

    printf("------------- Testing work_flow -------------\n");
    work_flow_test();

    printf("------------- Testing export_files -------------\n");
    export_files_test();

    return 0;
}
