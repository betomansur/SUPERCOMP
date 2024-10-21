#!/bin/bash
#SBATCH --job-name=pi_sequencial
#SBATCH --output=resultado_sequencial.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=1G              # Especifica 1 GB de memória
#SBATCH --time=00:05:00
#SBATCH --partition=express   # Especifica a partição (opcional)

# Execução do programa
./monte_carlo_sequencial
