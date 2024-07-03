#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int i, myid, size;
    int *sendBuf, recvBuf;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (myid == 0) {
        sendBuf = (int*)malloc(size * sizeof(int));
        for (i = 0; i < size; i++) {
            sendBuf[i] = 100 + i * 5 + i; // Initialize the send buffer with some values
        }
    }
    // Scatter the data from root process to all processes
    MPI_Scatter(sendBuf, 1, MPI_INT, &recvBuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (myid == 0) printf("Message broadcasted are: \n");
    printf("Process %d has %d\n", myid, recvBuf);

    if (myid == 0) free(sendBuf);

    MPI_Finalize();
    return 0;
}
