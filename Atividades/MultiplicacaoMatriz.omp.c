#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

#define THREADS 5

int main()
{
    int dim_A, dim_B, dim_C, seed;
    int i,j, k;

    scanf("%d %d %d %d", &dim_A, &dim_B, &dim_C, &seed);
    srand(seed);

    int matrizA[dim_A][dim_B];
    int matrizB[dim_B][dim_C];
    int matrizC[dim_A][dim_C];

    //Preenche matrizA com valores aleatorios entre 0 e 9
    for(i = 0; i < dim_A; i++)                      //Percorre linhas                             
    {
        for(j = 0; j < dim_B; j++)                  //Percorre colunas
        {
            matrizA[i][j] = rand() % 10;
        }
    }

    //Preenche matrizB com valores aleatorios entre 0 e 9
    for(i = 0; i < dim_B; i++)                      //Percorre linhas
    {
        for(j = 0; j < dim_C; j++)                  //Percorre colunas
        {
            matrizB[i][j] = rand() % 10;
        }
    }

    //Preenche matrizC: matric = matrizA * matrizB
    #pragma omp parallel for num_threads(THREADS) private(i, j, k)
    for(i = 0; i < dim_A; i++)                     //Percorre linhas
    {
        for(j = 0; j < dim_C; j++)                 //Percorre colunas
        {
            matrizC[i][j] = 0;
            for(k = 0; k < dim_B; k++)
            {
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }

    //Exibe a matriz resultante (matrizC)
    for(i = 0; i < dim_A; i++)                      //Percorre linhas
    {
        for(j = 0; j < dim_C; j++)                  //Percorre colunas
        {
            if(j == dim_A - 1)
            {
                printf("%d", matrizC[i][j]);
            } else
            {
                printf("%d ", matrizC[i][j]);
            }
            
        }
        printf("\n");
    }
    
    return 0; 
}