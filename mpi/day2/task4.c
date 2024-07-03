#include <mpi.h>
#include <stdio.h>
#define N 10000

int main(int argc, char** argv) {
    int arr[N];
    for(int i = 0; i < N; i++){
        arr[i] = i + 1;
    }
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int chunksize = N / size;
    int start = chunksize * rank;
    int end = (rank + 1) * chunksize;

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int localSum = 0;
    for(int i = start; i < end; i++){
        localSum+= arr[i];
    }
    if(rank != 0){
        MPI_Send(&localSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (rank == 0) {
        int totalSum = 0;
        totalSum += localSum;
        for(int i = 1; i < size; i++){
            MPI_Recv(&localSum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSum += localSum;
        }
        printf("Total sum = %d\n", totalSum);
    }

    MPI_Finalize();
    return 0;
}
