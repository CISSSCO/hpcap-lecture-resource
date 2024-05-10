#include<stdio.h>
#include<omp.h>
int main()
{
    
    int arr[12] = {10, 100, 10000000, 10000, 50, 500, 2000, 1, 2, 3, 4, 5};
    omp_set_schedule(omp_sched_dynamic, 2);
#pragma omp parallel for schedule(runtime) num_threads(4)
    for (int i = 0; i < 20; i++)
	{
		printf("Thread %d is running number %d\n", omp_get_thread_num(), i);
        for(int j = 0; j < arr[j]; j++);
	}
	return 0;
}
