#!/bin/bash
#SBATCH --job-name=mochila             # Nome do job
#SBATCH --output=mochila_1_%j.txt          # Nome do arquivo de saída
#SBATCH --ntasks=4                              # Número de tarefas (4 processos)
#SBATCH --cpus-per-task=4                       # Número de threads por tarefa (2 threads por processo)
#SBATCH --mem=4096                               # Memória total alocada por nó (1024 MB = 1 GB)
#SBATCH --time=03:00:00                         # Tempo máximo de execução (10 minutos)
#SBATCH --partition=espec                      # fila do cluster a ser utilizada

# Exporta a variável de ambiente para configurar o número de threads OpenMP
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK


# Executa o programa usando MPI e OpenMP
./mochila_exaustiva


