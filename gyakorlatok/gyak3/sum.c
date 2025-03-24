#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// to compile: gcc aggregation.c -o run.exe -lpthread

const int N_MAX_THREADS = 5;

pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INTIALIZER;
int thread_count = 1;

typedef struct Task {
	double* data;
	unsigned long a;
	unsigned long b;
	double result;
} Task;

double* generate_data(unsigned long size) {
	double* data;
	int i;
	
	data = (double*)malloc(size * sizeof(double));
	for (i = 0; i < size; i++) {
		data[i] = (double)(rand()) / RAND_MAX;
	}
	return data;
}

void aggragate_values(Task* task) {
	int center;
	Task task_1, task_2;
	pthread_t thread;
	
	printf("[
}
