#include <activations.h>
#include <math.h>

double sign(double x) { return ((x >= 0) ? 1 : -1); }

double sigmoid(double x) { return 1.0f / (1.0f + (double)exp(-x)); }

double identity(double x) { return x; }
