#ifndef _METRICS_H_
#define _METRICS_H_

#include <stddef.h>

/* This linked list keeps the history of the values of a metric */
typedef struct history_entry {
	float value;
	struct history_entry *next;
} history_t;

typedef enum {
	LOSS,
	ACCURACY
} metric_t;


/* Self explanatory stuff ahead */

history_t *history_create(float first);

void history_destroy(history_t *history);

void history_append(history_t *history, float value);

size_t history_length(history_t *history);

float *history_as_array(history_t *history);

#endif
