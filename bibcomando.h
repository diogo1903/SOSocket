#ifndef bibcomando
#define  bibcomando
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> // write
#include <sys/wait.h>
#include <curses.h>

typedef struct comando1{
  int funcao;
  int tamChar;
  char nome[];
  int conexao;
}comando;

comando* criacomando(){
  comando new = malloc(comando);
  if(new == NULL){
    printf("Não foi possivel criar comando!\n");
    return NULL;
  }
  return &new;
};

void printcomando(comando* p, int conexao){
  ssize_t write(conexao, p.funcao + p.nome, p.tamChar+4);
  //ssize_t write(conexao, p.tamChar, 8);
  //ssize_t write(conexao, p.nome, p.tamChar + 4);
}

comando* readcomando(int conexao){
  comando new = malloc(comando);
  if(new == NULL){
    printf("Não foi possivel ler o buffer!\n");
    return NULL;
  }

  char buffer = ssize_t read(conexao)
  /*
  new.funcao = ssize_t read(conexao, int x, 8);
  new.tamChar = ssize_t read(conexao, int y, 8);
  new.nome = ssize_t read(conexao, char z[], new.tamChar + 4);*/

  return &(new);
}

void MenuPrincipal(conteudo* novo){
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

    switch(opcao)
    {
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
                menunomearq();
        case 6: novo.funcao =

        default:
                break;

    }
    MenuPrincipal();
}

void menunomedir(comando* func){

}

void menunomearq(comando* func){

}
