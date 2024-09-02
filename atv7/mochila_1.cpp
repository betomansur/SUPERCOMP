#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>  // Para ajustar a precisão de impressão

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

int mochila_exaustiva(int &capacidade, const vector<Item> &itens, int n) {
    if (n == 0 || capacidade == 0)
        return 0;

    if (itens[n-1].peso > capacidade)
        return mochila_exaustiva(capacidade, itens, n-1);

    return max(itens[n-1].valor + mochila_exaustiva(capacidade - itens[n-1].peso, itens, n-1),
               mochila_exaustiva(capacidade, itens, n-1));
}

void processar_arquivo(const string& nome_arquivo) {
    ifstream entrada(nome_arquivo);
    if (!entrada) {
        cerr << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return;
    }

    int N, W;
    entrada >> N >> W;
    
    vector<Item> itens(N);
    for (int i = 0; i < N; i++) {
        entrada >> itens[i].peso >> itens[i].valor;
    }

    auto start = high_resolution_clock::now();
    int valor_exaustivo = mochila_exaustiva(W, itens, N);
    auto end = high_resolution_clock::now();
    duration<double> duracao_exaustiva = end - start;

    cout << fixed << setprecision(8);
    cout << "Busca Exaustiva - Arquivo: " << nome_arquivo << endl;
    cout << "Valor alcançado: " << valor_exaustivo << " dinheiros em " << duracao_exaustiva.count() << " segundos" << endl << endl;

    entrada.close();
}

int main() {
    vector<string> arquivos = {"entrada1.txt", "entrada2.txt", "entrada3.txt", "entrada4.txt"};

    for (const string& arquivo : arquivos) {
        processar_arquivo(arquivo);
    }

    return 0;
}
