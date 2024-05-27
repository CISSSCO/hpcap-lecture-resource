#include <stdio.h>
#include <omp.h>
void process(int i) {
    printf("task %d is executed by %d\n", i, omp_get_thread_num());
}
int main() {
    #pragma omp parallel num_threads(5)
    {
        #pragma omp single
        {
            printf("tasks created by %d\n", omp_get_thread_num());
            for (int i = 0; i < 10; i++) {
                #pragma omp task
                process(i);
            }
            #pragma omp taskwait
        }
    }
    return 0;
}

