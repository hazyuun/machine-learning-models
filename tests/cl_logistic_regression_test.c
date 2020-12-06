#include <csv.h>
#include <export.h>
#include <logistic_regression.h>
#include <neuron.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  csv_t csv = csv_load("./test-data/noisy01.csv");

  size_t rows = csv_count_rows(csv);
  size_t cols = csv_count_cols(csv);

  double x[2 * (rows - 1)]; /* 2 inputs */
  double y[1 * (rows - 1)]; /* 1 label */

  for (size_t i = 1; i < rows; i++) {
    for (size_t j = 0; j < cols - 1; j++) {
      x[2 * (i - 1) + j] = atof(csv_get_value(csv, i, j));
    }
  }

  for (size_t i = 1; i < rows; i++) {
    y[i - 1] = atof(csv_get_value(csv, i, cols - 1));
  }

  csv_destroy(csv);

  /* Make a new dataset with the previous arrays */
  labeled_dataset_t *data = labeled_dataset_create(2, rows - 1);
  data->x = x;
  data->y = y;

  /* Make a new neuron and train it with the dataset */
  neuron_t *p = neuron_create(2, &sigmoid);
  history_t *history = log_reg_learn(p, data, 0, 0.01, 10000);

  /* Print the final weights */
  printf("\n Final weights :");
  for (size_t j = 0; j < p->dim + 1; j++)
    printf("\t%.1f", (double)(p->w[j]));
  printf("\n");

  /* Test the neuron */
  double in[2] = {4, 4};
  printf("\n Predicted (4, 4) label : %f \n", (double)neuron_predict(p, in));

  printf("\n loss : %f \n", compute_binary_cross_entropy_loss(p, data));

  /* Generate the output files for plotting */
#if 1
  gp_export_labeled_dataset(data, "data.in");

#else /* To plot a bunch of points to visualize the boundary */
  FILE *out = fopen("data.in", "w");

  if (!out)
    return 1;

  for (double xx = 0.0; xx < 10.0; xx += 0.1) {
    for (double yy = 0.0; yy < 8.0; yy += 0.1) {
      double inin[2] = {xx, yy};
      fprintf(out, "%.5lf %.5lf %.5lf\n", xx, yy, neuron_predict(p, inin));
    }
  }

  fclose(out);
#endif
  gp_export_weights(p, "weights.in");
  gp_export_history(history, "history.in");
}
