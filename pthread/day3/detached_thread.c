#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10000  // Size of the array
#define T 4      // Number of threads

int arr[N];

void *init_array(void *arg) {
    int thread_id = *(int *)arg;
    int chunk_size = N / T;
    int start = thread_id * chunk_size;
    int end = (thread_id + 1) * chunk_size;

    if (thread_id == T - 1) {
        end = N;
    }

    for (int i = start; i < end; ++i) {
        arr[i] = i + 1;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[T];
    pthread_attr_t attr;
    int thread_args[T];

    // Initialize thread attributes
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Create detached threads to initialize array
    for (int i = 0; i < T; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], &attr, init_array, (void *)&thread_args[i]);
    }

    // Destroy thread attributes
    pthread_attr_destroy(&attr);

    // Optional: Main thread can perform other tasks or wait
    // e.g., usleep(1000); // Wait for threads to complete if necessary

    printf("Array initialization using detached threads...\n");

    // Main thread continues execution
    // Print or use initialized array if needed

    // Example: Print a few initialized array elements
    printf("Initialized array elements:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
