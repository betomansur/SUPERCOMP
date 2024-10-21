#include <omp.h>
#include <iostream>
#include <iomanip>

static long num_steps = 1024l*1024*1024*2;
double sum = 0;

void pi_r(long Nstart, long Nfinish, double step, int MIN_BLK) {
    long i, iblk;
    if (Nfinish - Nstart < MIN_BLK) {
        for (i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            #pragma omp atomic
            sum += 4.0 / (1.0 + x * x);
        }
    } else {
        iblk = Nfinish - Nstart;
        
        #pragma omp task shared(sum)
        pi_r(Nstart, Nfinish - iblk / 2, step, MIN_BLK);
        
        #pragma omp task shared(sum)
        pi_r(Nfinish - iblk / 2, Nfinish, step, MIN_BLK);
        
        #pragma omp taskwait
    }
}

void run_test(int MIN_BLK) {
    sum = 0; // Resetar a soma para cada execução
    double step = 1.0 / (double) num_steps;
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        pi_r(0, num_steps, step, MIN_BLK);
    }

    double pi = step * sum;
    double exec_time = omp_get_wtime() - start_time;

    std::cout << "MIN_BLK: " << MIN_BLK << ", Pi: " << std::setprecision(15) << pi 
              << ", Tempo de execução: " << exec_time << " segundos\n";
}

int main() {
    // Testando diferentes valores de MIN_BLK
    int min_blk_values[] = {1024*1024*64, 1024*1024*128, 1024*1024*256};

    for (int i = 0; i < 3; i++) {
        std::cout << "Execução " << i + 1 << ":\n";
        for (int j = 0; j < 3; j++) {
            run_test(min_blk_values[j]);
        }
        std::cout << "=====================\n";
    }

    return 0;
}
