#ifndef bibcomando
#define  bibcomando
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // write
#include <string.h>

typedef struct comando1{
  int funcao;
  int tamChar;
  string nome;
} comando;

void printfcomando(comando p, int conexao){
  ssize_t write(conexao, p.funcao, 8);
  ssize_t write(conexao, p.tamChar, 8);
  ssize_t write(conexao, p.nome, p.tamChar);
}

comando readcomando(int conexao){
  comando new = malloc(comando);
  if(new == NULL){
    printf("Não foi possivel ler o buffer!\n");
    return NULL;
  }

  new.funcao = ssize_t read(conexao, int x, 8);
  new.tamChar = ssize_t read(conexao, int y, 8);
  new.nome = ssize_t read(conexao, string z, new.tamChar + 4);

  return new;
}
