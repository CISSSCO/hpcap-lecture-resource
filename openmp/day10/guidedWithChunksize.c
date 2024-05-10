#include<stdio.h>
#include<omp.h>
int main()
{
#pragma omp parallel for schedule(guided,4) num_threads(2)
    for (int i = 0; i < 35; i++)
	{
		printf("Thread %d is running number %d\n", omp_get_thread_num(), i);
    }	
	return 0;
}
