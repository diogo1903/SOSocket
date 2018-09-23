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

void trat_leitura(char* msg)
{
    char arg1[16], arg2[1008];
    int ultimo = strlen(msg);
    msg[ultimo-1] = (char)NULL;

}

int main(int argc, char * argv[])
{
    /*typedef struct comando{
        char[16] comando;
        char[1008] texto ;
    }comando;*/

    int listenfd=0, connfd=0;
    struct sockaddr_in serv_addr;// é um estrutura do sockaddr
    struct sockaddr_in sock_cli; // é o socket do cliente 
    socklen_t sock_novo_len; 
    char sendBuff[1025];
    char resposta[512];
    //time_t ticks; // time.h
    char msg[1025] ="2";
    char comando[16];
    char a[10] = "a";
    int terminar;

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
    serv_addr.sin_port = htons(5000); //porta do servidor 
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
        strcpy(resposta,"ola\n martin eh bumdao\n");
        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd, sendBuff,strlen(sendBuff)); 
        
        //leitura 
        if(read(connfd, msg, sizeof(msg))<0)
        {
            printf("Error de leitura do socket\n");
            exit(0);
        }
        trat_leitura(msg);
        printf("read ok, mensagem: %s \n", msg);
        strcpy(comando,msg);
        
        if(strcmp("crdir", (char*)comando)==0)
        {
            strcpy(resposta, "novo dir");
            system("mkdir oiii");
        }
        else if(strcmp("rm", (char*)comando)==0)
        {
            strcpy(resposta, "removido dir");
            system("rm -rf oiii");
        }
        else
        {
            printf("erro do if da conversa msg = %s  \n",msg );
            strcpy(resposta, "ERROR");
            testebug = 1;
        } 

       
        
        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd, sendBuff,strlen(sendBuff));
        close(connfd);
        printf("terminar?\n");
        scanf("%d", &terminar);
        if(terminar ==1)
            exit(0);
        
       
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
