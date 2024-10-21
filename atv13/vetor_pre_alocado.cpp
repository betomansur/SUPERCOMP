#include <vector>
#include <iostream>
#include <omp.h>

double conta_complexa(int i) {
    return 2 * i; // Função simples para simular uma operação complexa
}

void run_test() {
    int N = 10000;
    std::vector<double> vec(N);  // Pré-aloca memória para o vetor com N elementos
    double start_time = omp_get_wtime(); // Medir o tempo de início

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vec[i] = conta_complexa(i); // Atribui diretamente o resultado na posição correta do vetor
    }

    double end_time = omp_get_wtime(); // Medir o tempo de término
    double exec_time = end_time - start_time;

    std::cout << "Tempo de execução: " << exec_time << " segundos\n";
}

int main() {
    // Executar o teste 3 vezes
    for (int i = 0; i < 3; i++) {
        std::cout << "Execução " << i + 1 << ":\n";
        run_test();
        std::cout << "=====================\n";
    }

    return 0;
}
