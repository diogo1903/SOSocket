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
  short tipo; //tipo do arquivo 0 - livre, 1 - diretorio, 2 - ".txt"
  short tam; //tamanho do arquivo em bytes
  short tamlista; //quantos blocos referenciados
  short lista[9]; // listagem endereços de blocos referenciados
  short tamnome;
  char nome[50]; //nome do arquivo
}inode;

typedef struct arq{
  char livre[nbytelistabits];
  inode i[ninodes];
  char blocos[nblocos*tambloco];
}arquivo;

FILE *fp;
arquivo principal;


int alocaespaco(char texto){

}

void printinode(inode a){
  int x;
  printf("Tipo: %c\n", a.tipo);
  printf("Tamanho: %d Bytes\n",a.tam);
  printf("Tam Lista: %c \nLista: ", a.tamlista);
  for(x = 0; x < 9; x++){
    printf("%d, ", a.lista[x]);
  }
  printf("%d\n", a.tamnome);
  printf("\n Nome: ");
  for(x = 0; x < 50; x++){
    printf("%c", a.nome[x]);
  }
  printf("\n");
}

int main(){

  int x = sizeof(inode);
  int y = sizeof(arquivo);
  printf("texto texto texto\n\n");
  printf("%d \n%d", x, y);
  return 0;
}

// int fseek (FILE *fp, long numbytes, int origem);
