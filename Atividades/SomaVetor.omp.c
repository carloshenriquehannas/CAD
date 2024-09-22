#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

#define THREADS 5

int main()
{
    int N, seed, soma, i;
    soma = 0;

    scanf("%d %d", &N, &seed);
    srand(seed);

    int vetor[N];

    //Gera valores aleatorios entre 0 e 9 para cada posicao do vetor
    for(i = 0; i < N; i++)
    {
        vetor[i] = rand() % 10;
    }

    //Codigo paralelo: soma dos elementos do vetor
    #pragma omp parallel for num_threads(THREADS) private(i) reduction(+:soma)
    for (i = 0; i < N; i++)
    {
        soma += vetor[i];
    }
       
    //Exibe a soma dos elementos do vetor
    printf("%d", soma);

    return 0;
}