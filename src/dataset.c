#include <dataset.h>
#include <stdlib.h>

/* Makes a new empty labeled dataset given its length and the input dimension */
labeled_dataset_t *labeled_dataset_create(size_t dim, size_t len) {
  labeled_dataset_t *dataset =
      (labeled_dataset_t *)malloc(sizeof(labeled_dataset_t));
  dataset->y = NULL;
  dataset->x = NULL;

  dataset->dim = dim;
  dataset->len = len;
  return dataset;
}

void labeled_dataset_destroy(labeled_dataset_t *dataset) {
  free(dataset->x);
  free(dataset->y);
  free(dataset);
}

/* Makes a new empty dataset given its length and the input dimension */
dataset_t *dataset_create(size_t dim, size_t len) {
  dataset_t *dataset = (dataset_t *)malloc(sizeof(dataset_t));
  dataset->x = NULL;
  dataset->dim = dim;
  dataset->len = len;
  return dataset;
}

void dataset_destroy(dataset_t *dataset) {
  free(dataset->x);
  free(dataset);
}
