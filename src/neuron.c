#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <activations.h>
#include <mathutils.h>
#include <metrics.h>
#include <neuron.h>

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

/* Note : All classification learning algorithms implemented here, */
/*	only work with sign as activation 	*/
/* TODO : extend them to work on other activations */

/* Note : Please use THE sign function defined in activations.h */
/*	Do NOT try to implement your own, it won't work, */
/*	since the assertion uses the one in activations.h */

/******************/
/* CLASSIFICATION */
/******************/

/* One iteration of the Perceptron Learning algorithm */
static void PLA_weight_update(neuron_t *p, labeled_dataset_t *data,
                              size_t *t) {
  for (size_t i = 0; i < data->len; i++) {
    if (((neuron_predict(p, data->x + i * p->dim)) != (data->y[i]))) {
      for (size_t j = 0; j < p->dim; j++)
        p->w[j] += data->y[i] * data->x[i * p->dim + j];
      p->w[p->dim] += data->y[i];
      ++(*t);
    }
  }
}

/* Trains a neuron on a dataset using Perceptron Learning algorithm */
history_t *neuron_PLA_learn(neuron_t *p, labeled_dataset_t *data,
                                metric_t metric) {
  assert(p->activation == sign);
  size_t t = 0;
  history_t *history;

  double LS;
  LS = compute_LS(p, data);

  double history_entry = compute_metric(p, data, metric);
  history = history_create(history_entry);

  while (LS != 0) {
    PLA_weight_update(p, data, &t);
    LS = compute_LS(p, data);
    history_entry = compute_metric(p, data, metric);
    history_append(history, history_entry);
  }
  return history;
}

/* One iteration of Pocket algorithm */
static void pocket_weight_update(neuron_t *p, neuron_t *pocket,
                                 labeled_dataset_t *data, size_t *t) {
  double pocket_LS, real_LS;

  for (size_t i = 0; i < data->len; i++) {
    if (((neuron_predict(pocket, data->x + i * pocket->dim)) !=
         (data->y[i]))) {

      /* Change the weights as in the PLA */
      for (size_t j = 0; j < pocket->dim; j++)
        pocket->w[j] += data->y[i] * data->x[i * pocket->dim + j];
      pocket->w[p->dim] += data->y[i];

      /* Calculate losses and keep the best one */
      pocket_LS = compute_LS(pocket, data);
      real_LS = compute_LS(p, data);
      if (real_LS > pocket_LS)
        memcpy(p->w, pocket->w, (p->dim + 1) * sizeof(double));
    }
    ++(*t);
  }
}

history_t *neuron_pocket_learn(neuron_t *p, labeled_dataset_t *data,
                                   metric_t metric, size_t max_iterations) {
  assert(p->activation == sign);
  size_t t = 0;

  history_t *history;
  double history_entry = compute_metric(p, data, metric);
  history = history_create(history_entry);

  neuron_t *pocket;
  pocket = neuron_clone(p);
  /* Well, this is a waste of memory, since we are cloning the entire neuron
   * struct */
  /* all we need to clone is the weights, but since compute_LS needs a
   * neuron_t */
  /* and since I am feeling lazy, I just cloned it */
  /* TODO: Be less lazy */

  while (t < max_iterations) {
    pocket_weight_update(p, pocket, data, &t);
    history_entry = compute_metric(p, data, metric);
    history_append(history, history_entry);
  }
  neuron_destroy(pocket);
  return history;
}

/* One iteration of Adaline (Delta rule) algorithm */
static void adaline_weight_update(neuron_t *p, labeled_dataset_t *data,
                                  size_t *t) {
  for (size_t i = 0; i < data->len; i++) {
    if (((neuron_predict(p, data->x + i * p->dim)) != (data->y[i]))) {
      double e = data->y[i];
      e -= neuron_predict(p, data->x + i * p->dim);
      for (size_t j = 0; j < p->dim; j++)
        p->w[j] += 2 * e * data->x[i * p->dim + j];
      p->w[p->dim] += 2 * e;
    }
  }
  ++(*t);
}

/* I noticed this is pretty much the same code in pocket function */
/* TODO: DRY! Do not repeat yourself */
history_t *neuron_adaline_learn(neuron_t *p, labeled_dataset_t *data,
                                    metric_t metric, size_t max_iterations) {
  assert(p->activation == sign);
  size_t t = 0;

  history_t *history;
  double history_entry = compute_metric(p, data, metric);
  history = history_create(history_entry);

  while (t < max_iterations) {
    adaline_weight_update(p, data, &t);
    history_entry = compute_metric(p, data, metric);
    history_append(history, history_entry);
  }
  return history;
}

/* A wrapper for all training algorithsms */
history_t *neuron_train(neuron_t *p, labeled_dataset_t *data,
                            algorithm_t algorithm, metric_t metric,
                            size_t max_iterations) {
  history_t *history = NULL;

  switch (algorithm) {
  case PLA_ALGO:
    history = neuron_PLA_learn(p, data, metric);
    break;
  case POCKET_ALGO:
    history = neuron_pocket_learn(p, data, metric, max_iterations);
    break;
  case ADALINE_ALGO:
    history = neuron_adaline_learn(p, data, metric, max_iterations);
    break;
  default: /* TODO: Print something ?*/
    break;
  }

  return history;
}

/**************/
/* REGRESSION */
/**************/

/* Returns the jth component of the gradient vector of the MSE */
static double compute_grad_MSE(neuron_t *p, dataset_t *data, size_t index) {
  double grad_mse = 0.0f;

  for (size_t i = 0; i < data->len; i++) {
    double error = (neuron_predict(p, data->x + data->dim * i) -
                    data->x[data->dim * i + p->dim]);

    grad_mse +=
        error * ((index != p->dim) ? data->x[data->dim * i + index] : 1.0);
  }
  grad_mse *= 2.0f;
  grad_mse /= data->len;

  return grad_mse;
}

/* One iteration of least squares method using GD */
static void lsquares_weight_update(neuron_t *p, dataset_t *data,
                                   double learning_rate, size_t *t) {
  /* Calculate the gradient */
  double grad[p->dim + 1];
  for (size_t j = 0; j < p->dim + 1; j++)
    grad[j] = compute_grad_MSE(p, data, j);

  /* Perform gradient decent */
  for (size_t j = 0; j < p->dim + 1; j++)
    p->w[j] -= learning_rate * grad[j];

  ++(*t);
}

/* WARNING : Only works with MSE */
/* metric parameter is there only for flexibility */
/* just in case I want to implement other metrics */
history_t *neuron_lsquares_learn(neuron_t *p, dataset_t *data,
                                     metric_t metric, double learning_rate,
                                     size_t max_iterations) {
  assert(metric == MSE_METRIC);

  history_t *history;
  double history_entry = compute_MSE(p, data);
  history = history_create(history_entry);
  (void)metric;
  size_t t = 0;
  while (t < max_iterations) {
    lsquares_weight_update(p, data, learning_rate, &t);
    history_entry = compute_MSE(p, data);
    history_append(history, history_entry);
  }

  return history;
}

/* Predicts an input's class */
double neuron_predict(neuron_t *p, double *x) {
  double z = vec_dot(p->dim, p->w, x) + p->w[p->dim];
  return p->activation(z);
}
