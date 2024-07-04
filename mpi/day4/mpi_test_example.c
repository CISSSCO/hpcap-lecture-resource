#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number;
    MPI_Request request;
    MPI_Status status;
    int flag = 0;

    if (rank == 0) {
        number = 100;
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        while (!flag) {
            MPI_Test(&request, &flag, &status);
        }
        printf("Process 0: Send complete\n");
    } else if (rank == 1) {
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        while (!flag) {
            MPI_Test(&request, &flag, &status);
        }
        if (flag) {
            printf("Process 1 received number %d\n", number);
        } else {
            printf("Process 1: Receive incomplete\n");
        }
    }

    MPI_Finalize();
    return 0;
}
