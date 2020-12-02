#include <stdio.h>
#include <stdlib.h>
#include <perceptron.h>
#include <csv.h>

int main(int argc, char **argv){
    (void) argc;
	(void) argv;
    
    csv_t csv = csv_load("./test-data/regression.csv");
    
    /* -1 because the first row is only for the headers */
    size_t rows = csv_count_rows(csv) - 1;
    size_t cols = csv_count_cols(csv);
    const size_t n = rows * cols;
    
    float x[n];
    
	for(size_t i = 1; i < rows; i++){
        for(size_t j = 0; j < cols; j++){
           x[cols * i + j] = atof(csv_get_value(csv, i, j));
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
    float input = -10.0f;
    for(; input < 10.0f; input++)
        printf("\n %.1f : %.3f", input, perceptron_predict(p, &input));
    
    /* export history and all stuff needed to plot */
    (void) history;
    
    return 0;
}
