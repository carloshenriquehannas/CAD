#include <stdio.h> 
#include <omp.h>   

int main()
{
    int number_threads;

    //Leitura do teclado: quantidade de threads que serao usadas
    scanf("%d", &number_threads);                           

    //Codigo paralelizado
    #pragma omp parallel num_threads(number_threads)
    {
        printf("Hello, World!\n");
    }

    return 0;
}