typedef struct ds_t {
    int rows, *cols; // included processors col
    int *processors;
    float **runs;
} ds_t;

int read_dataset(char* filename, ds_t *ds);