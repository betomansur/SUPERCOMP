#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream arquivoEntrada("entrada.txt");
    std::ofstream arquivoSaida("estatisticas.txt");

    if (!arquivoEntrada.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada!" << std::endl;
        return 1;
    }

    std::string linha, palavra;
    int totalPalavras = 0;
    int totalLinhas = 0;
    std::map<std::string, int> frequenciaPalavras;

    while (std::getline(arquivoEntrada, linha)) {
        totalLinhas++;
        std::stringstream ss(linha);
        int palavrasLinha = 0;

        while (ss >> palavra) {
            totalPalavras++;
            palavrasLinha++;
            frequenciaPalavras[palavra]++;
        }
    }

    double mediaPalavrasPorLinha = static_cast<double>(totalPalavras) / totalLinhas;

    std::string palavraMaisFrequente;
    int maiorFrequencia = 0;

    for (const auto& par : frequenciaPalavras) {
        if (par.second > maiorFrequencia) {
            maiorFrequencia = par.second;
            palavraMaisFrequente = par.first;
        }
    }

    arquivoSaida << "Número total de palavras: " << totalPalavras << std::endl;
    arquivoSaida << "Número total de linhas: " << totalLinhas << std::endl;
    arquivoSaida << "Número médio de palavras por linha: " << mediaPalavrasPorLinha << std::endl;
    arquivoSaida << "Palavra mais frequente: " << palavraMaisFrequente << " (" << maiorFrequencia << " vezes)" << std::endl;

    arquivoEntrada.close();
    arquivoSaida.close();

    std::cout << "Estatísticas gravadas em 'estatisticas.txt'." << std::endl;

    return 0;
}
