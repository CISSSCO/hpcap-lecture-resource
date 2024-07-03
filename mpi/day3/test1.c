#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 100000; // Size of the array
    long *array = NULL;
    int chunk_size = n / size;
    long *sub_array = (long*)malloc(chunk_size * sizeof(long));

    double start_time, end_time, total_time;
    double data_transfer_time = 0.0, computation_time = 0.0;

    if (rank == 0) {
        array = (long*)malloc(n * sizeof(long));
        for (int i = 0; i < n; i++) {
            array[i] = i + 1; // Initialize the array with values 1 to n
        }

        // Start timing the data transfer
        start_time = MPI_Wtime();

        // Distribute chunks of the array to other processes
        for (int i = 1; i < size; i++) {
            MPI_Send(array + i * chunk_size, chunk_size, MPI_LONG, i, 0, MPI_COMM_WORLD);
        }

        // Stop timing the data transfer
        end_time = MPI_Wtime();
        data_transfer_time = end_time - start_time;

        // Copy the first chunk to sub_array
        for (int i = 0; i < chunk_size; i++) {
            sub_array[i] = array[i];
        }
    } else {
        // Start timing the data transfer
        start_time = MPI_Wtime();

        // Receive chunk of the array
        MPI_Recv(sub_array, chunk_size, MPI_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Stop timing the data transfer
        end_time = MPI_Wtime();
        data_transfer_time = end_time - start_time;
    }

    // Start timing the computation
    start_time = MPI_Wtime();

    // Compute the local sum
    long local_sum = 0;
    for (int i = 0; i < chunk_size; i++) {
        local_sum += sub_array[i];
    }

    // Stop timing the computation
    end_time = MPI_Wtime();
    computation_time = end_time - start_time;

    if (rank != 0) {
        // Send local sum to process 0
        MPI_Send(&local_sum, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    } else {
        // Process 0 receives the local sums and computes the final sum
        long final_sum = local_sum;
        long temp_sum;

        // Start timing the data transfer for receiving local sums
        start_time = MPI_Wtime();

        for (int i = 1; i < size; i++) {
            MPI_Recv(&temp_sum, 1, MPI_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            final_sum += temp_sum;
        }

        // Stop timing the data transfer
        end_time = MPI_Wtime();
        data_transfer_time += end_time - start_time;

        printf("The total sum of array elements is %ld\n", final_sum);
        printf("Time taken for data transfer: %f seconds\n", data_transfer_time);
        printf("Time taken for computation on process 0: %f seconds\n", computation_time);
    }

    printf("Process %d time taken for local computation: %f seconds\n", rank, computation_time);

    free(sub_array);
    if (rank == 0) {
        free(array);
    }

    MPI_Finalize();
    return 0;
}
