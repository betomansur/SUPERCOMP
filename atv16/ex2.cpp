#include <mpi.h>
#include <iostream>
#include <cmath>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_iterations = 1000;  // Número de iterações, definido pelo processo raiz

    // Processo 0 define a configuração e a transmite para os outros processos
    if (rank == 0) {
        num_iterations = 5000;  // Exemplo de valor configurado pelo processo raiz
    }

    MPI_Bcast(&num_iterations, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo realiza o cálculo com base no número de iterações recebido
    double local_result = 0.0;
    for (int i = 0; i < num_iterations; i++) {
        local_result += std::sin(rank + i * 0.001);  // Exemplo de cálculo
    }

    std::cout << "Processo " << rank << " concluiu com resultado local: " << local_result << std::endl;

    MPI_Finalize();
    return 0;
}
