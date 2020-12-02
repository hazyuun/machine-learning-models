#include <stdio.h>
#include <stdlib.h>
#include <perceptron.h>
#include <csv.h>

int main(int argc, char **argv){
    (void) argc;
	(void) argv;
    
    csv_t csv = csv_load("./test-data/regression.csv");
    
    /* -1 because the first row is only for the headers */
    size_t rows = csv_count_rows(csv);
    size_t cols = csv_count_cols(csv);
    const size_t n = (rows - 1) * cols;
    
    float x[n];
    
	for(size_t i = 1; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
           x[cols * (i-1) + j] = atof(csv_get_value(csv, i, j));
        }
    }
	
	csv_destroy(csv);
    
    dataset_t *data = dataset_create(2, 12);
	data->x = x;
    
    perceptron_t *p = perceptron_create(1, &identity);
    
    /*
     * learning rate    : 0.01
     * iterations       : 500
     */
    history_t *history = perceptron_lsquares_learn(p, data, MSE_METRIC, 0.01, 500);
    
    /* Some tests */
#if 0
    float input = -10.0f;
    for(; input < 10.0f; input++)
        printf("\n %.1f : %.3f", input, perceptron_predict(p, &input));
#endif

    /* Generate the output files for plotting */
	FILE *out;
    
    /* Points */
	out = fopen("data.in", "w");
	for(size_t i = 0; i < rows; i++){
		fprintf(out, "%.5lf %.5lf %.5lf\n", x[2*i], x[2*i+1], 1.0f);
	}
	fclose(out);

    /* Weights */
	out = fopen("weights.in", "w");
	for(size_t i = 0; i < 2; i++){
		fprintf(out, "w%ld = %.5lf\n", i, p->w[i]);
	}
	fclose(out);

    /* History */
	float *history_array = history_as_array(history);
	size_t len = history_length(history);
	out = fopen("history.in", "w");
	for(size_t i = 0; i < len; i++){
		fprintf(out, "%.2lf %.2lf\n", (float)i, history_array[i]);
	}
	fclose(out);
    
    return 0;
}
