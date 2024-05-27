#include <stdio.h>
#include <omp.h>
void process(int i) {
    printf("Processing %d\n", i);
}
int main() {
    #pragma omp parallel num_threads(5)
    {
        #pragma omp single
        {
            for (int i = 0; i < 10; i++) {
                #pragma omp task
                process(i);
            }
            #pragma omp taskwait
        }
    }
    return 0;
}

