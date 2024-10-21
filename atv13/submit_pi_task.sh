#!/bin/bash
#SBATCH --job-name=pi_task_test
#SBATCH --output=output_pi_task.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1G
#SBATCH --time=00:10:00  # Tempo ajustado para 10 minutos
#SBATCH --partition=normal  # Partição alterada para 'normal', com limite de 20 minutos

./pi_recursivo_task
