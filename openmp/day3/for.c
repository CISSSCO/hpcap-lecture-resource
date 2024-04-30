#include<stdio.h>
#include<omp.h>

int main(){
    int a = 0;
    #pragma omp parallel for 
    for(int i = 0; i < 10; i++){
        a++;
        printf("a (inside parallel region)= %d, for thread %d\n", a, omp_get_thread_num());
    }

    printf("a (outside parallel region)= %d\n", a);
    return 0;
}
