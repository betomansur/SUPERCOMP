#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int array_size = 100;
    std::vector<int> array;
    int local_size = array_size / size;
    std::vector<int> local_array(local_size);
    int max_value = 0;

    if (rank == 0) {
        // Processo raiz cria o array e encontra o valor máximo
        array.resize(array_size);
        for (int i = 0; i < array_size; ++i) {
            array[i] = rand() % 100;  // Valores aleatórios entre 0 e 99
        }
        max_value = *std::max_element(array.begin(), array.end());
        std::cout << "Valor máximo encontrado pelo processo raiz: " << max_value << std::endl;
    }

    // Enviar o valor máximo para todos os processos
    MPI_Bcast(&max_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Dividir o array entre os processos
    MPI_Scatter(array.data(), local_size, MPI_INT, local_array.data(), local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Normalizar a parte local do array
    std::vector<double> normalized_local_array(local_size);
    for (int i = 0; i < local_size; ++i) {
        normalized_local_array[i] = static_cast<double>(local_array[i]) / max_value;
    }

    // Coletar os arrays normalizados no processo raiz
    std::vector<double> normalized_array(array_size);
    MPI_Gather(normalized_local_array.data(), local_size, MPI_DOUBLE, normalized_array.data(), local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Array normalizado: ";
        for (const auto& val : normalized_array) {
            std::cout << std::fixed << std::setprecision(2) << val << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
