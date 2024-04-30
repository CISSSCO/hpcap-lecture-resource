#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<omp.h>
#define N 10000

int main(){
    int a[N];
    double timeForParallel, timeForSerial;
    int maximum_by_single = 0;
    int maximum_by_serial = 0;
    struct timeval startParallel, startSerial, endParallel, endSerial;
    gettimeofday(&startParallel, NULL);
#pragma omp parallel num_threads(N)
    {
        int i = omp_get_thread_num();
        a[i] = rand() % 1000 + 1;
#pragma omp barrier
#pragma omp single
        {
            for(int j = 0; j < N; j++){
                if(a[j] >  maximum_by_single){
                    maximum_by_single = a[j];
                }
            }
        }
    }
    gettimeofday(&endParallel, NULL);

    // serial part goes here
    gettimeofday(&startSerial, NULL);
    for(int j = 0; j < N; j++){
        if(a[j] >  maximum_by_serial){
            maximum_by_serial = a[j];
        }
    }
    gettimeofday(&endSerial, NULL);

    timeForParallel = (endParallel.tv_sec + (endParallel.tv_usec/1000000.0)) - (startParallel.tv_sec + (startParallel.tv_usec/1000000.0));
    timeForSerial = (endSerial.tv_sec + (endSerial.tv_usec/1000000.0)) - (startSerial.tv_sec + (startSerial.tv_usec/1000000.0));
    printf("Maximum by single: %d\n", maximum_by_single);
    printf("Maximum by serial: %d\n", maximum_by_serial);
    printf("Time taken by serial part: %lf\n", timeForSerial);
    printf("Time taken by parallel region: %lf\n", timeForParallel);

    return 0;
}
