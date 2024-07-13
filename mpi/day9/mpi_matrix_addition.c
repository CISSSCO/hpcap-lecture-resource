#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int i, j, rank, size, n = 400;
    int **m1, **m2, **sumMat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunksize = n / size;
    int start = chunksize * rank;
    int end = chunksize + start;
    if (rank == size - 1) end = n;

    // Allocate memory for matrices and submatrices
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

    // Allocate memory for submatrices
    int **sub_m1 = (int**)malloc(chunksize * sizeof(int*));
    int **sub_m2 = (int**)malloc(chunksize * sizeof(int*));
    int **sub_sumMat = (int**)malloc(chunksize * sizeof(int*));
    for (i = 0; i < chunksize; i++) {
        sub_m1[i] = (int*)malloc(n * sizeof(int));
        sub_m2[i] = (int*)malloc(n * sizeof(int));
        sub_sumMat[i] = (int*)malloc(n * sizeof(int));
    }

    // Distribute the rows of the matrices to all processes
    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            int start = chunksize * proc;
            int end = (proc == size - 1) ? n : start + chunksize;
            for (i = start; i < end; i++) {
                MPI_Send(m1[i], n, MPI_INT, proc, 0, MPI_COMM_WORLD);
                MPI_Send(m2[i], n, MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        for (i = 0; i < chunksize; i++) {
            MPI_Recv(sub_m1[i], n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(sub_m2[i], n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    // Perform the addition on the submatrices
    for (i = 0; i < chunksize; i++) {
        for (j = 0; j < n; j++) {
            sub_sumMat[i][j] = sub_m1[i][j] + sub_m2[i][j];
        }
    }

    // Collect the results from all processes
    if (rank == 0) {
        for (i = 0; i < chunksize; i++) {
            for (j = 0; j < n; j++) {
                sumMat[i][j] = sub_sumMat[i][j];
            }
        }
        for (int proc = 1; proc < size; proc++) {
            int start = chunksize * proc;
            int end = (proc == size - 1) ? n : start + chunksize;
            for (i = start; i < end; i++) {
                MPI_Recv(sumMat[i], n, MPI_INT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    } else {
        for (i = 0; i < chunksize; i++) {
            MPI_Send(sub_sumMat[i], n, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    // Print the result
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

    for (i = 0; i < chunksize; i++) {
        free(sub_m1[i]);
        free(sub_m2[i]);
        free(sub_sumMat[i]);
    }
    free(sub_m1);
    free(sub_m2);
    free(sub_sumMat);

    MPI_Finalize();
    return 0;
}
