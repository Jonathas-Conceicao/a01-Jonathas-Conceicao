
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *imprime_mensagem( void *ptr );

int main(int argc, char ** argv)
{
	/* as threads que serao criadas */
     pthread_t thread1, thread2, thread3;
	  /* as mensagens */
     char *mensagem1 = "Thread 1";
     char *mensagem2 = "Thread 2";
     char *mensagem3 = "Thread 3";
	  /* os valores de retorno de cada thread */
     int  iret1, iret2, iret3;

	  /* cria threads independentes, cada uma executando a funcao com parametros diferentes */
     iret1 = pthread_create( &thread1, NULL, imprime_mensagem, (void*) mensagem1);
     iret2 = pthread_create( &thread2, NULL, imprime_mensagem, (void*) mensagem2);
     iret3 = pthread_create( &thread2, NULL, imprime_mensagem, (void*) mensagem3);

	  /* espera as threads terminarem antes de terminar a execucao do processo */
     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 
     pthread_join( thread3, NULL); 

     printf("Thread 1 retornou: %d\n",iret1);
     printf("Thread 2 retornou: %d\n",iret2);
     printf("Thread 3 retornou: %d\n",iret2);
     return 0;
}

void *imprime_mensagem( void *ptr )
{
     char *mensagem;
     mensagem = (char *) ptr;
     printf("Eu sou a thread %s \n", mensagem);
     return (void *) 0;	
}

