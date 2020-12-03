#include <metrics.h>
#include <stdlib.h>
#include <perceptron.h>

history_t *history_create(float first) {
  history_t *history;
  history = (history_t *)malloc(sizeof(history_t));
  history->next = NULL;
  history->value = first;
  return history;
}

void history_destroy(history_t *history) {
  if (!history)
    return;
  history_destroy(history->next);
  free(history);
}

void history_append(history_t *history, float value) {
  if (!history)
    return;
  while (history->next)
    history = history->next;
  history->next = history_create(value);
}

size_t history_length(history_t *history) {
  if (!history)
    return 0;
  return 1 + history_length(history->next);
}

float *history_as_array(history_t *history) {
  size_t len = history_length(history);
  float *output = (float *)malloc(len * sizeof(float));

  for (size_t i = 0; i < len; i++) {
    output[i] = history->value;
    history = history->next;
  }
  return output;
}

/* Computes the percentage of the incorrect predictions */
float compute_LS(perceptron_t *p, labeled_dataset_t *data) {
  float LS = 0;
  for (size_t i = 0; i < data->len; i++) {
    if (perceptron_predict(p, data->x + i * p->dim) != data->y[i])
      LS += 1;
  }
  return LS / (float)(data->len);
}

float compute_metric(perceptron_t *p, labeled_dataset_t *data,
                     metric_t metric) {
  switch (metric) {
  case LOSS_METRIC:
    return compute_LS(p, data);
  case ACCURACY_METRIC:
    return 1 - compute_LS(p, data);
  default:
    return -1;
  }
}

/* Computes Mean Squared Error */
float compute_MSE(perceptron_t *p, dataset_t *data) {
  float mse = 0.0f;
  for (size_t i = 0; i < data->len; i++)
    mse += pow(perceptron_predict(p, data->x + 2 * i) - data->x[2 * i + p->dim],
               2);
  mse /= data->len;
  return mse;
}
