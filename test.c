#include "roteador.h"
#include "simpletest.h"
#include <assert.h>


uint32_t iptoint(int a, int b, int c, int d){
	return (uint32_t) (a<<24)+(b<<16)+(c<<8)+d;
}




void test1(){
	entrada rotas[4] = { iptoint(5,4,0,0), 16, 1,
						 iptoint (99,0,0,0), 8, 2,
						 iptoint(123,0,0,0), 24, 3,
						 iptoint(200,0,1,0), 24, 4 };

	uint32_t pacs[4] = { iptoint(5,4,0,1), iptoint(99,0,0,1), iptoint(123,0,0,1), iptoint(200,0,1,1) };
	uint32_t * result;

	WHEN("Tenho quatro rotas disjuntas");
	IF("Envio um pacote para cada rota");

	result = roteamento(rotas, 4, pacs, 4, 4);
	assert(result);
	THEN("Devo ter descartado nenhum pacote");
	isEqual(result[0], 0, 1); /* nenhum pacote descartado */

	THEN("Devo ter um pacote em cada enlace");
	for(int i=1; i<=4; i++){
		isEqual(result[i], 1, 1);
	}

}


void test2(){
	entrada rotas[2] = { iptoint(5,4,0,0), 16, 1,
						 iptoint(5,4,1,0), 24, 2 };

	uint32_t pacs[2] = { iptoint(5,4,0,1), iptoint(5,4,1,1) };
	uint32_t * result;

	WHEN("Tenho duas rotas com prefixos iguais até certo ponto");
	IF("Envio um pacote para cada rota");
	THEN("Devo ter um pacote em cada enlace");

	result = roteamento(rotas, 2, pacs, 2, 2);
	assert(result);

	isEqual(result[0], 0, 1); /* nenhum pacote descartado */
	for(int i=1; i<=2; i++){
		isEqual(result[i], 1, 1);
	}

}

void test3(){
	entrada rotas[2] = { iptoint(5,4,1,0), 24, 1,
						 iptoint(5,4,0,0), 16, 2 };

	uint32_t pacs[2] = { iptoint(5,4,0,1), iptoint(5,4,1,1) };
	uint32_t * result;

	WHEN("Tenho duas rotas com prefixos iguais até certo ponto (inverso ao test2)");
	IF("Envio um pacote para cada rota");
	THEN("Devo ter um pacote em cada enlace");

	result = roteamento(rotas, 2, pacs, 2, 2);
	assert(result);

	isEqual(result[0], 0, 1); /* nenhum pacote descartado */
	for(int i=1; i<=2; i++){
		isEqual(result[i], 1, 1);
	}

}


void test4(){
	entrada rotas[256];
	uint32_t pacotes[1280];
	uint32_t * result;


	for (int i=0; i<64; i++){
		for(int j=0; j<4; j++){
			/* rotas com overlap de prefixo */
			rotas[i*4+j].endereco = iptoint(10+i,1<<j,0,0);
			rotas[i*4+j].mascara = 16+j;
			rotas[i*4+j].enlace = j+1;

			pacotes[(i*4+j)*4] = iptoint(10+i,1<<j,0,1);
			pacotes[(i*4+j)*4+1] = iptoint(10+i,1<<j,0,2);
			pacotes[(i*4+j)*4+2] = iptoint(10+i,1<<j,0,3);
			pacotes[(i*4+j)*4+3] = iptoint(10+i,1<<j,0,4);

		}
	}


	/* pacotes para serem descartados */
	for  (int i=1024; i<1280; i++)
		pacotes[i] = iptoint(99,93,11,1);

	WHEN("Tabela grande de rotas");
	IF("Envio um número igual de pacotes para cada rota");
	THEN("Devo ter o mesmo número de pacotes em cada enlace");

	result = roteamento(rotas, 256, pacotes, 1280, 5);
	assert(result);

	isEqual(result[0], 256, 1); /* descartados */
	for(int i=1; i<=4; i++){
		isEqual(result[i], 256, 1);
	}

}







int main(int argc, char ** argv){


	DESCRIBE("Testes do simulador de roteador CIDR");


	test1();
	test2();
	test3();
	test4();
	GRADEME();

	if (grade==maxgrade)
		return 0;
	else return grade;

}
