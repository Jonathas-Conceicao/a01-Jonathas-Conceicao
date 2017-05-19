#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "roteador.h"

typedef struct cList_ {
  uint32_t *list;
  int max_size;
  int insPos;
  int outPos;
  int qnt;
} cList;

typedef struct thrdArgs_ {
  cList *listaCircular;
  pthread_mutex_t fifo_lock;
  entrada *rotas;
  int num_rotas;
  uint32_t *pacotes;
  uint32_t *ret;
  int num_pacotes;
  pthread_mutex_t ret_lock;
  int inserting;
} thrdArgs;

cList *init(int);
void clean(cList **);
void push(cList *, uint32_t);
uint32_t pop(cList *);

int *split(uint32_t);
void printRota(uint32_t);

void sortEntrada(entrada*, int);
int compEntrada(entrada, entrada);

int assig(entrada *, int, uint32_t);


void *thread_push(void *);
void *thread_pop(void *);

uint32_t * roteamento(entrada * rotas, int num_rotas, uint32_t * pacotes,
                      int num_pacotes, int num_enlaces) {
  pthread_t threadIn, threadOut1, threadOut2, threadOut3, threadOut4;
  int idTIn, idTOut1, idTOut2, idTOut3, idTOut4;
  // pthread_mutex_t fifo_lock;
  // pthread_mutex_t ret_lock;
  cList *listaCircular;
  uint32_t *ret;

  sortEntrada(rotas, num_rotas);
  listaCircular = init(num_pacotes);
  ret = malloc(sizeof(uint32_t) * (num_enlaces + 1));
  for (size_t i = 0; i < (num_enlaces+1); i++) {
    ret[i] = 0;
  }

  thrdArgs pArgs;
  pArgs.listaCircular = listaCircular;
  pArgs.rotas = rotas;
  pArgs.num_rotas = num_rotas;
  pArgs.pacotes = pacotes;
  pArgs.num_pacotes = num_pacotes;
  pArgs.ret = ret;
  pArgs.inserting = 1;
  pthread_mutex_init(&pArgs.fifo_lock, NULL);
  pthread_mutex_init(&pArgs.ret_lock, NULL);
  idTIn = pthread_create( &threadIn, NULL, thread_push, (void *) &pArgs);
  idTOut1 = pthread_create( &threadOut1, NULL, thread_pop, (void *) &pArgs);
  idTOut2 = pthread_create( &threadOut2, NULL, thread_pop, (void *) &pArgs);
  idTOut3 = pthread_create( &threadOut3, NULL, thread_pop, (void *) &pArgs);
  idTOut4 = pthread_create( &threadOut4, NULL, thread_pop, (void *) &pArgs);
  pthread_join( threadOut4, NULL);
  pthread_join( threadOut3, NULL);
  pthread_join( threadOut2, NULL);
  pthread_join( threadOut1, NULL);
  pthread_join( threadIn, NULL);
  pthread_mutex_destroy(&pArgs.fifo_lock);
  pthread_mutex_destroy(&pArgs.ret_lock);

  clean(&listaCircular);
  return ret;
}

void *thread_push(void *ptr) {
  thrdArgs *arg = (thrdArgs *) ptr;
  for (size_t i = 0; i < (*arg).num_pacotes; i++) {
    pthread_mutex_lock(&(*arg).fifo_lock);
    push((*arg).listaCircular, (*arg).pacotes[i]);
    pthread_mutex_unlock(&(*arg).fifo_lock);
  }
  (*arg).inserting = 0;
  return (void *) 0;
}

void *thread_pop(void *ptr) {
  thrdArgs *arg = (thrdArgs *) ptr;
  uint32_t pacote;
  // for (size_t i = 0; i < (*arg).num_pacotes; i++) {
  while ( ((*(*arg).listaCircular).qnt != 0) || (*arg).inserting) {
    pthread_mutex_lock(&(*arg).fifo_lock);
    pacote = pop((*arg).listaCircular);
    pthread_mutex_unlock(&(*arg).fifo_lock);
    if (pacote) { //Ignores empty returns from pop
      pthread_mutex_lock(&(*arg).ret_lock);
      (*arg).ret[assig((*arg).rotas, (*arg).num_rotas, pacote)]++;
      pthread_mutex_unlock(&(*arg).ret_lock);
    }
  }
  // }
  return (void *) 0;
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

void clean(cList **p) {
  free((*(*p)).list);
  free(*p);
  return;
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
    (*cl).qnt--;
    return p;
  }
  return 0; //Usado para representar fila vazia.
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
