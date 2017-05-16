#include "roteador.h"
#include <stdlib.h>

#include <stdio.h>

int *split(uint32_t);
void sortEntrada(entrada*, int);
void printRota(entrada);
int compEntrada(entrada, entrada);
int assig(entrada *, int, uint32_t);

uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes,
                      int num_pacotes, int num_enlaces) {
  // printf("Pacotes\n");
  // for (size_t i = 0; i < num_rotas; i++) {
  //   printRota(rotas[i]);
  // }
  sortEntrada(rotas, num_rotas);
  // printf("Ordenados\n");
  // for (size_t i = 0; i < num_rotas; i++) {
  //   printRota(rotas[i]);
  // }
  uint32_t *ret;
  ret = malloc(sizeof(uint32_t) * num_enlaces);
  int x;
  for (size_t i = 0; i < num_pacotes; i++) {
    x = assig(rotas, num_rotas, pacotes[i]);
    ret[x]++;
  }
  return ret;
}

int assig(entrada *buffer, int buffer_length, uint32_t pacote) {
  int x = 0;
  int rBuffer;
  int rPacote;
  for (size_t i = 0; i < buffer_length; i++) {
    rPacote = pacote >> 32 - (int) buffer[i].mascara;
    rBuffer = buffer[i].endereco >> 32 - (int) buffer[i].mascara;
    if (rPacote == rBuffer) {
      return (int) buffer[i].enlace;
    }
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

void printRota(entrada in) {
    int *splited = split(in.endereco);
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

int compEntrada(entrada a, entrada b) {
  if (a.endereco > b.endereco) {
    return 1;
  } else if (a.endereco < b.endereco) {
    return -1;
  }
  return 0;
}
