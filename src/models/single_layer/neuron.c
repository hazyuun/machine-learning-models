#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <activations.h>
#include <mathutils.h>
#include <metrics.h>
#include <models/single_layer/neuron.h>

/* Makes a neuron given its input dimension and its activation function */
/* and initialize its weights to random values between -1 and 1 */
neuron_t *neuron_create(size_t dim, activation_t a) {
  neuron_t *p = (neuron_t *)malloc(sizeof(neuron_t));
  p->dim = dim;
  p->w = (double *)malloc((p->dim + 1) * sizeof(double)); /* +1 for the bias */

  srand(time(NULL));
  for (size_t i = 0; i < p->dim + 1; i++)
    p->w[i] = 2.0f * ((rand() / (double)RAND_MAX) - 1.0f);

  p->activation = a;
  return p;
}

neuron_t *neuron_clone(const neuron_t *p) {
  neuron_t *clone;
  clone = neuron_create(p->dim, p->activation);
  memcpy(clone->w, p->w, (p->dim + 1) * sizeof(double));
  return clone;
}

void neuron_destroy(neuron_t *p) {
  free(p->w);
  free(p);
}

/* Predicts an input's class */
double neuron_predict(neuron_t *p, double *x) {
  double z = vec_dot(p->dim, p->w, x) + p->w[p->dim];
  return p->activation(z);
}
