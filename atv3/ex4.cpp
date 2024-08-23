#include <iostream>
#include <string>

int main() {
    std::string texto;
    std::cout << "Insira uma string: ";
    std::getline(std::cin, texto);

    int comprimento = texto.length();
    std::cout << "O número de caracteres na string é: " << comprimento << std::endl;

    return 0;
}
