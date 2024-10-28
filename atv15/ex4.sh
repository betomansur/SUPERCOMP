#!/bin/bash
#SBATCH --job-name=mpi_ex4                  # Nome do job
#SBATCH --output=mpi_ex4.out                # Arquivo de saída
#SBATCH --ntasks=4                          # Número total de processos MPI (ajuste conforme o exercício)
#SBATCH --cpus-per-task=1                   # Número de CPUs por tarefa (1 por processo MPI)
#SBATCH --mem=1G                            # Especifica 1 GB de memória
#SBATCH --time=00:05:00                     # Tempo máximo de execução
#SBATCH --partition=express                 # Partição especificada

# Execução do programa MPI
mpiexec -n 4 ./ex4                          # Executa o programa com 4 processos
