#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    long n = 1000000; // Size of the array
    long *array = NULL;
    long chunk_size = n / world_size;
    long *sub_array = (long*)malloc(chunk_size * sizeof(long));

    if (world_rank == 0) {
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

    // Gather all local sums to the root process
    long final_sum = 0;
    MPI_Reduce(&local_sum, &final_sum, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("The total sum of array elements is %ld\n", final_sum);
        free(array);
    }

    free(sub_array);

    MPI_Finalize();
    return 0;
}
