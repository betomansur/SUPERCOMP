#include <iostream>

void bubbleSort(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = 0; j < tamanho - i - 1; ++j) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int main() {
    int tamanho;

    std::cout << "Insira o tamanho do vetor: ";
    std::cin >> tamanho;

    int vetor[tamanho];

    std::cout << "Insira os números do vetor:\n";
    for (int i = 0; i < tamanho; ++i) {
        std::cin >> vetor[i];
    }

    bubbleSort(vetor, tamanho);

    std::cout << "Vetor ordenado em ordem crescente:\n";
    for (int i = 0; i < tamanho; ++i) {
        std::cout << vetor[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
