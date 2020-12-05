#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_
#include <stddef.h>

double vec_dot(size_t n, double *u, double *v);

void vec_scale(size_t n, double k, double *u);

void vec_add(size_t n, double *u, const double *v);

#endif