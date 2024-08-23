#include <iostream>

int main() {
    int matriz[3][3];
    int somaDiagonal = 0;

    std::cout << "Insira os elementos da matriz 3x3:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << "Elemento [" << i << "][" << j << "]: ";
            std::cin >> matriz[i][j];
        }
    }

    for (int i = 0; i < 3; ++i) {
        somaDiagonal += matriz[i][i];
    }

    std::cout << "A soma dos elementos na diagonal principal é: " << somaDiagonal << std::endl;

    return 0;
}
