#include <stdio.h>
#include <perceptron.h>

int main(int argc, char **argv){
	(void) argc;
	(void) argv;
	
	/* Points' coordinates */
	float x[] = {
		1.0f, 1.0f,
		2.0f, 1.0f,
		2.0f, 2.0f,
		1.0f, 3.0f,
		
		3.0f, 3.0f,
		2.0f, 4.0f,
		5.0f, 4.0f,
		4.0f, 5.0f
	};
	/* Points' classes */
	float y[] = {
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f
	};
	
	/* Make a new dataset with the previous arrays */
	labeled_dataset_t *dataset = labeled_dataset_create(2, 8);
	dataset->x = x;
	dataset->y = y;
	
	/* Make a new perceptron and train it with the dataset */
	perceptron_t *p = perceptron_create(2, &sign);
	perceptron_learn(p, dataset);
	
	/* Print the final weights */
	printf("\n Final weights :");
	for(size_t j = 0; j < p->dim+1; j++)
		printf("\t%.1f",  (float)(p->w[j]));
	printf("\n");
	
	/* Test the perceptron */
	float in[2] = {4, 4};
	printf("\n%f", (float)perceptron_predict(p, in));

	/* Generate the output files for plotting */
	FILE *out;
	out = fopen("data.in", "w");
	for(size_t i = 0; i < 8; i++){
		fprintf(out, "%.2lf %.2lf %.2lf\n", x[2*i], x[2*i+1], y[i]);
	}
	fclose(out);	
	out = fopen("weights.in", "w");
	for(size_t i = 0; i < 3; i++){
		fprintf(out, "w%ld = %.2lf\n", i, p->w[i]);
	}
	fclose(out);
}

