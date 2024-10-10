/*	O codigo possui uma regiao paralela com 2 threads
	Na diretiva single apenas uma thread executara. Nela ha duas tasks
	Possiveis saidas: 
		"A is fun to watch race car", 
		"A is fun to watch car race", 
		"A race car is fun to watch"
		"A car race is fun to watch"
		"A race is fun to watch car"
		"A car is fun to watch race"
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
			
			#pragma omp task	//Cria uma tarefa e a coloca em fila
			{printf("race ");}
			
			#pragma omp task	//Cria uma tarefa e a coloca em fila
			{printf("car ");}
			
			printf("is fun to watch ");	    
		}

    }	//Final da regiao paralela

    printf("\n");
    return(0);

}
