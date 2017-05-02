# Trabalho 1 - Sistemas Operacionais 2017/1
Prof. Maurício Lima Pilla - http://lups.inf.ufpel.edu.br/~pilla

## Dados do aluno

Declaro que o presente trabalho contém código desenvolvido exclusivamente por mim e que não foi compartilhado de nenhuma forma com terceiros a não ser o professor da disciplina. Compreendo que qualquer violação destes princípios será punida rigorosamente de acordo com o Regimento da UFPEL.

(Preencha com seus dados)

- Nome completo: 
- Username do Github: 
- Email @inf: 

## Descrição

Neste trabalho, os alunos irão desenvolver um programa em C usando POSIX Threads para simular um roteador IPv4 CIDR (_Classless Inter-Domain Routing_) [1]. 

O problema de encaminhamento de pacotes no IPv4 CIDR é um caso típico de busca pelo prefixo máximo. Uma tabela de roteamento contém endereços de rede IP,  um tamanho de máscara em bits e o enlace para onde o pacote deve ser encaminhado. Por exemplo, 

        19.5.0.0/16 2
        19.5.5.0/24 1

Na primeira linha, especificou-se que todos os pacotes com endereços de destino entre 19.5.0.0 e 19.5.255.255 devem ser encaminhados para o enlace _2_.
 Porém, a segunda linha possui um prefixo de maior comprimento e todos os endereços entre 19.5.5.0 e 19.5.5.255 são encaminhados para o enlace _1_. Quanto maior o prefixo, maior sua prioridade.

No roteador simulado neste trabalho, uma fila de entrada representa os enlaces por onde chegam pacotes. Uma fila de saída representa os enlaces por onde os pacotes saem.

Uma _thread_ coordena a inserção dos pacotes que chegam na fila respectiva. Quatro _threads_ retiram pacotes desta fila, fazem o processamento de acordo com uma tabela de roteamento compartilhada e contabilizam quantos pacotes são encaminhados para cada enlace de saída.

A entrada do trabalho é uma lista com os pacotes e uma lista para a tabela de roteamento (armazenados em um vetor cada um). A lista da tabela de roteamento não precisa estar ordenada de qualquer forma.

A saída do trabalho é uma lista com o número de pacotes encaminhados para cada enlace em ordem crescente de número de enlace.

Os enlaces são numerados de _1_ a _n_, onde _n_ é o total de enlaces de saída.  
O código deve estar contido em um arquivo chamado *roteamento.c* para versão sequencial (que não precisa usar _threads_), *roteamento_t.c* para a versão paralela. Nenhum outro arquivo deve ser modificado. A única função que deverá ser declarada para o usuário final (quer dizer, o professor) está descrita em *roteamento.h*. __ATENÇÃO__: não altere nenhum arquivo original do repositório.

## Testes

Cada trabalho deverá fornecer pelo menos quatro exemplos de teste em um arquivo chamado *teste.c* usando a biblioteca Simplegrade.  Se os alunos quiserem, podem aumentar o número de testes seguindo este padrão de nomenclatura. Uma função *main()* deverá chamar as funções de teste. 


## Produtos

* Implementação (*roteamento.c*, *roteamento_t.c*)
* Casos de teste documentados (*teste.c*)

## Cronograma

* Envio da versão sequencial: _16/05/2017_ (2 pontos)
* Envio da versão final paralela: _30/05/2017_ (8 pontos)

## Problemas a considerar

1. Como implementar a fila?
2. Quais os problemas de condição de corrida que podem acontecer?
3. Como detectar o fim da execução? 
4. Como implementar a fila de eventos da _thread_? Eles tem que estar ordenados? 
5. Como reunir os resultados finais?


## Referências


* [1] [CIDR na Wikipedia](https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing)
* [2] [Tutorial sobre POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/)
