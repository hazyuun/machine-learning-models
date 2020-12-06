#ifndef _LOGISTIC_REGRESSION_H_
#define _LOGISTIC_REGRESSION_H_

#include <neuron.h>
#include <dataset.h>

void log_reg_weight_update(neuron_t *p, labeled_dataset_t *data,
                            double learning_rate, size_t *t);

history_t *log_reg_learn(neuron_t *p, labeled_dataset_t *data,
                          metric_t metric, double learning_rate,
                            size_t max_iterations);

#endif
