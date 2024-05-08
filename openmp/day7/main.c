#include<stdio.h>
#include<sys/time.h>
#define N 50000
#define T 7
int main(){
    double exe_time;
	struct timeval stop_time, start_time;
    int sum = 0;
    int localSum = 0;
    int a[N];
    for(int i = 0; i < N; i++)
        a[i] = i + 1;

    gettimeofday(&start_time, NULL);
#pragma omp parallel private(localSum) num_threads(T) 
    {
#pragma omp for 
        for(int i = 0; i < N; i++){
            localSum+= a[i];
        }
#pragma omp critical
        {
            sum+= localSum;
        }
    }
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec/1000000.0)) - (start_time.tv_sec + (start_time.tv_usec/1000000.0));
    printf("Sum = %d\n", sum);
    printf("Actual Sum = %d\n", (N * (N + 1)/ 2));
    printf("Parallel Execution time is = %lf seconds\n", exe_time);

    int serialSum = 0;
    gettimeofday(&start_time, NULL);
    for(int i = 0; i < N; i++){
        serialSum+= a[i];
    }
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec/1000000.0)) - (start_time.tv_sec + (start_time.tv_usec/1000000.0));
    printf("Serial Sum = %d\n", serialSum);
    printf("Serial Execution time is = %lf seconds\n", exe_time);
    return 0;
}
