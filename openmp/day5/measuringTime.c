#include<stdio.h>
#include<omp.h>
#include<sys/time.h>
#define N 100

int main(){
    int a[N];
    int sum = 0;
    double exe_time;
	struct timeval stop_time, start_time;

    gettimeofday(&start_time, NULL);
    #pragma omp parallel num_threads(N)
    {
        int i = omp_get_thread_num();
        a[i] = i + 1;

        #pragma omp barrier

        #pragma omp master 
        for(int j = 0; j < N; j++){
            sum+= a[j];
        }
    }
    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec/1000000.0)) - (start_time.tv_sec + (start_time.tv_usec/1000000.0));
    printf("Sum = %d\n", sum);
    printf("Execution time is = %lf seconds\n", exe_time);
    return 0;
}
