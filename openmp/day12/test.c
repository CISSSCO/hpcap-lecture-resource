#include <omp.h>
#include <stdio.h>
int main() {
    int shared_var = 0;

    #pragma omp parallel 
    {
        shared_var+= omp_get_thread_num();
    }
    printf("value : %d\n", shared_var);

    return 0;
}

