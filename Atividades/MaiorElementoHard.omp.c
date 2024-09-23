#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int N, num_threads;
    scanf("%d", &N);

    int *vetor = malloc(N * sizeof(int));
    
    //Preenche o vetor com 1 e coloca valor de 'N' na posicao intermediaria
    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        
        //Limites para cada thread
        int tid = omp_get_thread_num();
        int chunk_size = N / num_threads;
        int start = tid * chunk_size;
        int end = (tid == num_threads - 1) ? N : start + chunk_size;

        for (int i = start; i < end; i++) {
            vetor[i] = 1;
        }

        //Thread 0 coloca o valor N na posição intermediaria
        #pragma omp barrier
        if (tid == 0) {
            vetor[N / 2] = N;
        }

        #pragma omp barrier
    }

    //Encontrando o maior valor
    int max_value = 0;

    #pragma omp parallel
    {
        int local_max = 0;
        int tid = omp_get_thread_num();
        int chunk_size = N / num_threads;
        int start = tid * chunk_size;
        int end = (tid == num_threads - 1) ? N : start + chunk_size;

        //Busca pelo maior valor
        for (int i = start; i < end; i++) {
            if (vetor[i] > local_max) {
                local_max = vetor[i];
            }
        }

        //Atualizando o maximo global
        #pragma omp critical
        {
            if (local_max > max_value) {
                max_value = local_max;
            }
        }
    }

    //Exibe o maior valor
    printf("%d", max_value);

    free(vetor);

    return 0;
}
