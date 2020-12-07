#include <helpers/model.h>
#include <helpers/csv2dataset.h>
#include <utils/export.h>

#include <stdio.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  /* Load data */
  dataset_t *data = csv_to_dataset("./test-data/five.csv");
  
  /* Make and train the model */
  single_layer_model_t *model;
  model = make_single_layer_model(LIN_REG_MODEL, 4, &identity);
  history_t *history = model->train(model, data);

  /* Try to predict something */
  double input[] = {1, 83, 60, 40}; // Prediction should be close to 184
  printf("\n Prediction : %lf", neuron_predict(model->neuron, input));

  gp_export_history(history, "history.in");

  return 0;
}
