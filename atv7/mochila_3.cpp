#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>  // Para ajustar a precisão de impressão

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

int mochila_probabilistica(int capacidade, const vector<Item>& itens, double limiar = 0.5) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    int peso_total = 0, valor_total = 0;
    for (const auto& item : itens) {
        if (dis(gen) > limiar && (peso_total + item.peso <= capacidade)) {
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
        int valor_probabilistico = mochila_probabilistica(W, itens);
        auto end = high_resolution_clock::now();
        duration<double> duracao_probabilistica = end - start;

        cout << fixed << setprecision(8);
        cout << "Heurística Probabilística - Execução " << i + 1 << ": Valor alcançado: " << valor_probabilistico
             << " dinheiros em " << duracao_probabilistica.count() << " segundos" << endl;
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
