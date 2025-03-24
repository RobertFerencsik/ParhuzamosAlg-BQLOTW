#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to check if a value already exists in the array
int existsInArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return 1;
    }
    return 0;
}

// Function to generate an array with unique values and 50% probability of duplication
void generateArray(int arr[], int size) {
    srand(time(NULL));
    int uniqueSize = size / 2; // Half of the array will be unique values

    for (int i = 0; i < uniqueSize; i++) {
        int num;
        do {
            num = rand() % 1000; // Generate a random number
        } while (existsInArray(arr, i, num)); // Ensure uniqueness

        arr[i] = num;
    }

    // Duplicate some values with 50% probability
    for (int i = uniqueSize; i < size; i++) {
        if (rand() % 2 == 0) { // 50% chance of duplication
            arr[i] = arr[rand() % uniqueSize]; // Copy from existing values
        } else {
            int num;
            do {
                num = rand() % 1000;
            } while (existsInArray(arr, i, num));
            arr[i] = num;
        }
    }
}

// Function to check if all elements in the array are unique
int hasUniqueElements(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) return 0; // Duplicate found
        }
    }
    return 1; // All unique
}

// Function to measure execution time of the array generation
double measureExecutionTime(void (*func)(int[], int), int arr[], int size) {
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

    // Measure execution time
    double timeTaken = measureExecutionTime(generateArray, arr, size);
    printf("\nArray generated in %.2f µs\n", timeTaken);

    // Check uniqueness
    if (hasUniqueElements(arr, size)) {
        printf("All elements are unique.\n");
    } else {
        printf("The array contains duplicate elements.\n");
    }

    return 0;
}
