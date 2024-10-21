// monte_carlo_paralelo_melhorado.cpp
#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

int main() {
    const int N = 100000; // Número total de pontos
    int inside_circle = 0; // Contador de pontos dentro do círculo

    // Início da contagem de tempo
    auto start = std::chrono::high_resolution_clock::now();

    // Paralelização com OpenMP
    #pragma omp parallel
    {
        // Cada thread tem seu próprio gerador de números aleatórios
        std::random_device rd;
        int thread_id = omp_get_thread_num();
        std::mt19937 gen(rd() + thread_id);
        std::uniform_real_distribution<> dis(0.0, 1.0);

        int local_count = 0; // Contador local para cada thread

        #pragma omp for
        for (int i = 0; i < N; ++i) {
            double x = dis(gen);
            double y = dis(gen);
            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }

        // Soma local_count de cada thread em inside_circle de forma atômica
        #pragma omp atomic
        inside_circle += local_count;
    }

    // Fim da contagem de tempo
    auto end = std::chrono::high_resolution_clock::now();

    // Estimativa de pi
    double pi_estimate = 4.0 * inside_circle / N;

    // Cálculo do tempo de execução
    std::chrono::duration<double> elapsed = end - start;

    // Resultados
    std::cout << "Estimativa de pi (paralelo melhorado): " << pi_estimate << std::endl;
    std::cout << "Tempo de execução (paralelo melhorado): " << elapsed.count() << " segundos" << std::endl;

    return 0;
}
