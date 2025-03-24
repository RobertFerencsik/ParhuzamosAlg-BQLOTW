#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
#include <time.h>

typedef struct {
    double *arr;
    int start, end;
    double result;
} ThreadData;

// Function to generate an array with random floating-point numbers
void generateRandomArray(double arr[], int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = ((double)rand() / RAND_MAX) * 100.0; // Random values between 0 and 100
    }
}

// Sequential product calculation
double productSequential(double arr[], int size) {
    double product = 1.0;
    for (int i = 0; i < size; i++) {
        product *= arr[i];
    }
    return product;
}

// Recursive product calculation (with limited recursion depth)
double productRecursive(double arr[], int left, int right, int depthLimit) {
    if (left == right) return arr[left];

    if (depthLimit == 0) { // Prevent excessive recursion depth
        double product = 1.0;
        for (int i = left; i <= right; i++) product *= arr[i];
        return product;
    }

    int mid = (left + right) / 2;
    return productRecursive(arr, left, mid, depthLimit - 1) * 
           productRecursive(arr, mid + 1, right, depthLimit - 1);
}

// Thread function to compute product of a subarray
void *threadProduct(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->result = 1.0;
    for (int i = data->start; i < data->end; i++) {
        data->result *= data->arr[i];
    }
    return NULL;
}

// POSIX Threads parallel product computation
double productPOSIX(double arr[], int size, int numThreads) {
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];
    int chunkSize = size / numThreads;
    double product = 1.0;

    // Create threads
    for (int i = 0; i < numThreads; i++) {
        threadData[i].arr = arr;
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        pthread_create(&threads[i], NULL, threadProduct, &threadData[i]);
    }

    // Join threads and multiply results
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        product *= threadData[i].result;
    }

    return product;
}

// OpenMP parallel for-loop product computation
double productOpenMPParallel(double arr[], int size) {
    double product = 1.0;
    #pragma omp parallel for reduction(*:product)
    for (int i = 0; i < size; i++) {
        product *= arr[i];
    }
    return product;
}

// OpenMP reduction operator
double productOpenMPReduction(double arr[], int size) {
    double product = 1.0;
    #pragma omp parallel for reduction(*:product)
    for (int i = 0; i < size; i++) {
        product *= arr[i];
    }
    return product;
}

// Function to measure execution time for functions requiring (arr[], size) signature
double measureTime(double (*func)(double[], int), double arr[], int size) {
    clock_t start, end;
    start = clock();
    double result = func(arr, size);
    end = clock();
    printf("Result: %f\n", result);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // Convert to microseconds
}

// Function to measure execution time for functions requiring additional arguments (like POSIX or Recursive)
double measureTimeWithExtraArgs(double (*func)(double[], int, int), double arr[], int size, int extraArg) {
    clock_t start, end;
    start = clock();
    double result = func(arr, size, extraArg);
    end = clock();
    printf("Result: %f\n", result);
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // Convert to microseconds
}

int main() {
    int size = 1000000;  // Adjust size for performance testing
    double arr[size];
    generateRandomArray(arr, size);

    printf("Sequential: %.2f µs\n", measureTime(productSequential, arr, size));
    printf("POSIX Threads: %.2f µs\n", measureTimeWithExtraArgs(productPOSIX, arr, size, 4)); // Example with 4 threads
    printf("OpenMP Parallel: %.2f µs\n", measureTime(productOpenMPParallel, arr, size));
    printf("OpenMP Reduction: %.2f µs\n", measureTime(productOpenMPReduction, arr, size));

    return 0;
}
