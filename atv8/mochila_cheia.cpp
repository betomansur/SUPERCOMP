#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

int mochila_cheia(int capacidade, vector<Item> itens) {
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

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        int valor_cheia = mochila_cheia(W, itens);
        auto end = high_resolution_clock::now();
        duration<double> duracao = end - start;

        cout << fixed << setprecision(8);
        cout << "Mochila Cheia - Execução " << i + 1 << ": Valor alcançado: " << valor_cheia
             << " dinheiros em " << duracao.count() << " segundos" << endl;
    }

    entrada.close();
}

int main() {
    vector<string> arquivos = {"entrada1.txt", "entrada2.txt", "entrada3.txt"};

    for (const string& arquivo : arquivos) {
        processar_arquivo(arquivo);
    }

    return 0;
}
