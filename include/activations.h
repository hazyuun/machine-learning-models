#ifndef _ACTIVATIONS_H_
#define _ACTIVATIONS_H_

#include <math.h>

typedef double (*activation_t)(double);

double sign(double x);
double sigmoid(double x);
double identity(double x);

#endif
