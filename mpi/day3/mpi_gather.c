#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank; // Each process sends its rank
    int *recv_data = NULL;

    if (rank == 0) {
        recv_data = (int*)malloc(size * sizeof(int)); // Allocate memory for receiving data
    }

    // Gather the data from all processes to the root process
    MPI_Gather(&send_data, 1, MPI_INT, recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered data at root process: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", recv_data[i]);
        }
        printf("\n");
        free(recv_data);
    }

    MPI_Finalize();
    return 0;
}
