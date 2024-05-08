#include<stdio.h>
#define N 100
#define T 4
int main(){
    int sum = 0;
    int localSum = 0;
    int a[N];
    for(int i = 0; i < N; i++)
        a[i] = i + 1;

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
    printf("Sum = %d\n", sum);
    printf("Actual Sum = %d\n", (N * (N + 1)/ 2));
    return 0;
}
