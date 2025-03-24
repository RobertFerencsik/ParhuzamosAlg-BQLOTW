#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to read an array
void readArray(int arr[], int size) {
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
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

// Main function
int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    readArray(arr, size);

    printf("Sum (iterative): %d\n", sumIterative(arr, size));
    printf("Sum (recursive): %d\n", sumRecursive(arr, size));
    printf("Minimum (iterative): %d\n", minIterative(arr, size));
    printf("Minimum (recursive): %d\n", minRecursive(arr, size));
    printf("Maximum (iterative): %d\n", maxIterative(arr, size));
    printf("Maximum (recursive): %d\n", maxRecursive(arr, size));

    return 0;
}
