/*	O codigo possui uma regiao paralela com 2 threads
	Na diretiva single apenas uma thread executara o bloco
	Exibe "A" e depois coloca duas tarefas em fila
	As possiveis saidas são: "A race car" ou "A car race"
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[]) 
{
	//Inicio da regiao paralela com 2 threads
    #pragma omp parallel num_threads(2)
    {
		//Apenas uma thread executara esse bloco
		#pragma omp single
		{
			printf("A ");		//Exibe "A"
			
			#pragma omp task	//Coloca uma tarefa na fila
			{printf("race ");}
			
			#pragma omp task	//Coloca uma tarefa na fila
			{printf("car ");}
		}

    }	//Final da regiao paralela

    printf("\n");
    return(0);

}
