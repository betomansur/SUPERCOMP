#!/bin/bash
#SBATCH --job-name=vetor_pre_alocado_test
#SBATCH --output=output_vetor_pre_alocado.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1G
#SBATCH --time=00:05:00

./vetor_pre_alocado
