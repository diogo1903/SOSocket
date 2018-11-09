#include <stdio.h>
#include <stdlib.h>

#define TAMNOS 64
#define LIMITEREFENCIADOS 10

int[TAMNOS];

typedef struct nos{
  char perm[3]; //quem pode acessar 0 - read, 1 - write e 2 - execução
  int tipo; //tipo do arquivo
  int id[2]; //identificador do dono e grupo
  int tam; //tamanho do arquivo em bytes
  int tamlista; //quantos blocos referenciados
  int lista[LIMITEREFENCIADOS]; // listagem endereços de blocos referenciados
  char nome[50]; //nome do arquivo
}inode;

inode zera(inode* a){
  a.perm[0] = 0;
  a.perm[1] = 0;
  a.perm[2] = 0;
  a.tipo = 0;
  a.id[0] = 0;
  a.id[1] = 0;
  a.tam = 0;
  a.tamlista = 0;
  int x;
  for(x = 0, x < LIMITEREFENCIADOS; x++){
    a.lista[x] = 0;
  }
  for(x = 0, x < 50, x++){
    a.nome[x] = NULL;
  }
}
