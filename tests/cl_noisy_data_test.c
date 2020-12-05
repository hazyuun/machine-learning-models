#include <stdio.h>
#include <stdlib.h>
#include <perceptron.h>
#include <csv.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  csv_t csv = csv_load("./test-data/noisy.csv");

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
  labeled_dataset_t *dataset = labeled_dataset_create(2, 28);
  dataset->x = x;
  dataset->y = y;

  /* Make a new perceptron and train it with the dataset */
  perceptron_t *p = perceptron_create(2, &sign);

  history_t *history;

/* You can switch between pocket and adaline here */
#if 0
	history = perceptron_train(p, dataset, POCKET_ALGO, LOSS_METRIC, 800);
#else
  history = perceptron_train(p, dataset, ADALINE_ALGO, LOSS_METRIC, 1000);
#endif

  /* Print the final weights */
  printf("\n Final weights :");
  for (size_t j = 0; j < p->dim + 1; j++)
    printf("\t%.5f", (double)(p->w[j]));
  printf("\n");

  /* Test the perceptron */
  double in[2] = {4, 4};
  printf("\n Predicted (4, 4) label : %f \n", (double)perceptron_predict(p, in));

  /* Generate the output files for plotting */
  FILE *out;

  /* Points */
  out = fopen("data.in", "w");
  for (size_t i = 0; i < rows - 1; i++) {
    fprintf(out, "%.5lf %.5lf %.5lf\n", x[2 * i], x[2 * i + 1], y[i]);
  }
  fclose(out);

  /* Weights */
  out = fopen("weights.in", "w");
  for (size_t i = 0; i < 3; i++) {
    fprintf(out, "w%ld = %.5lf\n", i, p->w[i]);
  }
  fclose(out);

  /* History */
  double *history_array = history_as_array(history);
  size_t len = history_length(history);
  out = fopen("history.in", "w");
  for (size_t i = 0; i < len; i++) {
    fprintf(out, "%.2lf %.2lf\n", (double)i, history_array[i]);
  }
  fclose(out);
}
