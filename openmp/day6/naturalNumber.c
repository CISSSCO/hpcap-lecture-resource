#include<stdio.h>
#define N 100
#define T 4
int main(){
    int sum = 0;
    int localSum = 0;

#pragma omp parallel private(localSum)  
    {
#pragma omp for 
        for(int i = 1; i <= N; i++){
            localSum+= i;
        }
#pragma omp barrier
#pragma omp critical
        {
            sum+= localSum;
        }
    }
    printf("Sum = %d\n", sum);
    printf("Actual Sum = %d\n", (N * (N + 1)/ 2));
    return 0;
}
