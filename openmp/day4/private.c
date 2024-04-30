#include<stdio.h>
#include<omp.h>
#define N  5
int main()
{
    int a = 10; //shared
    int b = 20; //shared
    int c = 20;
    omp_set_num_threads(N);
    #pragma omp parallel for private(c)
    for(int i = 0; i < N;i++){
        printf("The thred %d value is %d\n",omp_get_thread_num(),c);
        c = a + b;    //private
        printf("The thred %d value is %d\n",omp_get_thread_num(),c);
    }
        printf("(after parallel) The thred %d value is %d\n",omp_get_thread_num(),c);
    return 0;
}
