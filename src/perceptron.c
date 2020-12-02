#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include <perceptron.h>
#include <activations.h>
#include <metrics.h>
#include <mathutils.h>

/* Makes a perceptron given its input dimension and its activation function */
/* and initialize its weights to random values between -1 and 1				*/
perceptron_t *perceptron_create(size_t dim, activation_t a){
	perceptron_t *p = (perceptron_t*) malloc(sizeof(perceptron_t));
	p->dim = dim;
	p->w = (float*) malloc((p->dim + 1) * sizeof(float)); /* +1 for the bias */
	
	srand(time(NULL));
	for(size_t i = 0; i < p->dim + 1; i++)
		p->w[i] = 2.0f*((rand() / (float)RAND_MAX) - 1.0f);
	
	p->activation = a;
	return p;
}

perceptron_t *perceptron_clone(const perceptron_t *p){
	perceptron_t *clone;
	clone = perceptron_create(p->dim, p->activation);
	memcpy(clone->w, p->w, (p->dim + 1)*sizeof(float));
	return clone;
}

void perceptron_destroy(perceptron_t *p){
	free(p->w);
	free(p);	
}

/* Note : All classification learning algorithms implemented here, */
/*	only work with sign as activation 	*/
/* TODO : extend them to work on other activations */


/* Note : Please use THE sign function defined in activations.h */
/*	Do NOT try to implement your own, it won't work, */
/*	since the assertion uses the one in activations.h */


/******************/
/* CLASSIFICATION */
/******************/

/* One iteration of the Perceptron Learning algorithm */
static void PLA_weight_update(perceptron_t *p, labeled_dataset_t *data, size_t *t){
	for(size_t i = 0; i < data->len; i++){
		if(((perceptron_predict(p, data->x + i*p->dim)) != (data->y[i]))){		
			for(size_t j = 0; j < p->dim; j++)
				p->w[j] += data->y[i] * data->x[i*p->dim + j];
			p->w[p->dim] += data->y[i];
			++(*t);
		}
	}
}


/* Trains a perceptron on a dataset using Perceptron Learning algorithm */
history_t *perceptron_PLA_learn(perceptron_t *p, labeled_dataset_t *data, metric_t metric){
	assert(p->activation == sign);
	size_t t = 0;
	history_t *history;
	
	float LS;
	LS = compute_LS(p, data);
	
	float history_entry = compute_metric(p, data, metric);
	history = history_create(history_entry);
	
	while(LS != 0){
		PLA_weight_update(p, data, &t);
		LS = compute_LS(p, data);
		history_entry = compute_metric(p, data, metric);
		history_append(history, history_entry);
	}
	return history;
}

/* One iteration of Pocket algorithm */
static void pocket_weight_update(perceptron_t *p, perceptron_t *pocket, labeled_dataset_t *data, size_t *t){
	float pocket_LS, real_LS;

	for(size_t i = 0; i < data->len; i++){	
		if(((perceptron_predict(pocket, data->x + i*pocket->dim)) != (data->y[i]))){
			
			/* Change the weights as in the PLA */
			for(size_t j = 0; j < pocket->dim; j++)
				pocket->w[j] += data->y[i] * data->x[i*pocket->dim + j];
			pocket->w[p->dim] += data->y[i];
			
			/* Calculate losses and keep the best one */
			pocket_LS = compute_LS(pocket, data);
			real_LS = compute_LS(p, data);
			if(real_LS > pocket_LS)
				memcpy(p->w, pocket->w, (p->dim+1)*sizeof(float));	
		}
		++(*t);
	}
	
}

history_t *perceptron_pocket_learn(perceptron_t *p, labeled_dataset_t *data, metric_t metric, size_t max_iterations){
	assert(p->activation == sign);	
	size_t t = 0;
	
	history_t *history;
	float history_entry = compute_metric(p, data, metric);
	history = history_create(history_entry);
	
	perceptron_t *pocket;
	pocket = perceptron_clone(p);
	/* Well, this is a waste of memory, since we are cloning the entire perceptron struct */
	/* all we need to clone is the weights, but since compute_LS needs a perceptron_t */
	/* and since I am feeling lazy, I just cloned it */
	/* TODO: Be less lazy */
	
	while(t < max_iterations){
		pocket_weight_update(p, pocket, data, &t);	
		history_entry = compute_metric(p, data, metric);
		history_append(history, history_entry);
	}
	perceptron_destroy(pocket);
	return history;
}

/* One iteration of Adaline (Delta rule) algorithm */
static void adaline_weight_update(perceptron_t *p, labeled_dataset_t *data, size_t *t){
	for(size_t i = 0; i < data->len; i++){
		if(((perceptron_predict(p, data->x + i*p->dim)) != (data->y[i]))){
			float e = data->y[i];
			e -= perceptron_predict(p, data->x + i*p->dim);
			for(size_t j = 0; j < p->dim; j++)
				p->w[j] += 2 * e * data->x[i*p->dim + j];
			p->w[p->dim] += 2*e;
		}
	}
	++(*t);
}

/* I noticed this is pretty much the same code in pocket function */
/* TODO: DRY! Do not repeat yourself */
history_t *perceptron_adaline_learn(perceptron_t *p, labeled_dataset_t *data, metric_t metric, size_t max_iterations){
	assert(p->activation == sign);
	size_t t = 0;

	history_t *history;
	float history_entry = compute_metric(p, data, metric);
	history = history_create(history_entry);
		
	while(t < max_iterations){
		adaline_weight_update(p, data, &t);
		history_entry = compute_metric(p, data, metric);
		history_append(history, history_entry);
	}
	return history;
}

/* A wrapper for all training algorithsms */
history_t *perceptron_train(perceptron_t *p, labeled_dataset_t *data, algorithm_t algorithm, metric_t metric, size_t max_iterations){
	history_t *history = NULL;
	
	switch(algorithm){
	case PLA_ALGO:
		history = perceptron_PLA_learn(p, data, metric);
		break;
	case POCKET_ALGO:
		history = perceptron_pocket_learn(p, data, metric, max_iterations);
		break;
	case ADALINE_ALGO:
		history = perceptron_adaline_learn(p, data, metric, max_iterations);
		break;
	default: /* TODO: Print something ?*/
		break;
	}
	
	return history;
}

/**************/
/* REGRESSION */
/**************/

/* Returns the jth component of the gradient vector of the MSE */
static float compute_grad_MSE(perceptron_t *p, dataset_t *data, size_t index){
    float grad_mse = 0.0f;
    
    if(index != p->dim){
        for(size_t i = 0; i < data->len; i++){
            grad_mse += data->x[data->dim*i + index] 
                        * (perceptron_predict(p, data->x + data->dim*i) - data->x[data->dim*i + p->dim]);
        }
    }else{
        for(size_t i = 0; i < data->len; i++)
            grad_mse += (perceptron_predict(p, data->x + data->dim*i) - data->x[data->dim*i + p->dim]);
    }
    
    grad_mse *= 2.0f;
    grad_mse /= data->len;
    
    return grad_mse;
}

/* One iteration of least squares method using GD */
static void lsquares_weight_update(perceptron_t *p, dataset_t *data, float learning_rate, size_t *t){
    /* Calculate the gradient */
    float grad[p->dim+1];
    for(size_t j = 0; j < p->dim+1; j++)
        grad[j] = compute_grad_MSE(p, data, j);
    
    /* Perform gradient decent */
    for(size_t j = 0; j < p->dim+1; j++)
        p->w[j] -= learning_rate * grad[j];
        
    ++(*t);
}

/* WARNING : Only works with MSE */
/* metric parameter is there only for flexibility */
/* just in case I want to implement other metrics */
history_t *perceptron_lsquares_learn(perceptron_t *p, dataset_t *data, metric_t metric, float learning_rate, size_t max_iterations){
    assert(metric == MSE_METRIC);
    
    history_t *history;
    float history_entry = compute_MSE(p, data);
    history = history_create(history_entry);
    (void) metric;
    size_t t = 0;
    while(t < max_iterations){
        lsquares_weight_update(p, data, learning_rate, &t);
        history_entry = compute_MSE(p, data);
        history_append(history, history_entry);
    }
    
    return history;
}



/* Predicts an input's class */
float perceptron_predict(perceptron_t *p, float *x){
	float z = vec_dot(p->dim, p->w, x) + p->w[p->dim];
	return p->activation(z);
}

