#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 1000000; // Size of the array
    long *array = NULL;
    int chunk_size = n / size;
    long *sub_array = (long*)malloc(chunk_size * sizeof(long));

    double start_time, end_time;

    if (rank == 0) {
        array = (long*)malloc(n * sizeof(long));
        for (int i = 0; i < n; i++) {
            array[i] = i + 1; // Initialize the array with values 1 to n
        }

        // Start timing the computation
        start_time = MPI_Wtime();

        // Distribute chunks of the array to other processes
        for (int i = 1; i < size; i++) {
            MPI_Send(array + i * chunk_size, chunk_size, MPI_LONG, i, 0, MPI_COMM_WORLD);
        }

        // Copy the first chunk to sub_array
        for (int i = 0; i < chunk_size; i++) {
            sub_array[i] = array[i];
        }
    } else {
        // Receive chunk of the array
        MPI_Recv(sub_array, chunk_size, MPI_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Compute the local sum
    long local_sum = 0;
    for (int i = 0; i < chunk_size; i++) {
        local_sum += sub_array[i];
    }

    if (rank != 0) {
        // Send local sum to process 0
        MPI_Send(&local_sum, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    } else {
        // Process 0 receives the local sums and computes the final sum
        long final_sum = local_sum;
        long temp_sum;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&temp_sum, 1, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            final_sum += temp_sum;
        }

        // Stop timing the computation
        end_time = MPI_Wtime();
        printf("The total sum of array elements is %ld\n", final_sum);
        printf("Time taken: %f seconds\n", end_time - start_time);

        free(array);
    }

    free(sub_array);

    MPI_Finalize();
    return 0;
}
