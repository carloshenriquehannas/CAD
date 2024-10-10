/* O codigo possui uma regiao paralela com 2 threads
   Exibe algumas variacoes: race car race car (mais usual), race race car car, etc
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) 
{
    //Regiao paralela com 2 threads
    #pragma omp parallel num_threads(2)
    {
      printf("race ");
      printf("car ");
      
    } //Final da regiao paralela
    
    printf("\n");

    return(0);

}
