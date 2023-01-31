#include <stdio.h>
#include <stdlib.h>

#include "ds.h"
#include "metrics.h"

#define NUM_POINTS 5
#define NUM_COMMANDS 4

void init_metrics(ds_t *ds, metrics_t *metrics) {
    metrics->avg_runtimes = (float *)malloc(ds->rows * sizeof(float));
    metrics->speedups = (float *)malloc(ds->rows * sizeof(float));
    metrics->efficiencies = (float *)malloc(ds->rows * sizeof(float));
}

void calc_metrics(ds_t *ds, metrics_t *metrics) {
    int i, j;
    double sum;

    for (i = 0; i < ds->rows; i++) {
        sum = 0.0;
        for (j = 0; j < ds->cols[i]-1; j++) {
            sum += ds->runs[i][j];
        }

        metrics->avg_runtimes[i] = sum / (ds->cols[i]-1);
        metrics->speedups[i] = metrics->avg_runtimes[0] / metrics->avg_runtimes[i];
        metrics->efficiencies[i] = metrics->speedups[i] / ds->processors[i];
    }
}

void print_metrics(ds_t *ds, metrics_t *metrics) {
    int i;

    printf("#procs  runtime speedup efficiency\n");

    for (i = 0; i < ds->rows; i++) {
        printf("%d  %f  %f  %f\n", ds->processors[i], metrics->avg_runtimes[i], metrics->speedups[i], metrics->efficiencies[i]);

    }
}