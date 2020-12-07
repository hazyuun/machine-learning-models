#ifndef _LOGISTIC_REGRESSION_H_
#define _LOGISTIC_REGRESSION_H_

#include <dataset.h>
#include <models/single_layer/neuron.h>

history_t *log_reg_learn(neuron_t *p, labeled_dataset_t *data, metric_t metric,
                         double learning_rate, size_t max_iterations);

#endif
