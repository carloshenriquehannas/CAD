#include <stdio.h> 
#include <omp.h>   

int main()
{
    int number_threads;
    scanf("%d", &number_threads);

    #pragma omp parallel num_threads(number_threads)
    {
        printf("Hello, World!\n");
    }

    return 0;
}