#ifndef _LINEAR_REGRESSION_H_
#define _LINEAR_REGRESSION_H_

#include <models/single_layer/neuron.h>

#include <dataset.h>
#include <metrics.h>
#include <models/single_layer/perceptron/perceptron.h>

/* Trains a neuron for linear regression with least squares method */
history_t *neuron_lsquares_learn(neuron_t *p, dataset_t *data, metric_t metric,
                                 double learning_rate, size_t max_iterations);

#endif
