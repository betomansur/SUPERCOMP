#!/bin/bash
#SBATCH --job-name=pi_test
#SBATCH --output=output_pi.txt
#SBATCH --ntasks=1
#SBATCH --mem=1G
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

./pi_recursivo
