#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int *send_data = (int*)malloc(size * sizeof(int));
    int *recv_data = (int*)malloc(size * sizeof(int));
    // Initialize send_data such that process i sends its rank to all processes
    for (int i = 0; i < size; i++) {
        send_data[i] = rank + i * 10;
    }
    // Perform all-to-all communication
    MPI_Alltoall(send_data, 1, MPI_INT, recv_data, 1, MPI_INT, MPI_COMM_WORLD);
    printf("Process %d received data: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recv_data[i]);
    }
    printf("\n");
    free(send_data);
    free(recv_data);
    MPI_Finalize();
    return 0;
}
