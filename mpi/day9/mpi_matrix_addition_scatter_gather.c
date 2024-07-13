#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int i, j, rank, size, n = 400;
    int **m1, **m2, **sumMat;
    int *sub_m1, *sub_m2, *sub_sumMat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunksize = n / size;

    // Allocate memory for the full matrices on the root process
    if (rank == 0) {
        m1 = (int**)malloc(n * sizeof(int*));
        m2 = (int**)malloc(n * sizeof(int*));
        sumMat = (int**)malloc(n * sizeof(int*));
        for (i = 0; i < n; i++) {
            m1[i] = (int*)malloc(n * sizeof(int));
            m2[i] = (int*)malloc(n * sizeof(int));
            sumMat[i] = (int*)malloc(n * sizeof(int));
            for (j = 0; j < n; j++) {
                m1[i][j] = 1;
                m2[i][j] = 1;
            }
        }
    }

    // Allocate memory for the submatrices on each process
    sub_m1 = (int*)malloc(chunksize * n * sizeof(int));
    sub_m2 = (int*)malloc(chunksize * n * sizeof(int));
    sub_sumMat = (int*)malloc(chunksize * n * sizeof(int));

    // Scatter the rows of the matrices to all processes
    if (rank == 0) {
        for (i = 0; i < size; i++) {
            MPI_Scatter(m1[i], chunksize * n, MPI_INT, sub_m1, chunksize * n, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Scatter(m2[i], chunksize * n, MPI_INT, sub_m2, chunksize * n, MPI_INT, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Scatter(NULL, chunksize * n, MPI_INT, sub_m1, chunksize * n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Scatter(NULL, chunksize * n, MPI_INT, sub_m2, chunksize * n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Perform the addition on the submatrices
    for (i = 0; i < chunksize * n; i++) {
        sub_sumMat[i] = sub_m1[i] + sub_m2[i];
    }

    // Gather the results from all processes
    if (rank == 0) {
        for (i = 0; i < size; i++) {
            MPI_Gather(sub_sumMat, chunksize * n, MPI_INT, sumMat[i], chunksize * n, MPI_INT, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Gather(sub_sumMat, chunksize * n, MPI_INT, NULL, chunksize * n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Print the result on the root process
    if (rank == 0) {
        int flag = 1;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (sumMat[i][j] != 2) {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag) printf("_____PASS_____\n");
        else printf("_____FAIL_____\n");

        // Free the allocated memory
        for (i = 0; i < n; i++) {
            free(m1[i]);
            free(m2[i]);
            free(sumMat[i]);
        }
        free(m1);
        free(m2);
        free(sumMat);
    }

    free(sub_m1);
    free(sub_m2);
    free(sub_sumMat);

    MPI_Finalize();
    return 0;
}
