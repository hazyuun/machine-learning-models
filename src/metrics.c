#include <metrics.h>
#include <stdlib.h>

history_t *history_create(float first){
	history_t *history;
	history = (history_t*) malloc(sizeof(history_t));
	history->next = NULL;
	history->value = first;
	return history;
}

void history_destroy(history_t *history){
	if(!history) return;
	history_destroy(history->next);
	free(history);
}

void history_append(history_t *history, float value){
	if(!history) return;
	while(history->next)
		history = history->next;
	history->next = history_create(value);
}

size_t history_length(history_t *history){
	if(!history) return 0;
	return 1 + history_length(history->next);
}

float *history_as_array(history_t *history){
	size_t len = history_length(history);
	float *output = (float*) malloc(len * sizeof(float));
	
	for(size_t i = 0; i < len; i++){
		output[i] = history->value;
		history = history->next;
	}	
	return output;
}

