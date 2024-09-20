/// SSC0903 - COMPUTAÇÃO DE ALTO DESEMPENHO - 2024/2 - Turma B
///
/// TRABALHO PRÁTICO 1
///
/// Integrantes do grupo:
///
/// Carlos Henrique Hannas de Carvalho      NUSP: 11965988
/// Carlos Nery Ribeiro                     NUSP: 12547698
/// Gabriel Ribeiro Rodrigues Dessotti      NUSP: 12547228
/// Lucas Carvalho Freiberger Stapf         NUSP: 11800559
/// Pedro Manicardi Soares                  NUSP: 12547621
///
/// Para compilar: gcc filter_conv.omp.c -o filter_conv -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/// Define a quantidade de threads a serem criadas pelo OMP.
#define NUM_THREADS 4

/// Calcula o índice linear equivalente de uma matriz bidimensional armazenada 
/// em um array unidimensional, como se fosse uma matriz armazenada de forma contínua em memória.
/// Parâmetros:
/// (i, j): índices da linha e da coluna da matriz.
/// c: número de colunas da matriz.
#define INDEX(i, j, c) ((i * c) + j)

#define I(n, c) (n / c)
#define J(n, c) (n % c)

int main(int argc, char const *argv[])
{
    
    if (argc != 4)
    {
        printf("Numero invalido de argumentos\n");
        return 1;
    }

    int N = atoi(argv[1]), M = atoi(argv[2]), S = atoi(argv[3]);
    srand(S);

    // Criação da imagem original
    unsigned char *img = malloc(N * N * sizeof(unsigned char));
    
    for (int n = 0; n < N * N; n++)
        img[n] = rand() % 256;
    
    // TESTE - REMOVER DPS
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", img[INDEX(i, j, N)]);
        printf("\n");
    }
    printf("\n");
    // FIM DO TESTE - REMOVER DPS
    
    // Criação do filtro
    float *filter = malloc(M * M * sizeof(float));
    
    for (int m = 0; m < M * M; m++)
    {
        float v = ((float) rand()) / (RAND_MAX);
        filter[m] = ((int) (v * 10)) / 10.0;
    }

    // TESTE - REMOVER DPS
    printf("\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%f ", filter[INDEX(i, j, M)]);
        printf("\n");
    }
    printf("\n");
    // FIM DO TESTE - REMOVER DPS


    // Criação da nova imagem (depois de aplicar o filtro)
    unsigned char *new_img = malloc(N * N * sizeof(unsigned char));

    // #pragma omp parallel for
    // for (int n = 0; n < N * N; n++)
    // {

    // }

    return 0;
}
