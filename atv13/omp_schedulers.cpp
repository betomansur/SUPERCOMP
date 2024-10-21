#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <omp.h>

void print_iterations(const std::string& description, const std::vector<std::vector<int>>& vectors, const int n) {
    std::vector<std::string> strings(4, std::string());
    for (int i = 0; i != n; i++) {
        for (int j = 0; j != 4; j++) {
            const auto& vector = vectors[j];
            auto it = std::find(vector.begin(), vector.end(), i);
            if (it != vector.end()) {
                strings[j] += "*";
            } else {
                strings[j] += " ";
            }
        }
    }
    std::cout << description << std::endl;
    for (auto& s : strings) {
        std::cout << s << "\n";
    }
    std::cout << std::endl;
}

template <typename T>
void schedule(T function, const std::string& description, const int n) {
    std::vector<std::vector<int>> vectors(4, std::vector<int>());
    double start_time = omp_get_wtime();  // Medir o tempo de início
    function(vectors, n);
    double end_time = omp_get_wtime();  // Medir o tempo de término
    print_iterations(description, vectors, n);
    std::cout << "Tempo de execução para " << description << ": " << (end_time - start_time) << " segundos\n";
}

void scheduleStatic(std::vector<std::vector<int>>& vectors, int n) {
    #pragma omp parallel num_threads(4), shared(vectors, n)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < n; i++) {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}

void scheduleDynamic(std::vector<std::vector<int>>& vectors, int n) {
    #pragma omp parallel num_threads(4), shared(vectors, n)
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < n; i++) {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}

void scheduleGuided(std::vector<std::vector<int>>& vectors, int n) {
    #pragma omp parallel num_threads(4), shared(vectors, n)
    {
        #pragma omp for schedule(guided)
        for (int i = 0; i < n; i++) {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}

void scheduleAuto(std::vector<std::vector<int>>& vectors, int n) {
    #pragma omp parallel num_threads(4), shared(vectors, n)
    {
        #pragma omp for schedule(auto)
        for (int i = 0; i < n; i++) {
            vectors[omp_get_thread_num()].push_back(i);
        }
    }
}

int main() {
    const int n = 64;

    // Executar o teste para cada scheduler 3 vezes
    for (int i = 1; i <= 3; i++) {
        std::cout << "Teste " << i << " com schedule(static)" << std::endl;
        schedule(scheduleStatic,  "schedule(static):      ", n);
        std::cout << "====================" << std::endl;
    }

    for (int i = 1; i <= 3; i++) {
        std::cout << "Teste " << i << " com schedule(dynamic)" << std::endl;
        schedule(scheduleDynamic, "schedule(dynamic):     ", n);
        std::cout << "====================" << std::endl;
    }

    for (int i = 1; i <= 3; i++) {
        std::cout << "Teste " << i << " com schedule(guided)" << std::endl;
        schedule(scheduleGuided,  "schedule(guided):      ", n);
        std::cout << "====================" << std::endl;
    }

    for (int i = 1; i <= 3; i++) {
        std::cout << "Teste " << i << " com schedule(auto)" << std::endl;
        schedule(scheduleAuto,    "schedule(auto):        ", n);
        std::cout << "====================" << std::endl;
    }

    return 0;
}
