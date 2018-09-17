#ifndef bibcomando
#define  bibcomando

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> // write
#include <sys/wait.h>
#include <curses.h>
#include <string.h>

//estatico
typedef struct comando1{
  int funcao;
  int tamChar;
  char nome[];
  int idconexao;
}comando;

// dinamico
// char funcao, char tamChar, char nome[], char idconexao
// funcao, tamChar, nome[], idconexao

comando *criacomando(int idconexao){
  comando novo = malloc(comando);
  if(new == NULL){
    printf("Não foi possivel criar comando!\n");
    return NULL;
  }
  novo.idconexao = conexao;
  novo.funcao = 0;
  return &novo;
};

void enviacomando(comando *p){
  ssize_t write(p.idconexao, p.funcao + p.nome, p.tamChar+4);
}     //arrumar

void freecomando(comando *novo){
  int i = novo.idconexao;
  free(&novo);
  fechaconexao(i);
}

void MenuCliente(conteudo* novo){
    int opcao;
    system("cls");
    printf("***************************\n");
    printf("1. Criar diretório\n");
    printf("2. Remover diretório\n");
    printf("3. Mostrar diretório\n");
    printf("4. Entrar em diretório\n");
    printf("5. Criar arquivo\n");
    printf("6. Remover arquivo\n");
    printf("7. Escrever no arquivo\n");
    printf("8. Mostrar conteudo do arquivo\n");
    printf("9. Sair\n");
    printf("***************************\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);
    switch(opcao){
        case 1: novo.funcao = 1;
                menunomedir(&novo);
                break
        case 2: novo.funcao = 2;
                menunomedir(&novo);
                break;
        case 3: novo.funcao = 3;
                menunomedir(&novo);
                break;
        case 4: novo.funcao = 4;
                menunomedir(&novo);
                break
        case 5: novo.funcao = 5;
                menunomearq(&novo);
                break;
        case 6: novo.funcao = 6;
                menunomearq(&novo);
                break;
        case 7: novo.funcao = 7;
                menunomearq(&novo);
                break;
        case 8: novo.funcao = 8;
                menunomearq(&novo);
                break;
        case 9: novo.funcao = 9;
                menunomearq(&novo);
                break;
        default:
                free(&novo);
                break;
    }
    if(novo.funcao != 0){
      enviacomando(&novo);
    }
    novo.funcao = 0;
    MenuCliente(conteudo* novo);
}

void menunomedir(comando* novo){
  system("cls");
  char frase;
  printf("Digite o nome do diretório com no maximo 50 caracteres: ");
  scanf("%s", &frase);
  int x = strlen(frase);
  novo.nome = frase;
  novo.tamChar = x;
}

void menunomearq(comando* func){
  system("cls");
  char frase;
  printf("Digite o nome do arquivo com no maximo 50 caracteres: ");
  scanf("%s", &frase);
  int x = strlen(frase);
  novo.nome = frase;
  novo.tamChar = x;
  return;
}

comando* readcomando(int conexao){  // arrumar
  comando new = malloc(comando);
  if(new == NULL){
    printf("Não foi possivel criar espaço!\n");
    return NULL;
  }

  char buffer[50] = ssize_t read(conexao);
  /*
  new.funcao = ssize_t read(conexao, int x, 8);
  new.tamChar = ssize_t read(conexao, int y, 8);
  new.nome = ssize_t read(conexao, char z[], new.tamChar + 4);*/

  return &new;
}

#endif
