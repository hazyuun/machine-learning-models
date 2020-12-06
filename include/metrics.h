#ifndef _METRICS_H_
#define _METRICS_H_

#include <dataset.h>
#include <stddef.h>

/* This linked list keeps the history of the values of a metric */

typedef struct history_entry history_t;
typedef struct neuron neuron_t;

struct history_entry {
  double value;
  struct history_entry *next;
};

typedef enum { LOSS_METRIC, ACCURACY_METRIC, MSE_METRIC } metric_t;

/* Self explanatory stuff ahead */

history_t *history_create(double first);

void history_destroy(history_t *history);

void history_append(history_t *history, double value);

size_t history_length(history_t *history);

double *history_as_array(history_t *history);

/* Metrics */

/* Computes the percentage of the incorrect predictions */
double compute_LS(neuron_t *p, labeled_dataset_t *data);
/* Computes Mean Squared Error */
double compute_MSE(neuron_t *p, dataset_t *data);
double compute_metric(neuron_t *p, labeled_dataset_t *data,
                      metric_t metric);
#endif
