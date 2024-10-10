/*	O codigo possui uma regiao paralela com 2 threads
	Na diretiva single apenas uma thread executara. Ha criacao de 2 tasks e diretiva para aguardar as tasks
	Possiveis saidas:
		"A race car is fun to watch"
		"A car race is fun to watch"
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[]) 
{
	//Inicio da regiao paralela, com 2 threads
    #pragma omp parallel num_threads(2)
    {
		//Apenas uma thread executara o bloco 
		#pragma omp single
		{
			printf("A ");
			
			#pragma omp task		//Cria uma tarefa
			{printf("race ");}
			
			#pragma omp task		//Cria uma tarefa
			{printf("car ");}
			
			#pragma omp taskwait	//Aguarda finalizacao das tarefas
			printf("is fun to watch ");	    
		}

    }	//Final da regiao paralela

    printf("\n");
    return(0);

}