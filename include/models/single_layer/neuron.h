#ifndef _NEURON_H_
#define _NEURON_H_

#include <activations.h>
#include <dataset.h>
#include <metrics.h>

typedef struct neuron neuron_t;

struct neuron {
  size_t dim;
  double *w;
  activation_t activation;
};

typedef enum {
  /* CLASSIFICATION */
  PLA_ALGO,
  POCKET_ALGO,
  ADALINE_ALGO,
  BIN_CROSS_ENTROPY_GD_ALGO,

  /* REGRESSION */
  LEAST_SQUARES_GD_ALGO

} algorithm_t;

/* Makes a neuron given its input dimension and its activation function */
/* and initialize its weights to random values between -1 and 1	*/
neuron_t *neuron_create(size_t input_size, activation_t a);

neuron_t *neuron_clone(const neuron_t *p);

void neuron_destroy(neuron_t *p);

/* Predicts an input's class */
double neuron_predict(neuron_t *p, double *x);

#endif
