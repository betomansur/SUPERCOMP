#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Processo 0 envia mensagens alternadas para cada processo
        for (int i = 1; i < size; i++) {
            std::string msg = "Mensagem para o processo " + std::to_string(i);
            MPI_Send(msg.c_str(), msg.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            std::cout << "Processo 0 enviou: " << msg << " para o processo " << i << std::endl;

            char response[50];
            MPI_Recv(response, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Processo 0 recebeu resposta: " << response << " do processo " << i << std::endl;
        }
    } else {
        // Cada processo (exceto o 0) recebe a mensagem e responde
        char recv_msg[50];
        MPI_Recv(recv_msg, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << recv_msg << std::endl;

        std::string response = "Resposta do processo " + std::to_string(rank);
        MPI_Send(response.c_str(), response.size() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << response << " para o processo 0" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
