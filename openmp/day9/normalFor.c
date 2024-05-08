#include<stdio.h>
#include<omp.h>
int main()
{
#pragma omp parallel for
    for (int i = 0; i < 20; i++)
	{
		printf("Thread %d is running number %d\n", omp_get_thread_num(), i);
	}
	return 0;
}
