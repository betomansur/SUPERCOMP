#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l*1024*1024*2;
double sum = 0;

void pi_r(long Nstart, long Nfinish, double step, int MIN_BLK) {
    long i, iblk;
    if (Nfinish - Nstart < MIN_BLK) {
        #pragma omp parallel for reduction(+:sum)
        for (i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    } else {
        iblk = Nfinish - Nstart;
        pi_r(Nstart, Nfinish - iblk / 2, step, MIN_BLK);
        pi_r(Nfinish - iblk / 2, Nfinish, step, MIN_BLK);
    }
}

void run_test(int MIN_BLK) {
    sum = 0; // Resetar a soma para cada execução
    double step = 1.0 / (double) num_steps;
    double start_time = omp_get_wtime();

    pi_r(0, num_steps, step, MIN_BLK);

    double pi = step * sum;
    double exec_time = omp_get_wtime() - start_time;

    std::cout << "MIN_BLK: " << MIN_BLK << ", Pi: " << std::setprecision(15) << pi 
              << ", Tempo de execução: " << exec_time << " segundos\n";
}

int main() {
    // Testando diferentes valores de MIN_BLK
    int min_blk_values[] = {1024*1024*64, 1024*1024*128, 1024*1024*256, 1024*1024*512, 1024*1024*1024};

    for (int i = 0; i < 5; i++) {
        std::cout << "Execução " << i + 1 << ":\n";
        for (int j = 0; j < 5; j++) {
            run_test(min_blk_values[j]);
        }
        std::cout << "=====================\n";
    }

    return 0;
}
