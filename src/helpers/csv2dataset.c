#include <helpers/csv2dataset.h>
#include <stdlib.h>

#ifdef USE_RAINY_CSV

#include <csv.h>

dataset_t *csv_to_dataset(const char *filename){
  csv_t csv = csv_load(filename);

  /* -1 because the first row is only for the headers */
  size_t rows = csv_count_rows(csv);
  size_t cols = csv_count_cols(csv);
  const size_t n = (rows - 1) * cols;

  double *x = (double*) malloc(n * sizeof(double));

  for (size_t i = 1; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      x[cols * (i - 1) + j] = atof(csv_get_value(csv, i, j));
    }
  }

  csv_destroy(csv);

  dataset_t *data = dataset_create(cols, rows - 1);
  data->x = x;

  return data;
}

labeled_dataset_t *csv_to_labeled_dataset(const char *filename){
  csv_t csv = csv_load(filename);

  size_t rows = csv_count_rows(csv);
  size_t cols = csv_count_cols(csv);

  double *x = (double*) malloc((cols - 1) * (rows - 1) * sizeof(double));
  double *y = (double*) malloc(1 * (rows - 1) * sizeof(double));

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
  labeled_dataset_t *data = labeled_dataset_create(cols - 1, rows - 1);
  data->x = x;
  data->y = y;

  return data;
}


#endif