
#ifndef _ROTEADOR_H_
#define _ROTEADOR_H_

		
struct roteamento{
	uint32 endereco;
	char mascara; /* entre 1 e 31 bits */
};


/* Função que totaliza o número de pacotes encaminhados para cada enlace 
 * @param rotas lista de rotas (um vetor)
 * @param num_rotas número de elementos da lista de rotas
 * @param pacotes lista de endereços de destino dos pacotes a serem encaminhados (um vetor)
 * @param num_pacotes número de pacotes a serem encaminhados
 */
uint32 * roteamento(struct roteamento * rotas, int num_rotas, uint32 * pacotes, int num_pacotes);


#endif