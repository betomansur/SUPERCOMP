// monte_carlo_paralelo.cpp
#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>

int main() {
    const int N = 100000; // Número total de pontos
    int inside_circle = 0; // Contador de pontos dentro do círculo

    // Gerador de números aleatórios (compartilhado entre threads)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Início da contagem de tempo
    auto start = std::chrono::high_resolution_clock::now();

    // Paralelização com OpenMP
    #pragma omp parallel for reduction(+:inside_circle)
    for (int i = 0; i < N; ++i) {
        double x, y;
        // Proteção da geração de números aleatórios (pode causar gargalo)
        #pragma omp critical
        {
            x = dis(gen);
            y = dis(gen);
        }
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    // Fim da contagem de tempo
    auto end = std::chrono::high_resolution_clock::now();

    // Estimativa de pi
    double pi_estimate = 4.0 * inside_circle / N;

    // Cálculo do tempo de execução
    std::chrono::duration<double> elapsed = end - start;

    // Resultados
    std::cout << "Estimativa de pi (paralelo): " << pi_estimate << std::endl;
    std::cout << "Tempo de execução (paralelo): " << elapsed.count() << " segundos" << std::endl;

    return 0;
}
