#include <omp.h>
#include <stdio.h>

omp_lock_t lock;

void solve(int thread_id) {
    omp_set_lock(&lock);    
    printf("Thread %d entering critical section\n", thread_id);
    
    printf("Thread %d leaving critical section\n", thread_id);
    omp_unset_lock(&lock);  
}

int main() {
    omp_init_lock(&lock);  
    int sum = 0;

    #pragma omp parallel shared(sum) num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        solve(thread_id);
    }

    omp_destroy_lock(&lock); 
    return 0;
}

