#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <omp.h>

#include "ds.h"
#include "metrics.h"

#define N_COMMANDS_1 7
#define N_COMMANDS_2 11

/*
 * allocates spaces for metrics struct
 */
void init_metrics(ds_t *ds, metrics_t *metrics) {
    metrics->avg_runtimes = (float *)malloc(ds->rows * sizeof(float));
    metrics->speedups = (float *)malloc(ds->rows * sizeof(float));
    metrics->efficiencies = (float *)malloc(ds->rows * sizeof(float));
}

/*
 * Calculates avg speeds, speedups and efficiencies for
 * a given dataset
 */
void calc_metrics(ds_t *ds, metrics_t *metrics) {
    int i, j;
    double sum = 0;

    #pragma omp parallel for default(none) private(i, j, sum) shared(ds, metrics)
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

/*
 * prints the calculated performance metrics to the stdout
 */
void print_metrics(ds_t *ds, metrics_t *metrics) {
    int i;

    printf("#procs  runtime speedup efficiency\n");

    for (i = 0; i < ds->rows; i++) {
        printf("%d  %f  %f  %f\n", ds->processors[i], metrics->avg_runtimes[i], metrics->speedups[i], metrics->efficiencies[i]);
    }
}

/*
 * exports the calculated metrics to a file
 */
int export_metrics(ds_t *ds, metrics_t *metrics) {
    struct stat st = {0};
    FILE *fp;
    int i;

    if (stat("./output", &st) == -1)
        mkdir("./output", 0700);

    fp = fopen("./output/metrics.dat", "w");
    if (fp == NULL) {
        perror("Error opening the file");
        return 1;
    }

    fprintf(fp, "#procs\truntime\t\t\tspeedup\t\t\tefficiency\n");
    fprintf(fp, "#=====\t=======\t\t\t=======\t\t\t==========\n");
    for (i = 0; i < ds->rows; i++) {
        fprintf(fp, "%6d\t%9f\t\t%9f\t\t%8f\n", ds->processors[i], metrics->avg_runtimes[i], metrics->speedups[i], metrics->efficiencies[i]);
    }

    return 0;
}

/**
 * Create a child process to run gnuplot, and plots the results of the metrics.
 */
void plot_metrics() {
    // Commands for execution time chart
    char *commands1[] = {
        "set term png",
        "set output \"./output/exec-time.png\"",
        "set title \"Exec. time\"",
        "set xlabel \"Processors\"",
        "set ylabel \"Runtime (ms)\"",
        "set style data lines",
        "plot \"./output/metrics.dat\" using 2:xticlabels(1) t \"\" with linespoints lw 2 dt 2 lc rgb \"blue\" pt 5",
    };
    // Commands for speedup and efficiency chart
    char * commands2[] = {
        "set term png",
        "set output \"./output/speedup-efficiency.png\"",
        "set title \"Speed Up and Efficiency\"",
        "set xlabel \"Processors\"",
        "set logscale x",
        "set ylabel \"Speed Up\"",
        "set y2label \"Efficiency\"",
        "set y2range [0:100]",
        "set format y2 \"%g%%\"",
        "set key bottom right box",
        "plot \"./output/metrics.dat\" using 1:3 with linespoints t \"Speed Up\" lw 2 dt 2 lc rgb \"red\" pt 5 axis x1y1, \"./output/metrics.dat\" using 1:($4*100):xtic(1) t \"Efficiency\" with linespoints lw 2 dt 2 lc rgb \"blue\" pt 2 axis x1y2"
    };
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;

    // Sends commands for first plot
    for (i = 0; i < N_COMMANDS_1; i++) {
        fprintf(gnuplotPipe, "%s \n", commands1[i]);
    }

    // Send commands for second plot
    for (i = 0; i < N_COMMANDS_2; i++) {
        fprintf(gnuplotPipe, "%s \n", commands2[i]);
    }
}