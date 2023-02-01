#include <stdio.h>
#include <stdlib.h>

#include "ds.h"
#include "metrics.h"

/*
 * Calculates the mean speeds, speedups and efficiencies from the text file
 * passed by argv
 */
int main(int argc, char *argv[]) {
    ds_t ds;
    metrics_t metrics;

    if (argc != 2) {
        printf("Usage: %s <input-file>\n", argv[0]);
        exit(1);
    }

    // read file and store data in struct
    read_dataset(argv[1], &ds);

    // calculate performance metrics
    init_metrics(&ds, &metrics);
    calc_metrics(&ds, &metrics);

    // store results in a file
    export_metrics(&ds, &metrics);
    printf("Results saved in ./output/metrics.dat\n");

    // draw plots
    plot_metrics();
    printf("Plots saved in ./output/exec-time.png and ./output/speedup-efficiency.png\n");

    // Not really needed, but for some environments
    free(ds.cols);
    free(ds.processors);
    for (int i = 0; i < ds.rows; i++)
        free(ds.runs[i]);
    free(ds.runs);
}