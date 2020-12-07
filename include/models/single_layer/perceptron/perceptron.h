#ifndef _PERCEPTROH_H_
#define _PERCEPTROH_H_

#include <models/single_layer/neuron.h>

#include <dataset.h>
#include <metrics.h>

/* Trains a neuron on a dataset using Perceptron Learning algorithm */
history_t *PLA_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric);

/* Trains a neuron on a dataset using Pocket algorithm */
history_t *pocket_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric,
                        size_t max_iterations);

/* Trains a neuron on a dataset using Adaline (Delta rule) algorithm */
history_t *adaline_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric,
                         size_t max_iterations);

/* A wrapper for all training algorithsms */
/* Note : max_iterations is ignored when using PLA */
history_t *perceptron_train(neuron_t *p, labeled_dataset_t *data,
                            algorithm_t algorithm, metric_t metric,
                            size_t max_iterations);

#endif
