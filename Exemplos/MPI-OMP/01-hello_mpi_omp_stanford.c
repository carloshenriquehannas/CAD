/*
	to compile: mpicc 01-hello_mpi_omp_stanford.c -o 01-hello_mpi_omp_stanford -fopenmp
	para rodar: mpirun -np 2 01-hello_mpi_omp_stanford
*/

#include <stdio.h>
#include <mpi.h>
#include <omp.h>

#define NT 2  							// Define o numero de threads

int main(int argc, char *argv[]) 
{
	int numprocs, rank;
	int iam = 0, np = 1, provided;

	// Funcao para inicializar ambiente MPI com OMP
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Ambiente paralelo com OMP
	#pragma omp parallel default(shared) private(iam, np) num_threads(NT)
	{
		np = omp_get_num_threads();		// Coleta a quantidade de threads
		iam = omp_get_thread_num();		// Coleta o numero da thread
		printf("Hello from thread %d/%d, from process %d/%d\n", iam, np, rank, numprocs);
	} 
	MPI_Finalize();
	
}
