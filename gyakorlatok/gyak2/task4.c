#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a sorted array of unique values
void generateSortedArray(int arr[], int size) {
    arr[0] = rand() % 10; // First element
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + (rand() % 10 + 1); // Ensure strictly increasing values
    }
}

// Iterative binary search
int binarySearchIterative(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // Not found
}

// Recursive binary search
int binarySearchRecursive(int arr[], int left, int right, int target) {
    if (left > right) return -1; // Base case: not found
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binarySearchRecursive(arr, mid + 1, right, target);
    return binarySearchRecursive(arr, left, mid - 1, target);
}

// Function to measure execution time
double measureExecutionTime(int (*func)(int[], int, int), int arr[], int size, int target) {
    clock_t start, end;
    start = clock();
    func(arr, size, target);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // Convert to microseconds
}

// Main function
int main() {
    srand(time(NULL));
    
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    generateSortedArray(arr, size);

    int target = arr[rand() % size]; // Pick a random element to search

    // Measure execution time
    double timeIterative = measureExecutionTime(binarySearchIterative, arr, size, target);
    clock_t start = clock();
    binarySearchRecursive(arr, 0, size - 1, target);
    clock_t end = clock();
    double timeRecursive = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

    // Print results
    printf("\nSearching for %d in the sorted array.\n", target);
    printf("Iterative Binary Search: %.2f µs\n", timeIterative);
    printf("Recursive Binary Search: %.2f µs\n", timeRecursive);

    return 0;
}
