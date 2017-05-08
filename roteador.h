
#ifndef _ROTEADOR_H_
#define _ROTEADOR_H_

#include <stdint.h> 
		
typedef struct roteamento{
	uint32_t endereco;
	char mascara; /* entre 1 e 31 bits, quantos bits da parte de rede */
	char enlace; /* enlace de saida */
} entrada;


/* Função que totaliza o número de pacotes encaminhados para cada enlace 
 * @param rotas lista de rotas (um vetor)
 * @param num_rotas número de elementos da lista de rotas
 * @param pacotes lista de endereços de destino dos pacotes a serem encaminhados (um vetor)
 * @param num_pacotes número de pacotes a serem encaminhados
 * @param num_enlaces número de enlaces de saída
 * @return vetor com número de pacotes encaminhados por enlace, com primeira posição sendo descartados
 */
uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes, 
	int num_pacotes, int num_enlaces);


#endif