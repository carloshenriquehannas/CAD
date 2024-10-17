#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpi.h"

#define MESSAGE  "Hello, World from process"
#define MESSAGE_LEN 29

int main (int argc, char *argv[])
{
    int rank;       // Define o numero do processo
    int npes, myrank, src, dest, msgtag, ret;
	char *bufrecv, *bufsend;
    MPI_Status status;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bufrecv = (char *) malloc (MESSAGE_LEN);
    bufsend = (char *) malloc (MESSAGE_LEN);

    msgtag = 0;

    if(rank == 0)                  // Processo 0: recebe mensagem dos outros processos para printar
    {

        for(src = 1; src <= 3; src++)
        {
            MPI_Recv(bufrecv, MESSAGE_LEN, MPI_CHAR, src, msgtag, MPI_COMM_WORLD, &status);
            printf("Message received: %s\n", bufrecv);
        }

    }
    else if (rank == 1)            // Processo 1: envia mensagem ao processo 0
    {
        
		dest = 0;
        sprintf(bufsend, "%s %d!", MESSAGE, rank);
        MPI_Send(bufsend, MESSAGE_LEN, MPI_CHAR, dest, msgtag, MPI_COMM_WORLD);
    }
    else if (rank == 2)            // Processo 2: envia mensagem ao processo 0
    {
        
		dest = 0;
        sprintf(bufsend, "%s %d!", MESSAGE, rank);
        MPI_Send(bufsend, MESSAGE_LEN, MPI_CHAR, dest, msgtag, MPI_COMM_WORLD);
    }
    else if (rank == 3)            // Processo 3: envia mensagem ao processo 0
    {
        
		dest = 0;
        sprintf(bufsend, "%s %d!", MESSAGE, rank);
        MPI_Send(bufsend, MESSAGE_LEN, MPI_CHAR, dest, msgtag, MPI_COMM_WORLD);
    }

    free(bufrecv);
    free(bufsend);

    ret = MPI_Finalize();

    return 0;
}
