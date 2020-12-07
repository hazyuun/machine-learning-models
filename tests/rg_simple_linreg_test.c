#include <helpers/model.h>
#include <helpers/csv2dataset.h>
#include <utils/export.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  /* Load data */
  dataset_t *data = csv_to_dataset("./test-data/regression.csv");
  
  /* Make and train the model */
  single_layer_model_t *model;
  model = make_single_layer_model(LIN_REG_MODEL, 1, &identity);
  history_t *history = model->train(model, data);

  /* Generate the output files for plotting */
  gp_export_dataset(data, "data.in");
  gp_export_single_layer_model(model, history);

  return 0;
}
