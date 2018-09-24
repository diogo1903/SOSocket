#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


typedef struct pedido{
    char comando[16];
    char texto[64];
}pedido;

pedido trat_leitura(char msg[80])
{
    pedido pedido1;
    int i = 0, teste = 0, j=0;
    int ultimo = strlen(msg);
    msg[ultimo-1] = NULL;
    printf("trat1 \n");
    while(msg[i]!= NULL)
    {
        if((int*)msg[i]!=32 & teste ==0 & msg[i] != NULL ){
        pedido1.comando[i]= msg[i];
        i++;
        }else if(teste == 0){
            teste =1;
            i++;
        }else if(msg[i]!= NULL & teste ==1 ){
            pedido1.texto[j]= msg[i];
            j++;
            i++;
        }else
        {
            printf("Erro no tratamento 1\n");
        }         
    }
    
    //printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
    //printf("comando:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));
    return pedido1;
}


void saida(char* saidaB;)
{

  FILE *pArq;
  short int ch;
  int i=0;
  
  pArq = popen("ls", "r");
  while((ch = fgetc(pArq)) != EOF)
  {
    saidaB[i] = ch;
    i++;
    
  }
  printf("saida ok\n");
  pclose(pArq);

  
}



int main(int argc, char * argv[])
{
    pedido pedido1;

    int listenfd=0, connfd=0;
    struct sockaddr_in serv_addr;// é um estrutura do sockaddr
    struct sockaddr_in sock_cli; // é o socket do cliente 
    socklen_t sock_novo_len; 
    char sendBuff[1025];
    char resposta[512];
    char msg[80] ="2";
    //char comando[16];
    char a[10] = "a";
    char saidaB[100000];
    char comando[16];
    char texto[64];

// listenfd recebe o indentificador, descritor de soccket  socket(domain, type, protocol
    listenfd = socket(AF_INET, SOCK_STREAM,0);
// memset prenche uma variavel por um valor 
    memset(&serv_addr, '0', sizeof(serv_addr));
   // printf(" serv _aadrs: %s \n",&serv_addr);
    memset(sendBuff, '0', sizeof(sendBuff));
    //printf(" serv _aadrs: %s \n",&sendBuff);
    
// atribuo valores para a estrutura socket serv_affr
    serv_addr.sin_family = AF_INET; // tipo de conexao 
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);// nao sei 
    serv_addr.sin_port = htons(5001); //porta do servidor 
// bind(s, name, namelen);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    // escuta 10 clientes 
    listen(listenfd,10);
    int testebug = 0;
    
    while(1)
    {
        printf("iniciando a while\n");
        sock_novo_len = sizeof(sock_cli);
        connfd = accept(listenfd, (struct sockaddr*)&sock_cli, &sock_novo_len);
        printf("accept ok \n"); 
        // resposta boas vindas
        strcpy(resposta,"ola\n bem vindo\n");
        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd, sendBuff,strlen(sendBuff)); 
        
        
        //leitura 
        if(read(connfd, msg, sizeof(msg))<0)
        {
            printf("Error de leitura do socket\n");
            exit(0);
        }
        pedido1 = trat_leitura(msg);
        printf("read ok, mensagem: %s \n", msg);
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
        printf("comando:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));

        strcpy(comando, pedido1.comando);
        strcpy(texto, pedido1.texto);
        
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));


        //resposta
        char temp[40];
        if(strcmp("crdir", pedido1.comando)==0){
            strcpy(resposta, "novo dir");
            strcpy(temp, "mkdir " );
            strcat(temp, texto);
            system(temp);
        }else if(strcmp("rm", pedido1.comando)==0){
             strcpy(resposta, "deletado dir");
            strcpy(temp, "rm -r " );
            strcat(temp, texto);
            system(temp);
        }else if(strcmp("sair", pedido1.comando)==0){
            strcpy(resposta, "saindo");
            close(connfd);
        }else if(strcmp("listar", pedido1.comando)==0){
            strcpy(resposta, "listando diretorio");
            strcpy(temp, "ls " );
            strcat(temp, texto);
            system(temp);
            saida(saidaB);
            printf("%d",strlen(*saidaB));
            strcpy(resposta , saidaB);
        }else{
            printf("erro do if da conversa msg = %s  \n",msg );
            strcpy(resposta, "comando nao exite\n");
            testebug = 1;
        } 

        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd, sendBuff,strlen(sendBuff));
        close(connfd);
    }
    

    
}




//funcao que recebe o msg e atribui uma resposta
/*
void procedimento(char* comando, char* resposta)
{
    if(strcmp(comando, "oi"))
        {
            strcpy(resposta, "oi");
        }else
        printf("erro do if da conversa");   
}
*/

/*
void conversa(char* cliente)
{
    if(cliente == "oi")
    {
        resposta
    } 
    else if(cliente == "bem")
    {
        return "bem";
    }
    else if(cliente == "chau")
    {
        retunrn "chau";
    }
}
*/

// trabalho
/*
Enunciado dos trabalho

Desenvolver um sistema de arquivos distribuídos que simula padrão EXT3. O sistema deve ser desenvolvido em C ou C++ utilizando o compilador GNU GCC e chamadas de sistemas do padrão POSIX. 

O sistema deve permitir que arquivos locais sejam acessados por usuários remotos simultaneamente. As operações permitidas pelo sistema devem incluir:

    criar (sub)diretório
    remover (sub)diretório
    entrar em (sub)diretório
    mostrar conteúdo do diretório
    criar arquivo 
    remover arquivo
    escrever um sequência de caracteres em um arquivo
    mostrar conteúdo do arquivo

Etapa 1

Desenvolver a estrutura de acesso do servidor de arquivos. Ele deverá será acessado via socket TCP. Cada conexão deverá ser gerida por uma thread. Condições de corrida deverão ser tratadas por meio de semáforos ou mutexes. Nesta etapa você não precisa implementar as operações sobre arquivos listadas acima. Ao invés disso, use as operações diretamente do sistema de arquivos do seu sistema operacional. Recomenda-se que o servidor imprima mensagens na tela para demonstrar o funcionamento ao professor.

Observações:

    Não é necessário autenticação dos usuários.
    Não é necessário criar um aplicativo cliente. Você pode usar o aplicativo netcat disponível para Linux e Windows.
*/


/* verificar vetores char
 printf("valor de a: %s \t valor de msg: %s\n", (char*)a , (char*)msg);
        printf("valor de a: %d \t valor de msg: %d\n", a , msg);
        printf("tamanho de a: %d \t tamanho de msg %d\n",strlen(a), strlen(msg));
        for(int i=0; i<10;i++)
        {
            printf("%d: valor de a: %d, valor de msg %d\n",i,a[i],msg[i]);
        }
*/



/*

resposta para o cliente.

if(strcmp(msg, "ls"))
        {
            strcpy(resposta, "ls dir");
            system("ls >> saida.txt");
        }
          if(strcmp(msg, "exit"))
        {
            break;
        }



*/
/*
pedido trat_leitura(char* msg)
{
    pedido pedido1;
    char* arg1;
    char* arg2;
    int ultimo = strlen(msg);
    char * temp;
    msg[ultimo-1] = (char)NULL;
    printf("trat1 \n");
    //strcpy(pedido1.comando, strtok(msg, " "));
    arg1 = strtok(msg," ");
    arg2 = strtok(NULL, " ");
    strcpy(pedido1.comando, (char*)arg1);
    strcpy(pedido1.texto, (char*)arg2);
    
    printf("%s\n",pedido1.comando );
    printf("%s\n",pedido1.texto );

    printf("trat2 \n");
    //if( temp strtok(NULL, " ") != NULL)
      //  strcpy(pedido1.texto, strtok(NULL, " "));
    

    return pedido1;
}
*/
