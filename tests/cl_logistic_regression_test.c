#include <helpers/model.h>
#include <helpers/csv2dataset.h>
#include <utils/export.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

   /* Load data */
  labeled_dataset_t *data;
  data = csv_to_labeled_dataset("./test-data/noisy01.csv");

  /* Make and train the model */
  single_layer_model_t *model;
  model = make_single_layer_model(LOG_REG_MODEL, 2, &sigmoid);
  history_t *history = model->train(model, data);

  /* Generate the output files for plotting */
  gp_export_labeled_dataset(data, "data.in");
  gp_export_single_layer_model(model, history);
}
