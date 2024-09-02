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

// Função para a busca exaustiva
int mochila_exaustiva(int capacidade, const vector<Item>& itens, int n) {
    if (n == 0 || capacidade == 0)
        return 0;

    if (itens[n-1].peso > capacidade)
        return mochila_exaustiva(capacidade, itens, n-1);

    return max(itens[n-1].valor + mochila_exaustiva(capacidade - itens[n-1].peso, itens, n-1),
               mochila_exaustiva(capacidade, itens, n-1));
}

// Função para a heurística de embaralhar e preencher a mochila
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

// Função para a heurística de seleção aleatória baseada em probabilidade
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

    // Medição precisa de tempo para a busca exaustiva
    auto start = high_resolution_clock::now();
    int valor_exaustivo = mochila_exaustiva(W, itens, N);
    auto end = high_resolution_clock::now();
    duration<double> duracao_exaustiva = end - start;

    cout << fixed << setprecision(8);  // Ajuste de precisão para 8 casas decimais
    cout << "Busca Exaustiva - Arquivo: " << nome_arquivo << endl;
    cout << "Valor alcançado: " << valor_exaustivo << " dinheiros em " << duracao_exaustiva.count() << " segundos" << endl << endl;

    // Heurística Embaralhada
    for (int i = 0; i < 5; i++) {
        start = high_resolution_clock::now();
        int valor_embaralhado = mochila_embaralhada(W, itens);
        end = high_resolution_clock::now();
        duration<double> duracao_embaralhada = end - start;

        cout << "Heurística Embaralhada - Execução " << i + 1 << ": Valor alcançado: " << valor_embaralhado
             << " dinheiros em " << duracao_embaralhada.count() << " segundos" << endl;
    }

    // Heurística Probabilística
    for (int i = 0; i < 5; i++) {
        start = high_resolution_clock::now();
        int valor_probabilistico = mochila_probabilistica(W, itens);
        end = high_resolution_clock::now();
        duration<double> duracao_probabilistica = end - start;

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
