#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

// Number of threads to be used in parallel processing
const int N_THREADS = 16;

/**
 * Structure representing a task assigned to a thread.
 * Each thread will process a subset of the data.
 */
typedef struct Task
{
  double* data;           // Pointer to the dataset
  unsigned long offset;   // Starting index for this thread
  unsigned long length;   // Number of elements this thread will process
} Task;

/**
 * Function to generate an array of random floating-point numbers.
 * @param size: Number of elements in the array.
 * @return Pointer to dynamically allocated array.
 */
double* generate_data(unsigned long size)
{
  double* data;
  int i;

  // Allocate memory for the dataset
  data = (double*)malloc(size * sizeof(double));
  
  // Fill the dataset with random floating-point numbers in the range [0, 1]
  for (i = 0; i < size; ++i) {
    data[i] = (double)(rand()) / RAND_MAX;
  }

  return data;
}

/**
 * Function to calculate the elapsed time between two timestamps.
 * @param start_time: Pointer to the starting time structure.
 * @param finish_time: Pointer to the finishing time structure.
 * @return Elapsed time in seconds.
 */
double calc_elapsed_time(struct timespec* start_time, struct timespec* finish_time)
{
  double elapsed_time;

  elapsed_time = (finish_time->tv_sec - start_time->tv_sec);
  elapsed_time += (double)(finish_time->tv_nsec - start_time->tv_nsec) / 1000000000;

  return elapsed_time;
}

/**
 * Function executed by each thread to process its assigned section of data.
 * It applies a mathematical transformation to each element.
 */
void* map_values(void* param)
{
  Task* task;
  int i;
  int index;

  task = (Task*)param;
  printf("Thread processing offset = %lu, length = %lu\n", task->offset, task->length);
  
  // Apply transformation: sqrt(data[index] * 10)
  for (i = 0; i < task->length; ++i) {
    index = task->offset + i;
    task->data[index] = sqrt(task->data[index] * 10);
  }
  return NULL;
}

/**
 * Main function - sets up the dataset, creates threads, and measures execution time.
 */
int main(int argc, char* argv[])
{
  int i, j;
  unsigned long size;
  double* data;
  struct timespec start_time;
  struct timespec finish_time;
  double elapsed_time;
  pthread_t threads[N_THREADS];
  Task tasks[N_THREADS];
  int length;

  // Iterate over different dataset sizes for benchmarking
  for (i = 0; i <= 10; ++i) {
    size = i * 10000000;
    printf(":: size = %lu\n", size);
    
    // Generate dataset
    data = generate_data(size);
    
    // Record start time
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    
    // Divide the dataset into equal parts for each thread
    length = size / N_THREADS;
    printf(":: Create threads ...\n");
    
    // Create threads and assign tasks
    for (j = 0; j < N_THREADS; ++j) {
      tasks[j].data = data;
      tasks[j].offset = j * length;
      tasks[j].length = length;
      pthread_create(&threads[j], NULL, map_values, tasks + j);
    }
    
    // Wait for all threads to complete execution
    printf(":: Join threads ...\n");
    for (j = 0; j < N_THREADS; ++j) {
      pthread_join(threads[j], NULL);
    }
    
    // Record finish time
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish_time);
    
    // Compute elapsed time
    elapsed_time = calc_elapsed_time(&start_time, &finish_time);
    printf(":: time %lu;%lf\n", size, elapsed_time);
    
    // Free dynamically allocated memory
    free(data);
  }

  return 0;
}
