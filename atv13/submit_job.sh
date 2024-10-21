#!/bin/bash
#SBATCH --job-name=omp_scheduler_test
#SBATCH --output=output_omp_schedulers2.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=1G
#SBATCH --time=00:05:00

./omp_schedulers