#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

#define N 999999999

int main(int argc, char** argv) {
    int rank, size, i;
    double dx, x, y, local_area, total_area;
    double start_time, end_time, execution_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dx = 1.0 / N;
    local_area = 0.0;

    start_time = MPI_Wtime();

    for (i = rank; i < N; i += size) {
        x = i * dx;
        y = sqrt(1 - x * x);
        local_area += y * dx;
    }

    MPI_Reduce(&local_area, &total_area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();
    execution_time = end_time - start_time;

    if (rank == 0) {
        double pi = 4.0 * total_area;
        printf("\nValue of pi is = %.16lf\nExecution time is = %lf seconds\n", pi, execution_time);
    }

    MPI_Finalize();
    return 0;
}
