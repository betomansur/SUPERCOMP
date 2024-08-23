#include <iostream>

int main() {
    int vetor[10];
    int maior;

    std::cout << "Insira 10 números:\n";
    for (int i = 0; i < 10; ++i) {
        std::cin >> vetor[i];
    }

    maior = vetor[0];
    for (int i = 1; i < 10; ++i) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }

    std::cout << "O maior número é: " << maior << std::endl;

    return 0;
}
