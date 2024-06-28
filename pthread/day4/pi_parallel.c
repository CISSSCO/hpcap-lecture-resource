#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define N 999999999
#define T 20 // Number of threads

double dx;
pthread_mutex_t mutex;
double area = 0.0;

struct thread_data {
    int start;
    int end;
};

void *compute_area(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    double local_area = 0.0;
    double x, y;

    for (int i = data->start; i < data->end; i++) {
        x = (i + 0.5) * dx; // Midpoint of the interval
        y = sqrt(1 - x * x);
        local_area += y * dx;
    }

    // Acquire mutex before updating global area
    pthread_mutex_lock(&mutex);
    area += local_area;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[T];
    struct thread_data thread_data_array[T];
    double pi, exe_time;
    struct timeval start_time, stop_time;

    dx = 1.0 / N;

    gettimeofday(&start_time, NULL);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int t = 0; t < T; t++) {
        thread_data_array[t].start = t * (N / T);
        thread_data_array[t].end = (t + 1) * (N / T);
        pthread_create(&threads[t], NULL, compute_area, (void *)&thread_data_array[t]);
    }

    // Join threads
    for (int t = 0; t < T; t++) {
        pthread_join(threads[t], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

    pi = 4.0 * area;
    printf("\nValue of pi is = %.16lf\nExecution time is = %lf seconds\n", pi, exe_time);

    return 0;
}
