#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
listagem de 064 blocos =   16 bytes - bytes 0 a 16
  10 inodes * 76 bytes =  760 bytes - bytes 8 a 775
   64 blocos * 4 bytes =  256 bytes - bytes 776 a 1031
                 total = 1032 bytes
*/

#define taminodes 76
#define tambloco 4
#define nlistabits 8
#define ninodes 10
#define nblocos 64
#define iniclista 0
#define inicinodes 16
#define inicblocos 776
#define tambuffer 1032

typedef struct nos{
  short tipo; //tipo do arquivo 0 - livre, 1 - diretorio, 2 - ".txt"
  short tam; //tamanho do arquivo em bytes
  short tamlista; //quantos blocos referenciados
  short lista[9]; // listagem endereços de blocos referenciados
  short tamnome;
  char nome[50]; //nome do arquivo
}inode;

typedef struct arq{
  short livre[nlistabits];
  inode i[ninodes];
  char blocos[nblocos*tambloco];
}arquivo;

FILE *fp;
arquivo principal;

// Calcula posição na memoria, retorna posição. Recebe x = arquivo.livre[x] e y = slot (1 e 2)
int conta(int x, int pos){ // pega end bloco
  int resultado;
  resultado = ((pos-1) * 4 + x * 8) + inicblocos;
  return resultado;
}

// Procura slot de 4 bytes livres, retorna end do primeiro
int alocaespaco(arquivo *novo){
  int x, res;
  for(x = 0; x < nlistabits; x++){
    if(novo->livre[x] = 0){ // sem espaço ocupado
      novo->livre[x] = 1;
      res = conta(x, 1);
      return res;
    }
    if(novo->livre[x] = 1){ //pega segundo slot
      novo->livre[x] = 3;
      res = conta(x, 2);
      return res;
    }
    if(novo->livre[x] = 2){ //pega primeiro slot
      novo->livre[x] = 3;
      res = conta(x, 1);
      return res;
    }
  }
  printf("Sem espaço");
  return -1;
}

//define inode, iniciando com nome e tipo, retorna posição do inode na lista
int criainode(arquivo *novo, int tipo, char nome[50]){ 
  int x, y;
  for(x = 0; x < ninodes; x++){
    if(novo->i[x].tipo = 0){
      novo->i[x]->tipo = tipo;
      strcpy(novo->i[x]->nome, nome);
      novo->i[x]->tam = 0;
      novo->i[x]->tamlista = 0;
      for(y = 0; y < 9; y++){
        novo->i[x]->lista[y] = 0;
      }
      novo->i[x]->tamnome = strlen(nome);
    }
    return x;
  }
  if(x >= ninodes){
    printf("Sem Inode disponivel!\n");
  }
}

void printinode(inode *a){
  int x;
  printf("Tipo: %d\n", a->tipo);
  printf("Tamanho: %d Bytes\n",a->tam);
  printf("Tam Lista: %d \nLista: ", a->tamlista);
  for(x = 0; x < 9; x++){
    printf("%d, ", a->lista[x]);
  }
  printf("%d\n", a->tamnome);
  printf("\n Nome: ");
  for(x = 0; x < 50; x++){
    printf("%c", a->nome[x]);
  }
  printf("\n");
}
