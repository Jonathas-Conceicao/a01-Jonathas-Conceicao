#include "roteador.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct cList_ {
  uint32_t *list;
  int max_size;
  int insPos;
  int outPos;
  int qnt;
} cList;

cList *init(int);
void push(cList *, uint32_t);
uint32_t pop(cList *);

int *split(uint32_t);
void printRota(uint32_t);

void sortEntrada(entrada*, int);
int compEntrada(entrada, entrada);

int assig(entrada *, int, uint32_t);

uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes,
                      int num_pacotes, int num_enlaces) {
  // printf("Pacotes\n");
  // for (size_t i = 0; i < num_rotas; i++) {
  //   printRota(rotas[i].endereco);
  // }
  sortEntrada(rotas, num_rotas);
  // printf("Ordenados\n");
  // for (size_t i = 0; i < num_rotas; i++) {
  //   printRota(rotas[i].endereco);
  // }
  cList *listaCircular;
  listaCircular = init(num_pacotes);
  for (size_t i = 0; i < num_pacotes; i++) {
    push(listaCircular, pacotes[i]);
  }
  uint32_t *ret;
  ret = malloc(sizeof(uint32_t) * num_enlaces);
  int x;
  for (size_t i = 0; i < num_pacotes; i++) {
    // x = assig(rotas, num_rotas, pacotes[i]);
    x = assig(rotas, num_rotas, pop(listaCircular));
    ret[x]++;
  }
  return ret;
}

int assig(entrada *buffer, int buffer_length, uint32_t pacote) {
  int x = 0;
  uint32_t rBuffer;
  uint32_t rPacote;
  for (size_t i = 0; i < buffer_length; i++) {
    rBuffer = buffer[i].endereco >> 32 - (int) buffer[i].mascara;
    rPacote = pacote >> 32 - (int) buffer[i].mascara;
    if (rPacote == rBuffer) {
      return (int) buffer[i].enlace;
    }
  }
  return 0;
}

cList *init(int size) {
  cList *ret;
  ret = malloc(sizeof(cList));
  (*ret).list = malloc(sizeof(uint32_t) * size);
  (*ret).insPos = 0;
  (*ret).outPos = 0;
  (*ret).max_size = size;
  (*ret).qnt = 0;

  return ret;
}

void push(cList *cl, uint32_t data) {
  (*cl).list[(*cl).insPos] = data;
  (*cl).insPos = ((*cl).insPos + 1) % (*cl).max_size;
  if ((*cl).qnt + 1 >= (*cl).max_size) {
    (*cl).qnt = (*cl).max_size;
  } else {
    (*cl).qnt++;
  }
  return;
}

uint32_t pop(cList *cl) {
  if ((*cl).qnt) {
    uint32_t p;
    p = (*cl).list[(*cl).outPos];
    (*cl).outPos = ((*cl).outPos + 1) % (*cl).max_size;
    return p;
  }
  return 0;
}

void sortEntrada(entrada* buffer, int size) {
  int i, flag;
  entrada tmp;
  do{
    flag = 0;
    for (i = 0; i < size-1; i++) {
      if (compEntrada(buffer[i], buffer[i+1]) == -1) {
        tmp = buffer[i];
        buffer[i] = buffer[i+1];
        buffer[i+1] = tmp;
        flag = 1;
      }
    }
  }while(flag);
}

int compEntrada(entrada a, entrada b) {
  if (a.endereco > b.endereco) {
    return 1;
  } else if (a.endereco < b.endereco) {
    return -1;
  }
  return 0;
}

void printRota(uint32_t in) {
  int *splited = split(in);
  printf("%i.%i.%i.%i\n",splited[0], splited[1], splited[2], splited[3]);
}

int *split(uint32_t addr) {
  int *ret = malloc(sizeof(short int)*4);
  ret[0] = addr>>24;
  ret[1] = (addr<<8)>>24;
  ret[2] = (addr<<16)>>24;
  ret[3] = (addr<<24)>>24;
  return ret;
}
