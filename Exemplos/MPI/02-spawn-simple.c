/* to compile: mpicc 01-spawn-simple.c -o 01-spawn-simple
    to run: mpirun -np 1 01-spawn-simple
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_SPAWNS 7

int main(int argc, char *argv[])
{
  int my_rank;
  int errcodes[NUM_SPAWNS];

  MPI_Comm parentcomm, intercomm;

  MPI_Init(&argc, &argv);                     // Inicializa o OpenMPI
  MPI_Comm_get_parent(&parentcomm);           // Retorna o intercomunicador de processo MPI

  if (parentcomm == MPI_COMM_NULL)            // Processo principal
  {
    int root = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  // Retorna o numero do rank do processo pai principal

    // Criacao de novos processos filhos
    MPI_Comm_spawn("01-spawn-simple", MPI_ARGV_NULL, NUM_SPAWNS, MPI_INFO_NULL, root, MPI_COMM_WORLD, &intercomm, errcodes);
    printf("I'm the parent number %d.\n", my_rank);
    fflush(0);
  }
  else                                        // Se nao for o processo principal   
  {
    MPI_Comm_rank(parentcomm, &my_rank);      // Retorna o numero do rank do processo filho
    printf("I'm the spawned process number %d.\n", my_rank);
  }

  fflush(stdout);
  MPI_Finalize();                            // Finaliza o MPI        

  return 0;
}
