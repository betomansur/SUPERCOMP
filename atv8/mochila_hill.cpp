#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

struct Item {
    int peso;
    int valor;
};

// Função para calcular o valor total e o peso total de uma solução binária
pair<int, int> calcular_qualidade(const vector<int>& solucao, const vector<Item>& itens) {
    int valor_total = 0, peso_total = 0;
    for (int i = 0; i < solucao.size(); i++) {
        if (solucao[i] == 1) {
            peso_total += itens[i].peso;
            valor_total += itens[i].valor;
        }
    }
    return {valor_total, peso_total};
}

// Função de Hill Climbing para resolver o problema da mochila
int mochila_hill_climbing(int capacidade, const vector<Item>& itens) {
    int N = itens.size();
    
    // Gera uma solução inicial aleatória
    vector<int> solucao(N, 0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < N; i++) {
        solucao[i] = dis(gen);
    }

    // Calcula a qualidade inicial (valor e peso)
    auto [melhor_valor, melhor_peso] = calcular_qualidade(solucao, itens);

    // Garantir que a solução inicial seja válida
    if (melhor_peso > capacidade) {
        for (int i = 0; i < N; i++) {
            if (solucao[i] == 1 && melhor_peso > capacidade) {
                solucao[i] = 0;
                melhor_peso -= itens[i].peso;
                melhor_valor -= itens[i].valor;
            }
        }
    }

    bool melhorou = true;
    
    while (melhorou) {
        melhorou = false;
        // Gera vizinhos alterando um bit de cada vez
        for (int i = 0; i < N; i++) {
            vector<int> vizinho = solucao;
            vizinho[i] = 1 - vizinho[i];  // Inverte o bit i

            // Calcula o valor e peso do vizinho gerado
            auto [valor_vizinho, peso_vizinho] = calcular_qualidade(vizinho, itens);

            // Se o vizinho for melhor e não ultrapassar a capacidade, adotamos o vizinho
            if (peso_vizinho <= capacidade && valor_vizinho > melhor_valor) {
                solucao = vizinho;
                melhor_valor = valor_vizinho;
                melhor_peso = peso_vizinho;
                melhorou = true;
            }
        }
    }

    return melhor_valor;
}

// Função para processar o arquivo de entrada
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
        int valor_hill_climbing = mochila_hill_climbing(W, itens);
        auto end = high_resolution_clock::now();
        duration<double> duracao = end - start;

        cout << fixed << setprecision(8);
        cout << "Hill Climbing - Execução " << i + 1 << ": Valor alcançado: " << valor_hill_climbing
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
