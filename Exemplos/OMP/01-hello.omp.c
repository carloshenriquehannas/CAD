/* O programa possui uma primeira regiao sequencia que imprime o ID e a quantidade de threads
   Em seguida, numa regiao paralela com 4 threads, novamente imprime-se o ID de cada uma delas e a quantidade de threads dentro da regiao paralela
   Por fim, uma nova regiao sequencial. Imprime o ID, a quantidade de threads e a soma dos IDs que existia na regiao paralela
*/

# include <stdlib.h>
# include <stdio.h>
# include <omp.h>

#define T 4

int main ( int argc, char *argv[] )
{  
	int thread_num, nthreads, soma = 0;  

	thread_num = omp_get_thread_num ( );	//Coleta o numero da thread  
	nthreads = omp_get_num_threads(); 		//Coleta a quantidade de threads na regiao sequencial
	printf ( "Hello-world da thread mestre  (região sequencial): %d. Num_threads=%d. \n", thread_num, nthreads );	//Imprime ID da thread mestre e quantidade de threads na regiao sequencial

	//Regiao paralela com T threads
	# pragma omp parallel private (thread_num, nthreads) num_threads(T) reduction(+: soma)
	{    
		thread_num = omp_get_thread_num();	//Coleta o numero da thread    
		nthreads = omp_get_num_threads( );	//Coleta a quantidade de threads na regiao paralela
		soma = thread_num;					//Soma o ID de cada thread
		printf (" \nHello-world da thread %d na região paralela, Num_threads aqui: %d\n", thread_num, nthreads);	//Imprime ID da thread e quantidade de threads na regiao paralela
	}

	//Nova regiao sequencial
	thread_num = omp_get_thread_num();	//Coleta o numero da thread
	nthreads = omp_get_num_threads();	//Coleta a quantidade de threads na regiao sequencial
	printf ( "\nRegião sequencial: thread_num = %d, Num_threads = %d e soma=%d \n", thread_num, nthreads, soma);	//Imprime ID da thread zero e quantidade de threads na regiao sequencial
	return 0;
}
