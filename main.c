#include "stdio.h"
#include "files.h"
#include "performance-metrics.h"

int main() {
    // read file and store data in struct
    read_file();

    // calculate performance metrics
    calculate_performance_metrics();

    // print metrics on screen
    print_metrics();
}