/*
    SSC0903 - COMPUTACAO DE ALTO DESEMPENHO - 2024/2 - Turma B
    TRABALHO PRATICO 1

    Integrantes do grupo:
        Carlos Henrique Hannas de Carvalho      NUSP: 11965988
        Carlos Nery Ribeiro                     NUSP: 12547698
        Gabriel Ribeiro Rodrigues Dessotti      NUSP: 12547228
        Lucas Carvalho Freiberger Stapf         NUSP: 11800559
        Pedro Manicardi Soares                  NUSP: 12547621

    Para compilar: gcc filter_conv.omp.c -o filter_conv -fopenmp

    OBS: Considerar o ultimo codigo enviado no RunCodes pelo membro Carlos Henrique Hannas de Carvalho
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/// Define a quantidade de threads a serem criadas pelo OMP
#define NUM_THREADS 8

/// Calcula o indice linear equivalente de uma matriz bidimensional armazenada 
/// em um array unidimensional, como se fosse uma matriz armazenada de forma continua em memoria
/// Parametros:
/// (i, j): indices da linha e da coluna da matriz.
/// c: numero de colunas da matriz. 
#define INDEX(i, j, c) ((i * c) + j)

/// Calcula a linha i de uma matriz que esta representada na forma de um vetor com base no indice n.
#define I(n, c) (n / c)

/// Calcula a coluna j de uma matriz que esta representada na forma de um vetor com base no indice n.
#define J(n, c) (n % c)

int main(int argc, char const *argv[])
{
    // Leitura dos dados de entrada
    int N, M, S;
    scanf("%d %d %d", &N, &M, &S);

    srand(S);

    // Criacao da imagem original
    unsigned char *img = malloc(N * N * sizeof(unsigned char));
    for (int n = 0; n < N * N; n++)
        img[n] = rand() % 256;
    
    // Criacao do filtro
    float *filter = malloc(M * M * sizeof(float));
    for (int m = 0; m < M * M; m++)
        filter[m] = (rand() % 10) / 10.0;

    // Criacao da imagem nova 
    unsigned char *new_img = malloc(N * N * sizeof(unsigned char));

    unsigned char maior = 0, menor = 255;
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(max: maior) reduction(min: menor)
    for (int n = 0; n < N * N; n++)
    {
        float sum_prod = 0;

        // Cada submatriz MxM centrada no elemento i,j tem a seguinte estrutura:
        //
        // [i_start, j_start]   ...     [i_start, j_end]
        // .                            .
        // .                    [i,j]   .
        // .                            .
        // [i_end, j_start]     ...     [i_end, j_end]
        //
        // Onde:
        // - i_start = i - ((M - 1) / 2)
        // - i_end = i + ((M - 1) / 2)
        // - j_start = j - ((M - 1) / 2)
        // - j_end = j + ((M - 1) / 2)
        //
        // Nos casos de borda, indices negativos ou maiores que a dimensao da matriz sao ignorados.
        int i_start = I(n, N) - ((M - 1) / 2);
        int i_end = I(n, N) + ((M - 1) / 2);
        int j_start = J(n, N) - ((M - 1) / 2);
        int j_end = J(n, N) + ((M - 1) / 2);

        for (int i_img = i_start, i_fil = 0; i_img <= i_end; i_img++, i_fil++)
        {
            if (i_img < 0 || i_img >= N) // Linha fora dos limites da imagem
                continue;
            for (int j_img = j_start, j_fil = 0; j_img <= j_end; j_img++, j_fil++)
            {
                if (j_img < 0 || j_img >= N) // Coluna fora dos limites da imagem
                    continue;
                sum_prod += img[INDEX(i_img, j_img, N)] * filter[INDEX(i_fil, j_fil, M)];
            }
        }
        
        unsigned char result = (sum_prod > 255) ? 255 : sum_prod;
        if (result > maior)
            maior = result;
        
        if (result < menor)
            menor = result;

        new_img[n] = result;
    }

    printf("%d %d\n", maior, menor);

    // Limpa os vetores que foram alocados anteriormente
    free(img);
    free(filter);
    free(new_img);

    return 0;
}