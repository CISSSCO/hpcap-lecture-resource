#include <omp.h>
#include <stdio.h>

int main() {
    int count = 0;

    #pragma omp parallel 
    {
        #pragma omp atomic
        count++;
    }

    printf("Final count: %d\n", count);
    return 0;
}

