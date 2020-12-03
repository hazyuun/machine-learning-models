#include <activations.h>
#include <math.h>

float sign(float x) { return ((x >= 0) ? 1 : -1); }

float sigmoid(float x) { return 1.0f / (1.0f + (float)exp(-x)); }

float identity(float x) { return x; }
