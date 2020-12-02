#ifndef _ACTIVATIONS_H_
#define _ACTIVATIONS_H_

#include <math.h>

typedef float (*activation_t)(float);

float sign(float x);
float sigmoid(float x);
float identity(float x);

#endif
