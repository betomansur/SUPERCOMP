#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>  // Inclui a biblioteca para medição de tempo.
#include <iomanip> // Para ajustar a precisão de impressão.

using namespace std;
using namespace std::chrono;

// Função para calcular o valor máximo que pode ser carregado na mochila.
int mochila(int capacidade, const vector<int>& pesos, const vector<int>& valores, int n) {
    if (n == 0 || capacidade == 0)
        return 0;

    if (pesos[n-1] > capacidade)
        return mochila(capacidade, pesos, valores, n-1);

    return max(valores[n-1] + mochila(capacidade - pesos[n-1], pesos, valores, n-1),
               mochila(capacidade, pesos, valores, n-1));
}

// Função para processar cada arquivo de entrada.
void processar_arquivo(const string& nome_arquivo) {
    ifstream entrada(nome_arquivo);
    if (!entrada) {
        cerr << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return;
    }

    int N, W;
    entrada >> N >> W;
    
    vector<int> pesos(N);
    vector<int> valores(N);

    for (int i = 0; i < N; i++) {
        entrada >> pesos[i] >> valores[i];
    }

    auto start = high_resolution_clock::now();  // Inicia a medição de tempo.

    int valor_maximo = mochila(W, pesos, valores, N);

    auto end = high_resolution_clock::now();  // Finaliza a medição de tempo.
    duration<double> duracao = end - start;  // Calcula a duração em segundos com precisão dupla.

    cout << fixed << setprecision(8);  // Define a precisão de impressão para 8 casas decimais.
    cout << "Arquivo: " << nome_arquivo << endl;
    cout << "Peso ocupado: " << W << " Kg, Valor alcançado: " << valor_maximo << " dinheiros" << endl;
    cout << "Tempo de execução: " << duracao.count() << " segundos" << endl << endl;

    entrada.close();
}

int main() {
    vector<string> arquivos = {"entrada1.txt", "entrada2.txt", "entrada3.txt", "entrada4.txt"};

    for (const string& arquivo : arquivos) {
        processar_arquivo(arquivo);
    }

    return 0;
}
