#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THREADS 5

int main()
{
    int N, i, maior_elemento;
    scanf("%d", &N);
    
    int *vetor = (int *)malloc(N * sizeof(int));

    //Algoritmo paralelo: Preenche todos os elementos do vetor com '1'
    #pragma omp parallel for num_threads(THREADS)
    for(i = 0; i < N; i++)
    {
        vetor[i] = 1;
    }
    vetor[N/2] = N; //Posicao intermediaria do vetor recebe o valor de N

    maior_elemento = vetor[0];

    //Codigo paralelo: procura pelo maior elemento do vetor
    #pragma omp parallel for num_threads(THREADS)
    for(i = 0; i < N; i++)
    {
        if(vetor[i] > maior_elemento)
        {
            maior_elemento = vetor[i];  //Armazena o maior elemento do vetor
        }
    }

    printf("%d", maior_elemento);   //Exibe o resultado do maior elemento encontrado

    free(vetor);

    return 0;
}