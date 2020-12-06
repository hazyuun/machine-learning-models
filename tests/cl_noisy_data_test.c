#include <export.h>
#include <stdio.h>
#include <stdlib.h>

#include <csv.h>
#include <neuron.h>

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
  labeled_dataset_t *data = labeled_dataset_create(2, 28);
  data->x = x;
  data->y = y;

  /* Make a new neuron and train it with the dataset */
  neuron_t *p = neuron_create(2, &sign);

  history_t *history;

/* You can switch between pocket and adaline here */
#if 0
	history = neuron_train(p, dataset, POCKET_ALGO, LOSS_METRIC, 800);
#else
  history = neuron_train(p, data, ADALINE_ALGO, LOSS_METRIC, 1000);
#endif

  /* Print the final weights */
  printf("\n Final weights :");
  for (size_t j = 0; j < p->dim + 1; j++)
    printf("\t%.5f", (double)(p->w[j]));
  printf("\n");

  /* Test the neuron */
  double in[2] = {4, 4};
  printf("\n Predicted (4, 4) label : %f \n",
         (double)neuron_predict(p, in));

  /* Generate the output files for plotting */
  gp_export_labeled_dataset(data, "data.in");
  gp_export_weights(p, "weights.in");
  gp_export_history(history, "history.in");
}
