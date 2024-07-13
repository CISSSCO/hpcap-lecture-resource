#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void perform_computation(MPI_Comm comm) {
    int rank;
    MPI_Comm_rank(comm, &rank);
    printf("Process %d in computation group performing computation\n", rank);
    // Simulate computation by sleeping for a while
    sleep(2);
}

void perform_data_analysis(MPI_Comm comm) {
    int rank;
    MPI_Comm_rank(comm, &rank);
    printf("Process %d in data analysis group performing data analysis\n", rank);
    // Simulate data analysis by sleeping for a while
    sleep(3);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Define two groups: one for computation and one for data analysis
    int computation_group_size = world_size / 2;
    int data_analysis_group_size = world_size - computation_group_size;

    int *computation_ranks = malloc(computation_group_size * sizeof(int));
    int *data_analysis_ranks = malloc(data_analysis_group_size * sizeof(int));

    for (int i = 0; i < computation_group_size; i++) {
        computation_ranks[i] = i;
    }
    for (int i = 0; i < data_analysis_group_size; i++) {
        data_analysis_ranks[i] = i + computation_group_size;
    }

    // Create groups
    MPI_Group world_group, computation_group, data_analysis_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    MPI_Group_incl(world_group, computation_group_size, computation_ranks, &computation_group);
    MPI_Group_incl(world_group, data_analysis_group_size, data_analysis_ranks, &data_analysis_group);

    // Create communicators from groups
    MPI_Comm computation_comm, data_analysis_comm;
    MPI_Comm_create(MPI_COMM_WORLD, computation_group, &computation_comm);
    MPI_Comm_create(MPI_COMM_WORLD, data_analysis_group, &data_analysis_comm);

    // Perform tasks based on the communicator
    if (computation_comm != MPI_COMM_NULL) {
        perform_computation(computation_comm);
        MPI_Comm_free(&computation_comm);
    }
    if (data_analysis_comm != MPI_COMM_NULL) {
        perform_data_analysis(data_analysis_comm);
        MPI_Comm_free(&data_analysis_comm);
    }

    // Free the groups
    MPI_Group_free(&computation_group);
    MPI_Group_free(&data_analysis_group);
    MPI_Group_free(&world_group);

    free(computation_ranks);
    free(data_analysis_ranks);

    MPI_Finalize();
    return 0;
}
