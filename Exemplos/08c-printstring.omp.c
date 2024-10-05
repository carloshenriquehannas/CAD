/*  O codigo possui uma regiao paralela com 2 threads
    Na diretiva single, apenas uma thread executara. Ha duas tarefas (tasks) em fila
    A impressao pode ser: "race car" ou "car race", dependendo de qual task for executada antes
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[]) 
{
    //Inicio da regiao paralela, com 2 threads
    #pragma omp parallel num_threads(2)
    {
        //Apenas uma thread executara esse bloco de codigo
        #pragma omp single
        {
            #pragma omp task    //Coloca uma tarefa na fila
            {printf("race ");}
	    
            #pragma omp task    //Coloca uma tarefa na fila
            {printf("car ");}
        }
    
    }   //Final da regiao paralela

    printf("\n");
    return(0);
}
