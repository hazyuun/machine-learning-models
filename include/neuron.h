#ifndef _NEURON_H_
#define _NEURON_H_

#include <activations.h>
#include <dataset.h>
#include <metrics.h>

#include <stdarg.h>
typedef struct neuron neuron_t;
struct neuron {
  size_t dim;
  double *w;
  activation_t activation;
};

/* Makes a neuron given its input dimension and its activation function */
/* and initialize its weights to random values between -1 and 1	*/
neuron_t *neuron_create(size_t input_size, activation_t a);

neuron_t *neuron_clone(const neuron_t *p);

void neuron_destroy(neuron_t *p);

/* Note : All classification learning algorithms implemened in neuron.c , */
/*	only work with sign as activation 	*/
/* TODO : extend them to work on other activations */

/* Note : Please use THE sign function defined in activations.h */
/*	Do NOT try to implement your own, it won't work, */
/*	since the assertion uses the one in activations.h */

typedef enum {
  /* CLASSIFICATION */
  PLA_ALGO,
  POCKET_ALGO,
  ADALINE_ALGO,

  /* REGRESSION */
  LEAST_SQUARES_GD_ALGO

} algorithm_t;

/**** Classification ****/

/* Trains a neuron on a dataset using Perceptron Learning algorithm */
history_t *neuron_PLA_learn(neuron_t *p, labeled_dataset_t *data,
                                metric_t metric);

/* Trains a neuron on a dataset using Pocket algorithm */
history_t *neuron_pocket_learn(neuron_t *p, labeled_dataset_t *data,
                                   metric_t metric, size_t max_iterations);

/* Trains a neuron on a dataset using Adaline (Delta rule) algorithm */
history_t *neuron_adaline_learn(neuron_t *p, labeled_dataset_t *data,
                                    metric_t metric, size_t max_iterations);

/* A wrapper for all training algorithsms */
/* Note : max_iterations is ignored when using PLA */
history_t *neuron_train(neuron_t *p, labeled_dataset_t *data,
                            algorithm_t algorithm, metric_t metric,
                            size_t max_iterations);


/**** Regression ****/

/* Trains a neuron for linear regression with least squares method */
history_t *neuron_lsquares_learn(neuron_t *p, dataset_t *data,
                                     metric_t metric, double learning_rate,
                                     size_t max_iterations);

/* Predicts an input's class */
double neuron_predict(neuron_t *p, double *x);

#endif
