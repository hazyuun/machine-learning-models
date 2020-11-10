#ifndef _PERCEPTRON_H_
#define _PERCEPTRON_H_

#include <activations.h>
#include <dataset.h>

typedef struct {
	size_t dim;
	float *w;
	activation_t activation;
} perceptron_t;

/* Makes a perceptron given its input dimension and its activation function */
/* and initialize its weights to random values between -1 and 1	*/
perceptron_t *perceptron_create(size_t input_size, activation_t a);
void perceptron_destroy(perceptron_t *p);

/* Note : All learning algorithms implemened in perceptron.c , */
/*	only work with sign as activation 	*/
/* TODO : extend them to work on other activations */


/* Note : Please use THE sign function defined in activations.h */
/*	Do NOT try to implement your own, it won't work, */
/*	since the assertion uses the one in activations.h */

/* Trains a perceptron on a dataset using Perceptron Learning algorithm */
size_t perceptron_learn(perceptron_t *p, labeled_dataset_t *data);

/* Trains a perceptron on a dataset using Pocket algorithm */
size_t perceptron_pocket_learn(perceptron_t *p, labeled_dataset_t *data, size_t max_iterations);

/* Trains a perceptron on a dataset using Adaline (Delta rule) algorithm */
size_t perceptron_adaline_learn(perceptron_t *p, labeled_dataset_t *data, size_t max_iterations);

/* Predicts an input's class */
float perceptron_predict(perceptron_t *p, float *x);

/* Mean squared error */
inline float MSE(perceptron_t *p, labeled_dataset_t *data){
	float LS = 0;
	for(size_t i = 0; i < data->len; i++){
		float y = data->y[i];
		y -= perceptron_predict(p, data->x + i*p->dim);
		y = y * y;
		LS += y;
	}
	return LS / (float)(data->len);
}

#endif

