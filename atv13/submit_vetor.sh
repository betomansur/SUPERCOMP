#!/bin/bash
#SBATCH --job-name=vetor_critical_test
#SBATCH --output=output_vetor_critical.txt
#SBATCH --ntasks=1
#SBATCH --mem=1G
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

./vetor_critical
