#include <csv.h>
#include <export.h>
#include <neuron.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  csv_t csv = csv_load("./test-data/regression.csv");

  /* -1 because the first row is only for the headers */
  size_t rows = csv_count_rows(csv);
  size_t cols = csv_count_cols(csv);
  const size_t n = (rows - 1) * cols;

  double x[n];

  for (size_t i = 1; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      x[cols * (i - 1) + j] = atof(csv_get_value(csv, i, j));
    }
  }

  csv_destroy(csv);

  dataset_t *data = dataset_create(2, 12);
  data->x = x;

  neuron_t *p = neuron_create(1, &identity);

  /*
   * learning rate    : 0.01
   * iterations       : 500
   */
  history_t *history =
      neuron_lsquares_learn(p, data, MSE_METRIC, 0.01, 500);

  gp_export_dataset(data, "data.in");
  gp_export_weights(p, "weights.in");
  gp_export_history(history, "history.in");

  return 0;
}
