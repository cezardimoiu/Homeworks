/*
* Cezar Gabriel Dimoiu 332CB
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

typedef double complex cplx;
#define PI atan2(1, 1) * 4
#define HELP -2 * PI * I

int nr_threads;
FILE *in, *out;
int N;

cplx *arr;  //vector cu input
cplx *rez;    // vector cu solutii

void init(int argc, char *argv[]) {
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	nr_threads = atoi(argv[3]);

	if (fscanf(in, "%d", &N) == 0) {
		exit(1);
	}
	fprintf(out, "%d\n", N);
	arr = malloc(sizeof(cplx) * N);
	rez = malloc(sizeof(cplx) * N);
	if (arr == NULL || rez == NULL) {
		fprintf(stderr, "malloc failed!\n");
		exit(1);
	}
}

void fft(cplx *buf, cplx *out, int n, int step)   //basic function
{
	if (step < n) {
		fft(out, buf, n, step * 2);
		fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}

void fft2(cplx *buf, cplx *out, int n, int step, int thread_id)
{
	if (step < n) {
		if (thread_id == 0) fft(out, buf, n, step * 2);
		if (thread_id == 1) fft(out + step, buf + step, n, step * 2);

		if (thread_id == 0)
			for (int i = 0; i < n; i += 2 * step) {
				cplx t = cexp(-I * PI * i / n) * out[i + step];
				buf[i / 2]     = out[i] + t;
				buf[(i + n)/2] = out[i] - t;
			}
	}
}

void fft3(cplx *buf, cplx *out, int n, int step) 
{
	if (step < 2) {
		fft3(out, buf, n, step * 2);
		fft3(out + step, buf + step, n, step * 2);
 	}
	for (int i = 0; i < n; i += 2 * step) {
		cplx t = cexp(-I * PI * i / n) * out[i + step];
		buf[i / 2]     = out[i] + t;
		buf[(i + n)/2] = out[i] - t;
	}
}


void *threadFunction(void *var) {
	int thread_id = *(int*) var;

	if (nr_threads == 1) {
		fft(rez, arr, N, 1);
	} else if (nr_threads == 2) {
		if (thread_id == 0) fft2(rez, arr, N, 1, 0);
		if (thread_id == 1) fft2(rez, arr, N, 1, 1);
		
	} else if (nr_threads == 4) {
		if (thread_id == 0) fft(rez,     arr,     N, 4);
		if (thread_id == 1) fft(rez + 1, arr + 1, N, 4);
		if (thread_id == 2) fft(rez + 2, arr + 2, N, 4);
		if (thread_id == 3) fft(rez + 3, arr + 3, N, 4);

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

	double x;
	for (int i = 0; i < N; i++) {
		if (fscanf(in, "%lf", &x) == 0)
			exit(1);
		arr[i] = x;
	}

	for (int i = 0; i < N; i++) 
			rez[i] = arr[i];

	for (int i = 0; i < nr_threads; i++) 
		thread_id[i] = i;

	for (int i = 0; i < nr_threads; i++) 
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));

	for (int i = 0; i < nr_threads; i++) 
		pthread_join(tid[i], NULL);

	if (nr_threads == 4) 
		fft3(rez, arr, N, 1);

	print();

	fclose(in);
	fclose(out);

	return 0;
}
