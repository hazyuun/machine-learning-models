#ifndef _DATASET_H_
#define _DATASET_H_

#include <stddef.h>

/* A collection of points and their respective labels */
/* TODO: Maybe I should use dataset_t inside this */

typedef struct dataset dataset_t;
typedef struct labeled_dataset labeled_dataset_t;

struct labeled_dataset {
	size_t len;
	size_t dim;
	float *y;
	float *x;
};


/* Makes a new empty labeled dataset given its length and the input dimension */
labeled_dataset_t* labeled_dataset_create(size_t dim, size_t len);
void labeled_dataset_destroy(labeled_dataset_t *dataset);

/* A collection of points */
struct dataset{
	size_t len;
	size_t dim;
	float *x;
};

/* Makes a new empty dataset given its length and the input dimension */
dataset_t* dataset_create(size_t dim, size_t len);
void dataset_destroy(dataset_t *dataset);

#endif