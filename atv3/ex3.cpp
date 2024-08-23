#include <iostream>

int main() {
    int numero;
    std::cout << "Insira um número: ";
    std::cin >> numero;

    if (numero % 2 == 0) {
        std::cout << "O número " << numero << " é par." << std::endl;
    } else {
        std::cout << "O número " << numero << " é ímpar." << std::endl;
    }

    return 0;
}
