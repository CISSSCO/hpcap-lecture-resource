#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int i, j, k, rank, size, n = 400;
    int *A, *B, *C, *sub_A, *sub_C;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int rows_per_process = n / size;
    int remainder = n % size;

    // Allocate memory for matrices on the root process
    if (rank == 0) {
        A = (int*)malloc(n * n * sizeof(int));
        B = (int*)malloc(n * n * sizeof(int));
        C = (int*)malloc(n * n * sizeof(int));
        for (i = 0; i < n * n; i++) {
            A[i] = 1;
            B[i] = 1;
            C[i] = 0;
        }
    } else {
        B = (int*)malloc(n * n * sizeof(int));
    }

    // Allocate memory for submatrices
    int sub_n = rows_per_process + (rank < remainder ? 1 : 0);
    sub_A = (int*)malloc(sub_n * n * sizeof(int));
    sub_C = (int*)malloc(sub_n * n * sizeof(int));
    for (i = 0; i < sub_n * n; i++) {
        sub_C[i] = 0;
    }

    // Broadcast matrix B to all processes
    MPI_Bcast(B, n * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter the rows of matrix A to all processes
    int *sendcounts = (int*)malloc(size * sizeof(int));
    int *displs = (int*)malloc(size * sizeof(int));
    int offset = 0;
    for (i = 0; i < size; i++) {
        sendcounts[i] = (rows_per_process + (i < remainder ? 1 : 0)) * n;
        displs[i] = offset;
        offset += sendcounts[i];
    }
    MPI_Scatterv(A, sendcounts, displs, MPI_INT, sub_A, sendcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    // Perform the multiplication on the submatrices
    for (i = 0; i < sub_n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                sub_C[i * n + j] += sub_A[i * n + k] * B[k * n + j];
            }
        }
    }

    // Gather the results from all processes
    MPI_Gatherv(sub_C, sendcounts[rank], MPI_INT, C, sendcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the result on the root process
    if (rank == 0) {
        int flag = 1;
        for (i = 0; i < n * n; i++) {
            if (C[i] != n) {
                flag = 0;
                break;
            }
        }
        if (flag) printf("_____PASS_____\n");
        else printf("_____FAIL_____\n");

        // Free allocated memory
        free(A);
        free(B);
        free(C);
    } else {
        free(B);
    }

    free(sub_A);
    free(sub_C);
    free(sendcounts);
    free(displs);

    MPI_Finalize();
    return 0;
}
