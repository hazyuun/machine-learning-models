#ifndef _METRICS_H_
#define _METRICS_H_

#include <stddef.h>
#include <dataset.h>


/* This linked list keeps the history of the values of a metric */

typedef struct history_entry history_t;
typedef struct perceptron perceptron_t;

struct history_entry {
	float value;
	struct history_entry *next;
};


typedef enum {
	LOSS_METRIC,
	ACCURACY_METRIC,
    MSE_METRIC
} metric_t;


/* Self explanatory stuff ahead */

history_t *history_create(float first);

void history_destroy(history_t *history);

void history_append(history_t *history, float value);

size_t history_length(history_t *history);

float *history_as_array(history_t *history);


/* Metrics */


/* Computes the percentage of the incorrect predictions */
float compute_LS(perceptron_t *p, labeled_dataset_t *data);
/* Computes Mean Squared Error */
float compute_MSE(perceptron_t *p, dataset_t *data);
float compute_metric(perceptron_t *p, labeled_dataset_t *data, metric_t metric);
#endif
