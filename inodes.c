#include <stdio.h>
#include <stdlib.h>

#define BLOCOS 64

typedef struct nos{
  char tipo; //tipo do arquivo 0 - livre, 1 - diretorio, 2 - ".txt"
  char tam; //tamanho do arquivo em bytes
  char nome[50]; //nome do arquivo
  char tamlista; //quantos blocos referenciados
  int lista[10]; // listagem endereços de blocos referenciados
}inode;

/*
listagem de 064 blocos =    8 bytes
   64 blocos * 4 bytes =  256 bytes
  25 inodes * 93 bytes = 2325 bytes
                 total = 2589 bytes
*/

int main(){
  FILE *fp = fopen("arquivo.bin","r+b");
  if (!fp){
    printf ("Erro na abertura do arquivo. Fim de programa.");
    exit (1);
  }
  //Codigo aqui
  
  fclose(fp);
  return 0;
}
