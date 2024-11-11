/*
!! a simple Master/worker (dynamically spawnd) example with
!!  MPI_Comm_spawn, MPI_Comm_get_parent
!!  both Master and worker executables must be build, see worker
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define NUM_SPAWNS 4

int main(int argc, char **argv)
{
	int dst = 0, tag = 0, my_rank, num_proc;
	int array_of_errcodes[10];
	char message_0[] = "hello worker, i'm your master";
	char master_data[] = "workers to work";
	char message_1[50];
	char worker[25];

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;

	MPI_Status status;
	MPI_Comm inter_comm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	MPI_Get_processor_name(processor_name, &name_len);

	printf("MASTER (%s) : spawning %d workers ... \n", processor_name, NUM_SPAWNS);

	/* spawn worker and send it a message */
	strcpy(worker, "02-spawn-worker");
	MPI_Comm_spawn(worker, MPI_ARGV_NULL, NUM_SPAWNS, MPI_INFO_NULL, dst, MPI_COMM_WORLD, &inter_comm, array_of_errcodes);

	printf("MASTER(%s) : send a message to master of workers (%s) ...\n", processor_name, message_0);
	MPI_Send(message_0, 50, MPI_CHAR, dst, tag, inter_comm);

	MPI_Recv(message_1, 50, MPI_CHAR, dst, tag, inter_comm, &status);
	printf("MASTER (%s) : message received : %s\n", processor_name, message_1);

	MPI_Send(master_data, 50, MPI_CHAR, dst, tag, inter_comm);

	MPI_Finalize();
	exit(0);
}
