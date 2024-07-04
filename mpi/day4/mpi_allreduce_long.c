#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long n = 100000000; // Size of the array
    long *array = NULL;
    long chunk_size = n / size;
    long *sub_array = (long*)malloc(chunk_size * sizeof(long));

    if (rank == 0) {
        array = (long*)malloc(n * sizeof(long));
        for (long i = 0; i < n; i++) {
            array[i] = i + 1; // Initialize the array with values 1 to n
        }
    }

    // Scatter the chunks of the array to all processes
    MPI_Scatter(array, chunk_size, MPI_LONG, sub_array, chunk_size, MPI_LONG, 0, MPI_COMM_WORLD);

    // Compute the local sum
    long local_sum = 0;
    for (long i = 0; i < chunk_size; i++) {
        local_sum += sub_array[i];
    }

    // Compute the total sum using allreduce
    long total_sum = 0;
    MPI_Allreduce(&local_sum, &total_sum, 1, MPI_LONG, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d: The total sum of array elements is %ld\n", rank, total_sum);

    if (rank == 0) {
        free(array);
    }
    free(sub_array);

    MPI_Finalize();
    return 0;
}
