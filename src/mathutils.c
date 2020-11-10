#include <mathutils.h>

float vec_dot(size_t n, float *u, float *v){
	float d = 0;
	for(size_t i = 0; i < n; i++)
		d += u[i]*v[i];
	return d;
}

void vec_scale(size_t n, float k,  float *u){
	for(size_t i = 0; i < n; i++)
		u[i] *= k;
}

void vec_add(size_t n, float *u, const float *v){
	for(size_t i = 0; i < n; i++)
		u[i] += v[i];
}

