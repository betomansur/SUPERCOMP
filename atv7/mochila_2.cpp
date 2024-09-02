#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>  // Para ajustar a precisão de impressão

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

int mochila_embaralhada(int capacidade, vector<Item> itens) {
    shuffle(itens.begin(), itens.end(), default_random_engine(random_device()()));

    int peso_total = 0, valor_total = 0;
    for (const auto& item : itens) {
        if (peso_total + item.peso <= capacidade) {
            peso_total += item.peso;
            valor_total += item.valor;
        }
    }
    return valor_total;
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

    for (int i = 0; i < 5; i++) {
        auto start = high_resolution_clock::now();
        int valor_embaralhado = mochila_embaralhada(W, itens);
        auto end = high_resolution_clock::now();
        duration<double> duracao_embaralhada = end - start;

        cout << fixed << setprecision(8);
        cout << "Heurística Embaralhada - Execução " << i + 1 << ": Valor alcançado: " << valor_embaralhado
             << " dinheiros em " << duracao_embaralhada.count() << " segundos" << endl;
    }

    entrada.close();
}

int main() {
    vector<string> arquivos = {"entrada1.txt", "entrada2.txt", "entrada3.txt", "entrada4.txt"};

    for (const string& arquivo : arquivos) {
        processar_arquivo(arquivo);
    }

    return 0;
}
