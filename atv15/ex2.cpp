#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::string msg = "Mensagem do processo " + std::to_string(rank);
    char recv_msg[50];

    // Envia a mensagem para o próximo processo no anel
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    // Processo 0 inicia o anel enviando sua mensagem
    if (rank == 0) {
        MPI_Send(msg.c_str(), msg.size() + 1, MPI_CHAR, next, 0, MPI_COMM_WORLD);
        MPI_Recv(recv_msg, 50, MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << recv_msg << std::endl;
    } else {
        MPI_Recv(recv_msg, 50, MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << recv_msg << std::endl;
        MPI_Send(msg.c_str(), msg.size() + 1, MPI_CHAR, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
