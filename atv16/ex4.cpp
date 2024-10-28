#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int array_size = 100;  // Tamanho do array total
    int local_size = array_size / size;
    std::vector<int> array;
    std::vector<int> local_array(local_size);

    if (rank == 0) {
        // Processo raiz inicializa o array com valores aleatórios
        array.resize(array_size);
        for (int i = 0; i < array_size; ++i) {
            array[i] = rand() % 100;  // Valores aleatórios entre 0 e 99
        }
    }

    // Distribuir o array entre os processos
    MPI_Scatter(array.data(), local_size, MPI_INT, local_array.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo calcula a média e a variância local
    double local_sum = std::accumulate(local_array.begin(), local_array.end(), 0.0);
    double local_mean = local_sum / local_size;

    double local_variance = 0.0;
    for (int val : local_array) {
        local_variance += (val - local_mean) * (val - local_mean);
    }
    local_variance /= local_size;

    // Coletar médias e variâncias locais no processo raiz
    std::vector<double> local_means(size);
    std::vector<double> local_variances(size);
    MPI_Gather(&local_mean, 1, MPI_DOUBLE, local_means.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&local_variance, 1, MPI_DOUBLE, local_variances.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Processo raiz calcula a média e o desvio padrão global
    if (rank == 0) {
        double global_mean = std::accumulate(local_means.begin(), local_means.end(), 0.0) / size;

        double global_variance = 0.0;
        for (size_t i = 0; i < size; ++i) {
            global_variance += local_variances[i];
            global_variance += local_size * (local_means[i] - global_mean) * (local_means[i] - global_mean);
        }
        global_variance /= array_size;
        double global_std_dev = std::sqrt(global_variance);

        std::cout << "Desvio padrão global: " << global_std_dev << std::endl;
    }

    MPI_Finalize();
    return 0;
}
