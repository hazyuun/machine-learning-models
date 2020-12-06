#include <logistic_regression.h>

void log_reg_weight_update(neuron_t *p, labeled_dataset_t *data,
                           double learning_rate, size_t *t) {
  /* Calculate the gradient */
  double grad[p->dim + 1];
  for (size_t j = 0; j < p->dim + 1; j++)
    grad[j] = compute_grad_binary_cross_entropy_loss(p, data, j);

  /* Perform gradient decent */
  for (size_t j = 0; j < p->dim + 1; j++)
    p->w[j] -= learning_rate * grad[j];

  ++(*t);
}

history_t *log_reg_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric,
                         double learning_rate, size_t max_iterations) {

  history_t *history;
  double history_entry = compute_binary_cross_entropy_loss(p, data);
  history = history_create(history_entry);
  (void)metric;
  size_t t = 0;
  while (t < max_iterations) {
    log_reg_weight_update(p, data, learning_rate, &t);
    history_entry = compute_binary_cross_entropy_loss(p, data);
    history_append(history, history_entry);
  }

  return history;
}