typedef struct metrics_t {
    float *avg_runtimes;
    float *speedups;
    float *efficiencies;
} metrics_t;

void init_metrics(ds_t *ds, metrics_t *metrics);
void calc_metrics(ds_t *ds, metrics_t *metrics);
void print_metrics(ds_t *ds, metrics_t *metrics);
int export_metrics(ds_t *ds, metrics_t *metrics);
void plot_metrics();