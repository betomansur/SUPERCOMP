#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int array_size = 100;  // Tamanho total do array
    std::vector<int> array;
    int local_sum = 0;
    int local_size = array_size / size;
    std::vector<int> local_array(local_size);

    if (rank == 0) {
        array.resize(array_size);
        for (int i = 0; i < array_size; ++i) {
            array[i] = i + 1;  // Exemplo: valores de 1 a 100
        }
    }

    // Distribuição das partes do array entre os processos
    MPI_Scatter(array.data(), local_size, MPI_INT, local_array.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo calcula a média de sua parte do array
    local_sum = std::accumulate(local_array.begin(), local_array.end(), 0);
    double local_avg = static_cast<double>(local_sum) / local_size;

    // Coletar as médias locais no processo raiz
    std::vector<double> local_averages(size);
    MPI_Gather(&local_avg, 1, MPI_DOUBLE, local_averages.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Processo raiz calcula a média global
    if (rank == 0) {
        double global_avg = std::accumulate(local_averages.begin(), local_averages.end(), 0.0) / size;
        std::cout << "Média global do array: " << global_avg << std::endl;
    }

    MPI_Finalize();
    return 0;
}
