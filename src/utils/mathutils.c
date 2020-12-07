#include <mathutils.h>

double vec_dot(size_t n, double *u, double *v) {
  double d = 0;
  for (size_t i = 0; i < n; i++)
    d += u[i] * v[i];
  return d;
}

void vec_scale(size_t n, double k, double *u) {
  for (size_t i = 0; i < n; i++)
    u[i] *= k;
}

void vec_add(size_t n, double *u, const double *v) {
  for (size_t i = 0; i < n; i++)
    u[i] += v[i];
}
