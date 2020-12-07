#include <helpers/model.h>
#include <metrics.h>
#include <stdlib.h>

static history_t *perceptron_model_train(single_layer_model_t *model,
                                         void *data) {
  labeled_dataset_t *dataset = (labeled_dataset_t *)data;
  return perceptron_train(model->neuron, dataset, model->algorithm,
                          model->metric, model->epochs);
}

static history_t *lin_reg_model_train(single_layer_model_t *model, void *data) {
  dataset_t *dataset = (dataset_t *)data;
  return neuron_lsquares_learn(model->neuron, dataset, model->metric,
                               model->learning_rate, model->epochs);
}

static history_t *log_reg_model_train(single_layer_model_t *model, void *data) {
  labeled_dataset_t *dataset = (labeled_dataset_t *)data;
  return log_reg_learn(model->neuron, dataset, model->metric,
                       model->learning_rate, model->epochs);
}

single_layer_model_t *
make_single_layer_model(model_type_t type, size_t input_dim, activation_t act) {
  single_layer_model_t *model;
  model = (single_layer_model_t *)malloc(sizeof(single_layer_model_t));
  model->neuron = neuron_create(input_dim, act);
  model->learning_rate = 0.01;

  switch (type) {
  case PERCEPTRON_MODEL:
    model->algorithm = PLA_ALGO;
    model->metric = LOSS_METRIC;
    model->epochs = 2000;
    model->train = &perceptron_model_train;
    break;
  case LOG_REG_MODEL:
    model->algorithm = BIN_CROSS_ENTROPY_GD_ALGO;
    model->metric = BIN_CROSS_ENTROPY_METRIC;
    model->epochs = 20000;
    model->train = &log_reg_model_train;
    break;
  case LIN_REG_MODEL:
    model->algorithm = LEAST_SQUARES_GD_ALGO;
    model->metric = MSE_METRIC;
    model->epochs = 2000;
    model->train = &lin_reg_model_train;
    break;
  default:
    return NULL; /*TODO: print something ?*/
  }
  return model;
}
