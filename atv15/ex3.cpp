#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::string msg = "Mensagem recebida";
    char recv_msg[50];

    if (rank == 0) {
        // Processo 0 inicia a difusão
        MPI_Send(msg.c_str(), msg.size() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << msg << " para o processo 1" << std::endl;
    } else {
        // Recebe a mensagem do processo anterior
        MPI_Recv(recv_msg, 50, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << recv_msg << std::endl;

        // Envia para o próximo processo, se houver
        if (rank < size - 1) {
            MPI_Send(recv_msg, 50, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
