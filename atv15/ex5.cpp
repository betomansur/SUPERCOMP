#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int value = rank + 1;  // Valor exclusivo de cada processo (aqui configurado como o rank + 1 para simplicidade)
    int total_sum = 0;

    if (rank == 0) {
        // Processo 0 inicia a soma com seu valor e envia ao processo 1
        total_sum = value;
        MPI_Send(&total_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " iniciou com valor: " << value << std::endl;
    } else {
        // Cada processo recebe a soma acumulada do processo anterior
        MPI_Recv(&total_sum, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum += value;
        std::cout << "Processo " << rank << " recebeu soma parcial e adicionou seu valor (" << value << "): Total até agora = " << total_sum << std::endl;

        // Envia a soma acumulada para o próximo processo, se houver
        if (rank < size - 1) {
            MPI_Send(&total_sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            // Último processo exibe a soma total
            std::cout << "Processo " << rank << " finalizou a soma total: " << total_sum << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
