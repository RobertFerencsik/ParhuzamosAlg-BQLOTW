#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random array
void generateArray(int arr[], int size) {
    srand(time(NULL)); // Seed for random numbers
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Random numbers between 0-999
    }
}

// Iterative sum calculation
int sumIterative(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Recursive sum calculation
int sumRecursive(int arr[], int size) {
    if (size == 0) return 0;
    return arr[size - 1] + sumRecursive(arr, size - 1);
}

// Iterative minimum search
int minIterative(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

// Recursive minimum search
int minRecursive(int arr[], int size) {
    if (size == 1) return arr[0];
    int min_rest = minRecursive(arr, size - 1);
    return (arr[size - 1] < min_rest) ? arr[size - 1] : min_rest;
}

// Iterative maximum search
int maxIterative(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// Recursive maximum search
int maxRecursive(int arr[], int size) {
    if (size == 1) return arr[0];
    int max_rest = maxRecursive(arr, size - 1);
    return (arr[size - 1] > max_rest) ? arr[size - 1] : max_rest;
}

// Function to measure execution time
double measureExecutionTime(int (*func)(int[], int), int arr[], int size) {
    clock_t start, end;
    start = clock();
    func(arr, size);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // Convert to microseconds
}

// Main function
int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    generateArray(arr, size);

    // Measure and print execution times
    printf("\nExecution Time (microseconds):\n");
    printf("Sum (iterative): %.2f µs\n", measureExecutionTime(sumIterative, arr, size));
    printf("Sum (recursive): %.2f µs\n", measureExecutionTime(sumRecursive, arr, size));
    printf("Min (iterative): %.2f µs\n", measureExecutionTime(minIterative, arr, size));
    printf("Min (recursive): %.2f µs\n", measureExecutionTime(minRecursive, arr, size));
    printf("Max (iterative): %.2f µs\n", measureExecutionTime(maxIterative, arr, size));
    printf("Max (recursive): %.2f µs\n", measureExecutionTime(maxRecursive, arr, size));

    return 0;
}
