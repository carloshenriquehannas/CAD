/*  O codigo possui uma regiao paralela com 2 threads, porem apenas uma thread executa o comando single
    No bloco de codigo single, a saida sera: "race car"
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) 
{
  //Inicio da regiao paralela, com 2 threads
  #pragma omp parallel num_threads(2)
  {
    //Apenas uma thread executara esse bloco de codigo
    #pragma omp single
    {
      printf("race ");
      printf("car ");
    }

  } //Final da regiao paralela

  printf("\n");
  return(0);

}
