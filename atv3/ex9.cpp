#include <iostream>
#include <string>

int main() {
    std::string texto;
    bool ehPalindromo = true;

    std::cout << "Insira uma string: ";
    std::getline(std::cin, texto);

    int tamanho = texto.length();

    for (int i = 0; i < tamanho / 2; ++i) {
        if (texto[i] != texto[tamanho - i - 1]) {
            ehPalindromo = false;
            break;
        }
    }

    if (ehPalindromo) {
        std::cout << "A string \"" << texto << "\" é um palíndromo." << std::endl;
    } else {
        std::cout << "A string \"" << texto << "\" não é um palíndromo." << std::endl;
    }

    return 0;
}
