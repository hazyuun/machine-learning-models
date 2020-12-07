#include <dataset.h>
#include <metrics.h>
#include <models/single_layer/neuron.h>
#include <models/single_layer/perceptron/perceptron.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* One iteration of the Perceptron Learning algorithm */
static void PLA_weight_update(neuron_t *p, labeled_dataset_t *data, size_t *t) {
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
history_t *PLA_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric) {
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
    if (((neuron_predict(pocket, data->x + i * pocket->dim)) != (data->y[i]))) {

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

history_t *pocket_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric,
                        size_t max_iterations) {
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
history_t *adaline_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric,
                         size_t max_iterations) {
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
history_t *perceptron_train(neuron_t *p, labeled_dataset_t *data,
                            algorithm_t algorithm, metric_t metric,
                            size_t max_iterations) {
  history_t *history = NULL;

  switch (algorithm) {
  case PLA_ALGO:
    history = PLA_learn(p, data, metric);
    break;
  case POCKET_ALGO:
    history = pocket_learn(p, data, metric, max_iterations);
    break;
  case ADALINE_ALGO:
    history = adaline_learn(p, data, metric, max_iterations);
    break;
  default: /* TODO: Print something ?*/
    break;
  }

  return history;
}
