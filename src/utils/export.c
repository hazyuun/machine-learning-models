#include <dataset.h>
#include <export.h>
#include <metrics.h>
#include <helpers/model.h>
#include <stdio.h>

uint8_t gp_export_dataset(dataset_t *dataset, const char *filename) {
  FILE *out = fopen(filename, "w");

  if (!out)
    return 1;

  for (size_t i = 0; i < dataset->len; i++)
    fprintf(out, "%.5lf %.5lf %.5lf\n", dataset->x[2 * i],
            dataset->x[2 * i + 1], 1.0);

  fclose(out);
  return 0;
}

uint8_t gp_export_labeled_dataset(labeled_dataset_t *dataset,
                                  const char *filename) {
  FILE *out = fopen(filename, "w");

  if (!out)
    return 1;

  for (size_t i = 0; i < dataset->len; i++)
    fprintf(out, "%.5lf %.5lf %.5lf\n", dataset->x[2 * i],
            dataset->x[2 * i + 1], dataset->y[i]);

  fclose(out);
  return 0;
}

uint8_t gp_export_history(history_t *history, const char *filename) {

  FILE *out = fopen(filename, "w");
  if (!out)
    return 1;

  history_t *current = history;
  size_t i = 0;

  while (current) {
    fprintf(out, "%.2lf %.2lf\n", (double)i++, current->value);
    current = current->next;
  }

  fclose(out);
  return 0;
}

uint8_t gp_export_weights(neuron_t *neuron, const char *filename) {
  FILE *out = fopen(filename, "w");

  if (!out)
    return 1;

  for (size_t i = 0; i < neuron->dim + 1; i++) {
    fprintf(out, "w%ld = %.5lf\n", i, neuron->w[i]);
  }
  fclose(out);
  return 0;
}


uint8_t gp_export_single_layer_model(single_layer_model_t *model,
                                     history_t *history) {

  return gp_export_weights(model->neuron, "weights.in") |
         gp_export_history(history, "history.in");
}