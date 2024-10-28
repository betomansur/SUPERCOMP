#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        std::string msg = "Olá";
        MPI_Send(msg.c_str(), msg.size() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << msg << std::endl;

        char response[10];
        MPI_Recv(response, 10, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << response << std::endl;
    } else if (rank == 1) {
        char received_msg[10];
        MPI_Recv(received_msg, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: " << received_msg << std::endl;

        std::string response = "Oi";
        MPI_Send(response.c_str(), response.size() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: " << response << std::endl;
    }

    MPI_Finalize();
    return 0;
}
