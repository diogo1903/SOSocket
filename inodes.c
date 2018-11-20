#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
listagem de 064 blocos =    8 bytes - bytes 0 a 7
  10 inodes * 76 bytes =  760 bytes - bytes 8 a 767
   64 blocos * 4 bytes =  256 bytes - bytes 768 a 994
                 total = 1024 bytes
*/

#define taminodes 76
#define tambloco 4
#define nbytelistabits 8
#define ninodes 10
#define nblocos 64
#define iniclista 0
#define inicinodes 8
#define inicblocos 768
#define tambuffer 1024

typedef struct nos{
  char tipo; //tipo do arquivo 0 - livre, 1 - diretorio, 2 - ".txt"
  short tam; //tamanho do arquivo em bytes
  char tamlista; //quantos blocos referenciados
  short lista[9]; // listagem endereços de blocos referenciados
  short tamnome;
  char nome[49]; //nome do arquivo
}inode;

typedef struct arq{
  char livre[nbytelistabits];
  inode i[ninodes];
  char blocos[nblocos*tambloco];
}arquivo;

FILE *fp;
arquivo principal;
int fda;

// pega buffer e transforma em arquivo
void arrumaarquivo(char buffer[tambuffer]){
  int x, y, z;
  for(x = iniclista; x < inicinodes; x++){ // blocos livres
    principal.livre[x] = buffer[x];
  }
  for(x = inicinodes; x < inicblocos; x += taminodes){  // lista inodes
    for(y = 0; y < taminodes; y++){ // cada inode
      z = x + y; // posição no buffer
      if(y = 0){ // pega tipo
        principal.i[y].tipo = buffer[z];
      }
      if(y = 1 ){ // pega tam
        principal.i[y].tam = buffer[z];
      }
      if(y = 2){ // pega tamlista
        principal.i[y].tamlista = buffer[z];
      }
      if(y > 2 && y < 12){ // pega lista
        principal.i[y].lista[y - 3] = buffer[z];
      }
      if(y = 12){ // pega tamnome
        principal.i[y].tamnome = buffer[z];
      }
      if(y > 12 && y <= taminodes){ //pega nome
        principal.i[y].nome[y - 13] = buffer[z];
      }
    }
  }
  for(x = inicblocos; x <= tambuffer; x++){ // lista blocos
    principal.blocos[x] = buffer[x];
  }
}

int alocaespaco(char texto){

}

void printinode(inode a){
  int x;
  printf("Tipo: %c\n", a.tipo);
  printf("Tamanho: %c Bytes\n",a.tam);
  printf("Tam Lista: %c \nLista: ", a.tamlista);
  for(x = 0; x < 9; x++){
    printf("%c, ", a.lista[x]);
  }
  printf("\n Nome: ");
  for(x = 0; x < 50; x++){
    printf("%c", a.nome[x]);
  }
}

int main(){

  int x = sizeof(inode);
  int y = sizeof(arquivo);
  printf("%d \n%d", x, y);
  return 0;
}

// int fseek (FILE *fp, long numbytes, int origem);
