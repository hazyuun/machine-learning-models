#include <csv.h>
#include <export.h>
#include <neuron.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  csv_t csv = csv_load("./test-data/five.csv");

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

  dataset_t *data = dataset_create(5, rows - 1);
  data->x = x;

  neuron_t *p = neuron_create(4, &identity);

  /*
   * learning rate    : 0.01
   * iterations       : 500
   */
  history_t *history =
      neuron_lsquares_learn(p, data, MSE_METRIC, 0.001, 2500);

  /* Some tests */
  double input[] = {1, 83, 60, 40}; // Prediction should be close to 184
  printf("\n Prediction : %lf", neuron_predict(p, input));

  gp_export_history(history, "history.in");

  return 0;
}
