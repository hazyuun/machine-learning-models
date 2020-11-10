#ifndef _DATASET_H_
#define _DATASET_H_

#include <stddef.h>

typedef struct {
	size_t len;
	size_t dim;
	float *y;
	float *x;
} labeled_dataset_t;

/* Makes a new empty dataset given its length and the input dimension */
labeled_dataset_t* labeled_dataset_create(size_t dim, size_t len);
void labeled_dataset_destroy(labeled_dataset_t *dataset);

#endif