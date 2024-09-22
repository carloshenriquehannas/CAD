#include <stdio.h>
#include <omp.h>

#define THREADS 10

int main()
{
    int N, soma_perfeitos;
    soma_perfeitos = 0;

    scanf("%d", &N);    

    //Codigo paralelo: procura e soma os numeros perfeitos ate N
    #pragma omp parallel for num_threads(THREADS) reduction(+:soma_perfeitos)
    for (int num = 2; num <= N; num++)
    {
        int soma_divisores = 0;

        // Calcular a soma dos divisores do número atual
        for (int i = 1; i <= num / 2; i++)
        {
            if (num % i == 0)
            {
                soma_divisores += i;
            }
        }

        //Verifica se eh numero perfeito
        if (soma_divisores == num)
        {
            soma_perfeitos += num;  //Se sim, inclui no somatorio final
        }
    }

    //Exibe os numeros perfeitos
    printf("%d", soma_perfeitos);

    return 0;
}