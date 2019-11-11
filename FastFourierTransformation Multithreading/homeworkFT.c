#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

typedef double complex cplx;
#define PI acos(-1.0)
#define HELP -2 * PI * I

int nr_threads = 0;
FILE *in, *out;
int N = 0;

double *arr;  //vector cu input
cplx *rez;  // vector cu solutii

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


const cplx constant_exponent(int k, int n) {
	return cexp(k * n * HELP / N);
}

void init(int argc, char *argv[]) {
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	nr_threads = atoi(argv[3]);

	if (fscanf(in, "%d", &N) == 0) {
		exit(1);
	}
	fprintf(out, "%d\n", N);
	arr = malloc(sizeof(double) * N);
	rez = malloc(sizeof(cplx) * N);
	if (arr == NULL || rez == NULL) {
		fprintf(stderr, "malloc failed!\n");
		exit(1);
	}
}

void *threadFunction(void *var) {
	int thread_id = *(int*) var;

	int k = (thread_id * ((double)N / nr_threads));
	int aux = ((double)(thread_id + 1) * ((double)N / nr_threads));

	for (; k < aux && k < N; k++) {
		for (int i = 0; i < N; i++) {
			rez[k] += arr[i] * constant_exponent(k, i);			
		}
	}
	return NULL;
}

void print() {
	for (int i = 0; i < N; i++) {
		fprintf(out, "%lf %lf\n", (double)creal(rez[i]), (double)cimag(rez[i]));
	}
}

int main(int argc, char * argv[]) {
	if (argc < 4) {
		fprintf(stderr, "Too few arguments\n");
		exit(1);
	} else if (argc > 4) {
		fprintf(stderr, "Too many arguments\n");
		exit(1);
	}

	init(argc, argv);	

	pthread_t tid[nr_threads];
	int thread_id[nr_threads];

	for (int i = 0; i < N; i++)
		if (fscanf(in, "%lf", &arr[i]) == 0)
			exit(1);

	for (int i = 0; i < nr_threads; i++) 
		thread_id[i] = i;

	for (int i = 0; i < nr_threads; i++) 
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));

	for (int i = 0; i < nr_threads; i++) 
		pthread_join(tid[i], NULL);

	print();

	fclose(in);
	fclose(out);

	return 0;
}
