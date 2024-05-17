#include <omp.h>
#include <stdio.h>

int main() {
    int x = 0, y;

    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();
        #pragma omp atomic capture
        y = x++;
        printf("Thread %d: x was %d, now x is %d\n", thread_id, y, y+1);
    }

    printf("Final x: %d\n", x);
    return 0;
}

