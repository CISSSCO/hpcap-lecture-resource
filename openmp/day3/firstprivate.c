#include<stdio.h>
#include<omp.h>

int main(){
    int a = 10;
    #pragma omp parallel for firstprivate(a)
    for(int i = 0; i < 10; i++){
        a++;
        printf("a value for thread %d is %d\n", omp_get_thread_num(), a);
    }

    printf("a (outside parallel region) = %d\n", a);
    return 0;
}
