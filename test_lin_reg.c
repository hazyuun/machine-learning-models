#include <stdio.h>
#include <perceptron.h>

int main(int argc, char **argv){
    (void) argc;
	(void) argv;
    
    /* Use a .csv file and clean this mess */
#if 1
    float x[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.1f, 1.0f,
        1.2f, 1.1f,
        
        1.3f, 1.2f,
        1.3f, 1.3f,
        1.5f, 1.56f,
        2.0f, 2.1f,
        
        2.1f, 2.1f,
        2.1f, 2.15f,
        2.2f, 2.2f,
        2.3f, 2.35f
    };
#else
    float x[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.1f, 1.1f,
        1.2f, 1.2f,
        
        1.3f, 1.3f,
        1.4f, 1.4f,
        1.5f, 1.5f,
        2.0f, 2.0f,
        
        2.1f, 2.1f,
        2.2f, 2.2f,
        2.3f, 2.3f,
        2.35f, 2.35f
    };
#endif
    
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
