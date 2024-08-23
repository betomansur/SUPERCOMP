#include <iostream>



int main() {
    double num1, num2;
    char operation;
    
    std::cout << "Insira o primeiro número: ";
    std::cin >> num1;
    
    std::cout << "Insira o segundo número: ";
    std::cin >> num2;

    std::cout << "Insira a operação (+, -, *, /): ";
    std::cin >> operation;

    switch (operation) {
        case '+':
            std::cout << "Resultado: " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << "Resultado: " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << "Resultado: " << num1 * num2 << std::endl;
            break;
        case '/':
            if (num2 != 0) {
                std::cout << "Resultado: " << num1 / num2 << std::endl;
            } else {
                std::cout << "Erro: Divisão por zero não é permitida." << std::endl;
            }
            break;
        default:
            std::cout << "Operação inválida!" << std::endl;
            break;
    }

    return 0;
}
