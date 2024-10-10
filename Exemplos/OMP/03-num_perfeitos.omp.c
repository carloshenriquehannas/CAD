/* Regiao sequencial define um teto maximo para verificar quantos numeros perfeitos existem ate o limite
   Regiao paralela utiliza T threads para procurar todos os numeros perfeitos ate o limte
   Nova regiao sequencial apenas exibe qual o tempo gasto dentro da regiao paralela
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define T 4

int main(int argc, char *argv[])
{
    int i, j, num, soma;

    double wtime;

    
    if ( argc  != 2)
    {
	printf("Wrong arguments. Please use main <amount_of_elements>\n");
	exit(0);
    }

    num = atoi(argv[1]);    //Limite para verificar quais sao os numeros perfeitos ate num
    
    wtime = omp_get_wtime();

    //Regiao paralela com T threads executando: procura todos os numeros perfeitos ate num
    #pragma omp parallel for private (i, j, soma) num_threads(T)
    for (i = 1; i < num; i++)
    {
        soma = 0;
        for (j = 1; j < i; j++)
        {
            if(i%j == 0)    //Se o numero for divisivel, possivel canditato para perfeito
            {
                soma += j;
            }
        }
        if (soma == i)      //Se a soma dos divisiveis for igual ao numero: numero perfeito
        {
            printf("%d é perfeito. \n", i); //Exibe o numero perfeito
        }
    }

    wtime = omp_get_wtime() - wtime;

    printf ( "Done. Elapsed wall clock time = %.5f\n", wtime );

    return 0;
}
