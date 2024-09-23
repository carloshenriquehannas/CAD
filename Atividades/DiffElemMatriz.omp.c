#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_NEIGHBORS 8

//Funcao para gerar valores aleatorios
void generate_matrix(int **matrix, int N, unsigned int seed) {
    srand(seed);  //Define a semente para a geração de números aleatórios
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 100;  //Numeros entre 0 e 99
        }
    }
}

//Funcao para calcular a maior diferença entre um elemento e seus vizinhos
void find_max_difference(int **matrix, int N) {
    int max_diff = 0;
    int max_val = 0;
    int min_val = 0;

    #pragma omp parallel for collapse(2) shared(max_diff, max_val, min_val)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int current_val = matrix[i][j];
            int neighbors[MAX_NEIGHBORS];
            int count = 0;

            //Coleta os vizinhos
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if ((di != 0 || dj != 0) && (i + di >= 0 && i + di < N) && (j + dj >= 0 && j + dj < N)) {
                        neighbors[count++] = matrix[i + di][j + dj];
                    }
                }
            }

            //Calcula a diferença máxima
            for (int k = 0; k < count; k++) {
                int neighbor_val = neighbors[k];
                int diff = abs(current_val - neighbor_val);

                //Atualiza max_diff se necessário
                #pragma omp critical
                {
                    if (diff > max_diff) {
                        max_diff = diff;
                        max_val = (current_val > neighbor_val) ? current_val : neighbor_val;
                        min_val = (current_val < neighbor_val) ? current_val : neighbor_val;
                    } else if (diff == max_diff) {
                        //Manter os valores minimos e maximos em caso de empates
                        if (current_val > max_val) {
                            max_val = current_val;
                        }
                        if (current_val < min_val) {
                            min_val = current_val;
                        }
                    }
                }
            }
        }
    }

    //Exibe os resultados
    printf("%d %d", max_val, min_val);
}

int main() {
    int N, seed;

    scanf("%d %d", &N, &seed);

    // Alocação da matriz
    int **matrix = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = malloc(N * sizeof(int));
    }

    //Geracao da matriz
    generate_matrix(matrix, N, seed);

    //Procura maior diferenca
    find_max_difference(matrix, N);

    //Libera memoria da matriz
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
