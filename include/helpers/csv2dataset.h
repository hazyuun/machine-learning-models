#ifndef _CSV2DATASET_H_
#define _CSV2DATASET_H_

#include <dataset.h>

dataset_t *csv_to_dataset(const char *filename);
labeled_dataset_t *csv_to_labeled_dataset(const char *filename);

#endif