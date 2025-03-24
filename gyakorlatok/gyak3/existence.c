#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Define the batch size for checking values and number of threads
const int BATCH_SIZE = 100;
const int N_THREADS = 4;

// Mutex for synchronizing access to shared variable
pthread_mutex_t batch_mutex = PTHREAD_MUTEX_INITIALIZER;

// Boolean flag to indicate if the value has been found
bool is_existing_value = false;

/**
 * Structure representing a task assigned to a thread.
 * Each thread will search for a specific value within the data.
 */
typedef struct Task
{
  int value;           // The value to search for
  int* data;           // Pointer to the dataset
  unsigned long size;  // Size of the dataset
  unsigned long start_index; // Starting index for this thread
  unsigned long step;        // Step size (determines how threads divide work)
} Task;

/**
 * Function to generate an array of random integers.
 * @param size: Number of elements in the array.
 * @return Pointer to dynamically allocated array.
 */
int* generate_data(unsigned long size)
{
  int* data;
  int i;

  // Allocate memory for the dataset
  data = (int*)malloc(size * sizeof(int));
  
  // Fill the dataset with random integers in the range [0, 100]
  for (i = 0; i < size; ++i) {
    data[i] = 100 * (double)(rand()) / RAND_MAX;
  }

  return data;
}

/**
 * Function executed by each thread to search for a given value in the dataset.
 */
void find_value(Task* task)
{
  int n_steps = 0;
  int i;

  // Iterate through assigned section of the data using the given step size
  for (i = task->start_index; i < task->size; i += task->step) {
    
    // If the target value is found, update the shared flag and print location
    if (task->data[i] == task->value) {
      pthread_mutex_lock(&batch_mutex);
      is_existing_value = true;
      printf("---> Found by thread starting at index %d at position %d!\n", task->start_index, i);
      pthread_mutex_unlock(&batch_mutex);
      return;
    }
    
    // Increment batch counter
    ++n_steps;
    
    // Every BATCH_SIZE iterations, check if another thread has found the value
    if (n_steps == BATCH_SIZE) {
      pthread_mutex_lock(&batch_mutex);
      if (is_existing_value == true) {
        pthread_mutex_unlock(&batch_mutex);
        return; // Exit if another thread has already found the value
      }
      pthread_mutex_unlock(&batch_mutex);
      n_steps = 0; // Reset batch counter
    }
  }
}

/**
 * Main function - sets up the dataset, creates threads, and waits for completion.
 */
int main(int argc, char* argv[])
{
  int* data;
  Task tasks[N_THREADS];  // Array of tasks for threads
  pthread_t threads[N_THREADS]; // Array of thread identifiers
  int i;
  int size;

  // Set the size of the dataset
  size = 1000;
  
  // Generate the dataset
  data = generate_data(size);
  
  // Create and start threads
  for (i = 0; i < N_THREADS; ++i) {
    tasks[i].data = data;
    tasks[i].size = size;
    tasks[i].start_index = i; // Each thread starts at a different index
    tasks[i].step = N_THREADS; // Threads search in a round-robin manner
    tasks[i].value = 10; // Target value to search for
    
    printf(":: Start thread %d ...\n", i);
    pthread_create(&threads[i], NULL, (void* (*)(void*))find_value, tasks + i);
  }
  
  // Wait for all threads to finish
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }
  
  // Print final result indicating whether the value was found
  printf(":: Result = %d\n", is_existing_value);
  
  // Free dynamically allocated memory
  free(data);
  
  return 0;
}
