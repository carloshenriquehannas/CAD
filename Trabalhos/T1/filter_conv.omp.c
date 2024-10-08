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
#include <math.h>
#include <omp.h>
#include <time.h>

/// Define a quantidade de threads a serem criadas pelo OMP.
#define NUM_THREADS 4

/// Calcula o índice linear equivalente de uma matriz bidimensional armazenada 
/// em um array unidimensional, como se fosse uma matriz armazenada de forma contínua em memória.
/// Parâmetros:
/// (i, j): índices da linha e da coluna da matriz.
/// c: número de colunas da matriz.
#define INDEX(i, j, c) ((i * c) + j)

/// Calcula a linha i de uma matriz que está representada na forma de um vetor com base no índice n.
#define I(n, c) (n / c)

/// Calcula a coluna j de uma matriz que está representada na forma de um vetor com base no índice n.
#define J(n, c) (n % c)

int main(int argc, char const *argv[])
{
    // Remover depois
    clock_t time;
    
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
    // printf("NxN:\n");
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //         printf("%d ", img[INDEX(i, j, N)]);
    //     printf("\n");
    // }
    // printf("\n");
    // FIM DO TESTE - REMOVER DPS
    
    // Criação do filtro
    float *filter = malloc(M * M * sizeof(float));
    
    for (int m = 0; m < M * M; m++)
        filter[m] = (rand() % 10) / 10.0;

    // TESTE - REMOVER DPS
    // printf("MxM\n");
    // for (int i = 0; i < M; i++)
    // {
    //     for (int j = 0; j < M; j++)
    //         printf("%0.1f ", filter[INDEX(i, j, M)]);
    //     printf("\n");
    // }
    // printf("\n");
    // FIM DO TESTE - REMOVER DPS

    // Criação da imagem nova (Só para testes)
    unsigned char *new_img = malloc(N * N * sizeof(unsigned char));

    time = clock();
    unsigned char maior = 0, menor = 255;
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(max: maior) reduction(min: menor)
    for (int n = 0; n < N * N; n++)
    {
        float sum_prod = 0;
        int i_start = I(n, N) - ((M - 1) / 2);
        int i_end = I(n, N) + ((M - 1) / 2);
        int j_start = J(n, N) - ((M - 1) / 2);
        int j_end = J(n, N) + ((M - 1) / 2);
        for (int i_img = i_start, i_fil = 0; i_img <= i_end; i_img++, i_fil++)
        {
            if (i_img < 0 || i_img >= N)
                continue;
            for (int j_img = j_start, j_fil = 0; j_img <= j_end; j_img++, j_fil++)
            {
                if (j_img < 0 || j_img >= N)
                    continue;
                sum_prod += img[INDEX(i_img, j_img, N)] * filter[INDEX(i_fil, j_fil, M)];
            }
        }
        
        // printf("%f\n", sum_prod);
        // unsigned char result = ((int) sum_prod <= 255.0) ? (unsigned char) sum_prod : 255;
        unsigned char result = (sum_prod > 255) ? 255 : sum_prod;
        if (result > maior)
            maior = result;
        
        if (result < menor)
            menor = result;

        new_img[n] = result;
    }

    // TESTE - REMOVER DPS
    time = clock() - time;
    printf("Tempo: %fs\n", ((double) time) / (CLOCKS_PER_SEC));

    // TESTE - REMOVER DPS
    // printf("NxN * MxM:\n");
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //         printf("%d ", new_img[INDEX(i, j, N)]);
    //     printf("\n");
    // }
    // printf("\n");
    // FIM DO TESTE - REMOVER DPS

    printf("%d %d\n", maior, menor);
    return 0;
}
