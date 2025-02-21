#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char **argv) {
    int tab[] = {1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6, 4, 5, 6, 7};
    long int a = 1, my_a = 1;
    int rank, size, chunk_size, start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide the work among processes
    int n = sizeof(tab) / sizeof(tab[0]);
    chunk_size = n / size;
    start = rank * chunk_size;
    end = (rank == size - 1) ? n : start + chunk_size;

    // Set the number of OpenMP threads
    omp_set_num_threads(2);

    // Calculate the local product using OpenMP
    #pragma omp parallel for reduction(*:my_a)
    for (int i = start; i < end; i++) {
        my_a *= tab[i];
    }

    printf("Local process %d: my_a = %ld\n", rank, my_a);

    // Reduce the local products to the root process
    MPI_Reduce(&my_a, &a, 1, MPI_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    // Print the final result on the root process
    if (rank == 0) {
        printf("Final product (a) = %ld\n", a);
    }

    MPI_Finalize();
    return 0;
}
