#!/bin/bash
#SBATCH --job-name=mpi_exercicio1           # Nome do job
#SBATCH --output=mpi_exercicio1.out         # Arquivo de saída
#SBATCH --ntasks=2                          # Número total de processos MPI
#SBATCH --cpus-per-task=1                   # Número de CPUs por tarefa (1 por processo MPI)
#SBATCH --mem=1G                            # Especifica 1 GB de memória
#SBATCH --time=00:05:00                     # Tempo máximo de execução
#SBATCH --partition=express                 # Partição especificada

# Execução do programa MPI
mpiexec -n 2 ./ex1                   # Executa o programa com dois processos
