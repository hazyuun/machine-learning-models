#include <csv.h>
#include <perceptron.h>
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

  perceptron_t *p = perceptron_create(4, &identity);

  /*
   * learning rate    : 0.01
   * iterations       : 500
   */
  history_t *history =
      perceptron_lsquares_learn(p, data, MSE_METRIC, 0.001, 2500);

  /* Some tests */
#if 1
  double input[] = {1, 83, 60, 40}; // Prediction should be close to 184
  printf("\n Prediction : %lf", perceptron_predict(p, input));
#endif

  /* Generate the output files for plotting */
  FILE *out;

  /* History */
  double *history_array = history_as_array(history);
  size_t len = history_length(history);
  out = fopen("history.in", "w");

  for (size_t i = 0; i < len; i++) {
    fprintf(out, "%.2lf %.2lf\n", (double)i, history_array[i]);
  }

  fclose(out);

  return 0;
}
