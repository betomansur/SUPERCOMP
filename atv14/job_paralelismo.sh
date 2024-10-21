#!/bin/bash
#SBATCH --job-name=pi_paralelo
#SBATCH --output=resultado_paralelo.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1G              # Especifica 1 GB de memória
#SBATCH --time=00:05:00
#SBATCH --partition=express   # Especifica a partição

# Execução do programa
./monte_carlo_paralelismo
