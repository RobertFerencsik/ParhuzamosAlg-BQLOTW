#include <pthread.h>  // Include pthread for multithreading
#include <stdio.h>    // Standard I/O functions
#include <stdlib.h>   // Memory allocation and random number generation
#include <time.h>     // Time functions for seeding random numbers

// Maximum number of threads allowed
const int N_MAX_THREADS = 8;

// Mutex to synchronize access to thread_count
pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int thread_count = 1;  // Keeps track of active threads

// Structure defining a task for summing up array elements
typedef struct Task {
    double* data;        // Pointer to data array
    unsigned long a;     // Start index
    unsigned long b;     // End index
    double result;       // Stores the sum of elements from a to b
} Task;

/**
 * Function to generate an array of random double values.
 * @param size: The number of elements to generate.
 * @return Pointer to dynamically allocated array.
 */
double* generate_data(unsigned long size) {
    double* data;
    int i;
    
    data = (double*)malloc(size * sizeof(double));  // Allocate memory
    for (i = 0; i < size; ++i) {
        data[i] = (double)(rand()) / RAND_MAX;  // Generate random number between 0 and 1
    }
    return data;
}

/**
 * Recursively aggregate values in the given range [a, b].
 * @param task: Pointer to the task structure containing data and range.
 */
void aggregate_values(Task* task) {
    int center;
    Task task_1, task_2;
    pthread_t thread;

    // Print the current range being processed
    printf("[%lu, %lu]\n", task->a, task->b);

    // Base case: If only one element, return its value
    if (task->a == task->b) {
        task->result = task->data[task->a];
    } else {
        // Find the middle index to divide the work
        center = (task->a + task->b) / 2;
        
        // Create two sub-tasks for left and right halves
        task_1.data = task->data;
        task_1.a = task->a;
        task_1.b = center;
        
        task_2.data = task->data;
        task_2.a = center + 1;
        task_2.b = task->b;
        
        // Lock mutex to safely update thread count
        pthread_mutex_lock(&thread_count_mutex);
        if (thread_count < N_MAX_THREADS) {
            printf("Start thread ...\n");
            pthread_create(&thread, NULL, (void* (*)(void*))aggregate_values, &task_1);
            ++thread_count;
            pthread_mutex_unlock(&thread_count_mutex);
            
            // Compute the second half in the same thread
            aggregate_values(&task_2);
            
            // Wait for the new thread to complete
            pthread_join(thread, NULL);
            printf("Stop thread ...\n");
            
            // Decrement thread count after completion
            pthread_mutex_lock(&thread_count_mutex);
            --thread_count;
            pthread_mutex_unlock(&thread_count_mutex);
        } else {
            pthread_mutex_unlock(&thread_count_mutex);
            
            // No more available threads, compute both parts sequentially
            aggregate_values(&task_1);
            aggregate_values(&task_2);
        }
        
        // Store the sum of both halves in the result
        task->result = task_1.result + task_2.result;
    }
}

/**
 * Main function - entry point of the program.
 */
int main(int argc, char* argv[]) {
    unsigned long size;
    Task task;
    int i;

    // Define the size of the data array
    size = 1000;
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate random data
    task.data = generate_data(size);
    
    // Print generated data
    for (i = 0; i < size; ++i) {
        printf(":: data[%d] = %lf\n", i, task.data[i]);
    }
    
    // Set the range for processing
    task.a = 0;
    task.b = size - 1;
    
    // Start the recursive sum calculation
    aggregate_values(&task);
    
    // Print the final result
    printf(":: Result = %lf\n", task.result);
    
    // Free dynamically allocated memory
    free(task.data);
    
    return 0;
}
