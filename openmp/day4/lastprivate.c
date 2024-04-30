#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	omp_set_num_threads(100);

	int val = 123456789;

	printf("Value of \"val\" before the OpenMP parallel region: %d.\n", val);

	#pragma omp parallel for lastprivate(val)
	for(int i = 0; i < omp_get_num_threads(); i++)
	{
		val = omp_get_thread_num();
	}

	printf("Value of \"val\" after the OpenMP parallel region: %d. Thread %d was therefore the last one to modify it.\n", val, val);

	return 0;
}

