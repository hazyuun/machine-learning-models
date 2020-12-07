#ifndef _MODEL_H_
#define _MODEL_H_

#include <models/single_layer.h>
#include <stddef.h>

typedef enum model_type model_type_t;
typedef struct single_layer_model single_layer_model_t;

enum model_type { PERCEPTRON_MODEL, LOG_REG_MODEL, LIN_REG_MODEL };

typedef history_t *(*trainer_t)(single_layer_model_t *, void *);

struct single_layer_model {
  neuron_t *neuron;
  model_type_t type;
  algorithm_t algorithm;
  metric_t metric;
  size_t epochs;
  double learning_rate;
  trainer_t train;
};

single_layer_model_t *
make_single_layer_model(model_type_t type, size_t input_dim, activation_t act);

#endif