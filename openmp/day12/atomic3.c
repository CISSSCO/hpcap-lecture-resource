#include <omp.h>
#include <stdio.h>

int main() {
    int x = 110, y;

    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();
        #pragma omp atomic capture
        y = x++;
        printf("Thread %d: x was %d, now y is %d\n", thread_id, x, y);
    }

    printf("Final y: %d\n", y);
    return 0;
}

