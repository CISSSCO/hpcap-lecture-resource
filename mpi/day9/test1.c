#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mpi.h>

#define NUM_THREADS 4

void *thread_function(void* arg) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int thread_id = *(int*)arg;
  printf("Thread %d in process %d: Hello World!\n", thread_id, rank);

  // Simulate some work done by the thread
  for (int i = 0; i < 100000; i++) {
    // Do some calculations or operations here
  }

  return NULL;
}

int main(int argc, char* argv[]) {
  int thread_provided;
  int provided = MPI_THREAD_SINGLE;
  int thread_level = MPI_Init_thread(&argc, &argv, provided, &thread_provided);

  // Check the level of thread support provided by MPI
  if (thread_level != MPI_SUCCESS) {
    printf("Error initializing MPI threads\n");
    return 1;
  }

  if (thread_provided != MPI_THREAD_MULTIPLE) {
    printf("Warning: MPI_THREAD_MULTIPLE requested but not provided\n");
  }

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != 4) {
    printf("This program requires exactly 4 processes\n");
    MPI_Finalize();
    return 1;
  }


  // Create threads within each process
  pthread_t threads[NUM_THREADS];
  int thread_ids[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    thread_ids[i] = i;
    pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
  }

  // Wait for all threads to finish
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  MPI_Finalize();

  return 0;
}
