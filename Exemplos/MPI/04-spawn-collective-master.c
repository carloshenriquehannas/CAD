// compilar: mpicc 03-spawn-collective-master.c -o 03-spawn-collective-master
// executar: mpirun 03-spawn-collective-master -np 1 03-spawn-collective-master

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

#define NUM_SPAWNS 4

int main(int argc, char **argv)
{
  int tag = 1, my_rank, num_proc, src, dst, root;
  char msg_0[] = "hello worker, i'm your master";
  char msg_1[50], master_data[] = "workers to work", worker[40];
  int errcodes[10], i, vet[NUM_SPAWNS], buf_rcv, vet_master[NUM_SPAWNS];

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;

  MPI_Status status;
  MPI_Comm inter_comm;
  MPI_Request mpirequest_mr;

  strcpy(worker, "03-spawn-collective-worker");

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

  MPI_Get_processor_name(processor_name, &name_len);

  for (i = 0; i < NUM_SPAWNS; i++)
    vet[i] = i;

  src = dst = root = 0;
  MPI_Comm_spawn(worker, MPI_ARGV_NULL, NUM_SPAWNS, MPI_INFO_NULL, root, MPI_COMM_WORLD, &inter_comm, errcodes);

  MPI_Send(msg_0, 50, MPI_CHAR, dst, tag, inter_comm);
  MPI_Irecv(msg_1, 50, MPI_CHAR, src, tag, inter_comm, &mpirequest_mr);

  MPI_Send(master_data, 50, MPI_CHAR, dst, tag, inter_comm);

  MPI_Scatter(vet, 1, MPI_INT, &buf_rcv, 1, MPI_INT, MPI_ROOT, inter_comm);
  MPI_Gather(vet, 1, MPI_INT, &vet_master, 1, MPI_INT, MPI_ROOT, inter_comm);

  MPI_Wait(&mpirequest_mr, &status);

  for (i = 0; i < NUM_SPAWNS; i++)
    printf("Master (%s): msg_1=%s,vet[%d]=%d,buf_rcv=%d,vet_master[%d]=%d\n", processor_name, msg_1, i, vet[i], buf_rcv, i, vet_master[i]);

  MPI_Finalize();
  exit(0);
}
