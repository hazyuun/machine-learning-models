#include <stdio.h>
#include <perceptron.h>

int main(int argc, char **argv){
	(void) argc;
	(void) argv;
	
    /* Use a .csv file and clean this mess */
	/* Points' coordinates */
	float x[] = {
		0.0f, 2.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 2.0f,
		1.0f, 3.0f,
		1.0f, 3.5f,
		2.0f, 1.0f,
		2.0f, 2.0f,
		2.0f, 3.0f,
		2.0f, 3.5f,
		3.0f, 0.0f,
		3.0f, 2.0f,
		2.7f, 3.3f,
		4.0f, 1.0f,
		
		1.0f, 4.0f,
		2.0f, 4.0f,
		2.0f, 5.0f,
		2.5f, 3.0f,
		2.5f, 4.0f,
		3.0f, 3.0f,
		3.0f, 4.5f,
		3.0f, 6.0f,
		4.0f, 2.5f,
		4.0f, 3.5f,
		4.0f, 5.0f,
		5.0f, 2.0f,
		5.0f, 3.0f,
		5.0f, 4.0f,
	};
	/* Points' classes */
	float y[] = {
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f
	};
	
	/* Make a new dataset with the previous arrays */
	labeled_dataset_t *dataset = labeled_dataset_create(2, 28);
	dataset->x = x;
	dataset->y = y;
	
	/* Make a new perceptron and train it with the dataset */
	perceptron_t *p = perceptron_create(2, &sign);

	history_t *history;
	
	/* You can switch between pocket and adaline here */
#if 0
	history = perceptron_train(p, dataset, POCKET_ALGO, LOSS_METRIC, 800);
#else
	history = perceptron_train(p, dataset, ADALINE_ALGO, LOSS_METRIC, 1000);
#endif

	
	/* Print the final weights */
	printf("\n Final weights :");
	for(size_t j = 0; j < p->dim+1; j++)
		printf("\t%.5f",  (float)(p->w[j]));
	printf("\n");
	
	/* Test the perceptron */
	float in[2] = {4, 4};
	printf("\n Predicted (4, 4) label : %f \n", (float)perceptron_predict(p, in));

	/* Generate the output files for plotting */
	FILE *out;
	out = fopen("data.in", "w");
	for(size_t i = 0; i < 28; i++){
		fprintf(out, "%.5lf %.5lf %.5lf\n", x[2*i], x[2*i+1], y[i]);
	}
	fclose(out);
		
	out = fopen("weights.in", "w");
	for(size_t i = 0; i < 3; i++){
		fprintf(out, "w%ld = %.5lf\n", i, p->w[i]);
	}
	fclose(out);

	float *history_array = history_as_array(history);
	size_t len = history_length(history);
	out = fopen("history.in", "w");
	for(size_t i = 0; i < len; i++){
		fprintf(out, "%.2lf %.2lf\n", (float)i, history_array[i]);
	}
	fclose(out);
}

