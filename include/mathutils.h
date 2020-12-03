#ifndef _MATHUTILS_H_
#define _MATHUTILS_H_
#include <stddef.h>

float vec_dot(size_t n, float *u, float *v);

void vec_scale(size_t n, float k, float *u);

void vec_add(size_t n, float *u, const float *v);

#endif