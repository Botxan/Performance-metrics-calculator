#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds.h"

#define SIZE 4096

int read_dataset(char* filename, ds_t *ds) {
    FILE *fp;
    int i, j;
    char line[SIZE], *token;
    char delims[] = " \f\r\n\t\v";

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Skip headers
    fgets(line, SIZE, fp);

    // first pass: count number of rows and columns per row
    ds->rows = 0;
    ds->cols = (int *)malloc(ds->rows * sizeof(int));
    while (fgets(line, SIZE, fp) != NULL) {
        ds->cols[ds->rows] = 0;
        token = strtok(line, delims);
        while(token) {
            ds->cols[ds->rows]++;
            token = strtok(NULL, delims);
        }
        ds->rows++;
        ds->cols = (int*) realloc(ds->cols, (ds->rows+1) * sizeof(int));
    }

    // Allocate memory for processors and run samples
    ds->processors = (int *)malloc(ds->rows * sizeof(int));
    ds->runs = (float **)malloc(ds->rows * sizeof(float *));
    for (i = 0; i < ds->rows; i++) {
        ds->runs[i] = (float *)malloc((ds->cols[i]-1) * sizeof(float));
    }

    rewind(fp);
    fgets(line, SIZE, fp);

    // second pass: store data into struct
    for (i = 0; i < ds->rows; i++)  {
        fscanf(fp, "%d", &(ds->processors[i]));
        for (j = 0; j < ds->cols[i]-1; j++) {
            fscanf(fp, " %f", &(ds->runs[i][j]));
        }
    }

    return 0;
}