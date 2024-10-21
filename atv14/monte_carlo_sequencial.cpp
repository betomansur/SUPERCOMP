// monte_carlo_sequencial.cpp
#include <iostream>
#include <random>
#include <chrono>

int main() {
    const int N = 100000; // Número total de pontos
    int inside_circle = 0; // Contador de pontos dentro do círculo

    // Gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Início da contagem de tempo
    auto start = std::chrono::high_resolution_clock::now();

    // Loop principal
    for (int i = 0; i < N; ++i) {
        double x = dis(gen);
        double y = dis(gen);
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
    std::cout << "Estimativa de pi: " << pi_estimate << std::endl;
    std::cout << "Tempo de execução: " << elapsed.count() << " segundos" << std::endl;

    return 0;
}
