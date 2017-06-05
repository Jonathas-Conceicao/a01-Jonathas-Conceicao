#include "roteador.h"
#include "simpletest.h"
#include <assert.h>


uint32_t iptoint(int a, int b, int c, int d) {
  return (uint32_t) (a<<24)+(b<<16)+(c<<8)+d;
}

void test1() {
  entrada rotas[4] = { iptoint(5,15,0,0), 16, 1,
                       iptoint(5,3,13,0), 8,  2,
                       iptoint(3,13,0,0), 24, 3 };
  uint32_t pacotes[100];
  uint32_t *result;

  for (size_t i=0; i<100; i++ ) {
    pacotes[i] = iptoint(0,0,0,0);
  }

  WHEN("Teste um. Três rotas distintas mas com todos os pacotes para o ip 0.0.0.0 (Broadcast)");
  IF("Envio um número igual de pacotes para cada rota");

  result = roteamento(rotas, 3, pacotes, 100, 3);
  assert(result);

  THEN("Nenhum pacote deve ser descartado");
  isEqual(result[0], 0, 1); /* descartados */
  THEN("Devo ter o mesmo número de pacotes em cada enlace restante");
  for (size_t i=1; i<4; i++) {
    isEqual(result[i], 100, 1);
  }
}

int main(void) {

  DESCRIBE("Testes extras do simulador de roteador");

  test1();
  GRADEME();

  if (grade==maxgrade)
    return 0;
  else return grade;
}
