#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

#define N 10000000

int main(int argc, char** argv) {
    int rank, size, i, j, count, flag, local_count;
    double start_time, end_time, execution_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int range = N / size;
    int start = rank * range + 2;
    int end = (rank + 1) * range + 1;
    if (rank == size - 1) {
        end = N;
    }

    local_count = 0;
    if (rank == 0) {
        local_count = 1; // 2 is prime. Our loop starts from 3
    }

    start_time = MPI_Wtime();

    for (i = start; i <= end; i++) {
        flag = 0;
        for (j = 2; j <= sqrt(i); j++) {
            if ((i % j) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            local_count++;
        }
    }

    int total_count;
    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();
    execution_time = end_time - start_time;

    if (rank == 0) {
        printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", total_count, execution_time);
    }

    MPI_Finalize();
    return 0;
}
