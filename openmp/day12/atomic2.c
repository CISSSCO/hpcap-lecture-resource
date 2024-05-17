#include <omp.h>
#include <stdio.h>

int main() {
    int sum = 0;

    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();
        #pragma omp atomic
        sum += thread_id;
    }

    printf("Final sum: %d\n", sum);
    return 0;
}

