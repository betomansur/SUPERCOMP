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

int mochila_substituicao(int capacidade, vector<Item> itens) {
    vector<bool> usado(itens.size(), false);
    int peso_total = 0, valor_total = 0;

    for (int i = 0; i < itens.size(); i++) {
        if (peso_total + itens[i].peso <= capacidade) {
            peso_total += itens[i].peso;
            valor_total += itens[i].valor;
            usado[i] = true;
        }
    }

    bool melhorou = true;
    while (melhorou) {
        melhorou = false;
        for (int i = 0; i < itens.size(); i++) {
            if (usado[i]) {
                for (int j = 0; j < itens.size(); j++) {
                    if (!usado[j] && peso_total - itens[i].peso + itens[j].peso <= capacidade) {
                        int novo_valor = valor_total - itens[i].valor + itens[j].valor;
                        if (novo_valor > valor_total) {
                            valor_total = novo_valor;
                            peso_total = peso_total - itens[i].peso + itens[j].peso;
                            usado[i] = false;
                            usado[j] = true;
                            melhorou = true;
                        }
                    }
                }
            }
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
        int valor_substituicao = mochila_substituicao(W, itens);
        auto end = high_resolution_clock::now();
        duration<double> duracao = end - start;

        cout << fixed << setprecision(8);
        cout << "Substituição de Objeto - Execução " << i + 1 << ": Valor alcançado: " << valor_substituicao
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
