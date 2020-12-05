#ifndef _PERCEPTRON_H_
#define _PERCEPTRON_H_

#include <activations.h>
#include <dataset.h>
#include <metrics.h>

#include <stdarg.h>
typedef struct perceptron perceptron_t;
struct perceptron {
  size_t dim;
  double *w;
  activation_t activation;
};

/* Makes a perceptron given its input dimension and its activation function */
/* and initialize its weights to random values between -1 and 1	*/
perceptron_t *perceptron_create(size_t input_size, activation_t a);

perceptron_t *perceptron_clone(const perceptron_t *p);

void perceptron_destroy(perceptron_t *p);

/* Note : All classification learning algorithms implemened in perceptron.c , */
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

/* Trains a perceptron on a dataset using Perceptron Learning algorithm */
history_t *perceptron_PLA_learn(perceptron_t *p, labeled_dataset_t *data,
                                metric_t metric);

/* Trains a perceptron on a dataset using Pocket algorithm */
history_t *perceptron_pocket_learn(perceptron_t *p, labeled_dataset_t *data,
                                   metric_t metric, size_t max_iterations);

/* Trains a perceptron on a dataset using Adaline (Delta rule) algorithm */
history_t *perceptron_adaline_learn(perceptron_t *p, labeled_dataset_t *data,
                                    metric_t metric, size_t max_iterations);

/* A wrapper for all training algorithsms */
/* Note : max_iterations is ignored when using PLA */
history_t *perceptron_train(perceptron_t *p, labeled_dataset_t *data,
                            algorithm_t algorithm, metric_t metric,
                            size_t max_iterations);


/**** Regression ****/

/* Trains a perceptron for linear regression with least squares method */
history_t *perceptron_lsquares_learn(perceptron_t *p, dataset_t *data,
                                     metric_t metric, double learning_rate,
                                     size_t max_iterations);

/* Predicts an input's class */
double perceptron_predict(perceptron_t *p, double *x);

#endif
