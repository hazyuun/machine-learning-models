#include <models/single_layer/linear_regression/linear_regression.h>
#include <assert.h>

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
history_t *neuron_lsquares_learn(neuron_t *p, dataset_t *data, metric_t metric,
                                 double learning_rate, size_t max_iterations) {
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
