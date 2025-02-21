#include <mpi.h>
#include <iostream>
#include <algorithm>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 10;               // Length of the chain
    int chain[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // The chain of numbers
    int local_chunk[n / 2];         // Buffer to hold the part of the chain for each thread
    int local_max;                  // Local maximum

    if (rank == 0) {
        // Scatter the chain into two parts: First half to thread 1, second half to thread 2
        MPI_Scatter(chain, n / 2, MPI_INT, local_chunk, n / 2, MPI_INT, 0, MPI_COMM_WORLD);
        // Compute maximum of the first half (rank 0's data)
        local_max = *std::max_element(chain, chain + n / 2);
    } else {
        // Receive part of the chain (second half)
        MPI_Scatter(nullptr, n / 2, MPI_INT, local_chunk, n / 2, MPI_INT, 0, MPI_COMM_WORLD);
        // Compute maximum of this part
        local_max = *std::max_element(local_chunk, local_chunk + n / 2);
    }

    int global_max;
    if (rank != 0) {
        // Threads 1 and 2 send their local maximum to thread 0
        MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    } else {
        // Thread 0 receives and calculates the global maximum
        MPI_Reduce(MPI_IN_PLACE, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        // Thread 0 prints the global maximum
        std::cout << "The maximum value in the chain is: " << global_max << std::endl;
    }

    MPI_Finalize();
    return 0;
}
