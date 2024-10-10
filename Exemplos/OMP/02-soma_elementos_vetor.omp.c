/* Numa regiao sequencial cria-se um vetor de tamanho tam e o inicializa com numeros aleatorios entre 0 e 9
   Na regiao paralela, o ambiente define a quantidade de threads e, numa regiao critica (mas protegida), soma os elementos do vetor
   Em uma nova regiao sequencial, imprime-se o resultado da soma
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char *argv[])
{
    int tam,par,*vetor,i, seed;
    long int soma=0;
    
    double wtime;

    if ( argc  != 3)
    {
	printf("Wrong arguments. Please use main <amount_of_elements> <seed_for_rand> \n");
	exit(0);
    }

    tam = atoi(argv[1]);    //Coleta o tamanho do vetor
    seed = atoi(argv[2]);
		
    vetor=(int*)malloc(tam*sizeof(int)); //Aloca memoria para o vetor

    //Gera numeros aleatorios, entre 0 e 9, para cada posicao do vetor
    srand(seed);	
    for(i=0;i<tam;i++)
    {
        vetor[i] = rand() % 10; //Geracao dos numeros aleatorios e armazena na posicao i do vetor
        printf("%d ", vetor[i]);
    }
        
   wtime = omp_get_wtime ( );

   //Inicio da regiao paralela: programa nao define quantidade de threads (ambiente de execucao faz isso)
   #pragma omp parallel for private(i) shared(soma)
   
   //Soma os elementos do vetor
   for(i=0;i<tam;i++)
   {
       #pragma omp critical(rc_soma)    //Regiao critica: protege-se com diretiva critical
       soma += vetor[i];                //Soma os elementos do vetor
   }

   wtime = omp_get_wtime ( ) - wtime;
    
   printf("\nElapsed wall clock time = %.5f\n", wtime );
   
   printf("\n%ld\n",soma);                 //Impressao do resultado final
   free(vetor);
}
