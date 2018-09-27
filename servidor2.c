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

#define porta 5000


typedef struct pedido{
    char comando[16];
    char texto[64];
}pedido;



void limpar_pedido(pedido pedido1)
{   
    for(int i =0 ; i < 16; i++)
    pedido1.comando[i] = NULL;
    for(int j =0 ; j < 64 ; j++)
    pedido1.texto[j] = NULL;
}


pedido trat_leitura(char msg[80])
{
    pedido pedido1;
    int i = 0, teste = 0, j=0;
    int ultimo = strlen(msg);
    msg[ultimo-1] = NULL;
    
    char * pch;
    pch = strtok (msg," ");
    if(pch != NULL){
        strcpy(pedido1.comando, pch);
        pch = strtok (NULL, " ");
    }
      if(pch != NULL){
        strcpy(pedido1.texto, pch);
        pch = strtok (NULL, " ");
    }
    
    
    return pedido1;
}

void saidals(char* resposta)
{
    FILE *fp;
    char path[1035];
    char c;
    char total[10000];
    fp = popen("ls *", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        strcat(total,path);
    }
    pclose(fp);
    strcpy(resposta, total);
}

int main(int argc, char * argv[])
{
    

    int listenfd=0, connfd=0;
    struct sockaddr_in serv_addr;// é um estrutura do sockaddr
    struct sockaddr_in sock_cli; // é o socket do cliente 
    socklen_t sock_novo_len; 
    char sendBuff[1025];
    char resposta[1000000];
    
        

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
    serv_addr.sin_port = htons(porta); //porta do servidor 
// bind(s, name, namelen);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    // escuta 10 clientes 
    listen(listenfd,10);
    int testebug = 0;
    
    
    while(1)
    {
        char msg[80];
        pedido pedido1;
        sock_novo_len = sizeof(sock_cli);
        printf("aaaa");
        connfd = accept(listenfd, (struct sockaddr*)&sock_cli, &sock_novo_len);


        for(int i=0; i<= sizeof(msg);i++)
            msg[i] = NULL;
        printf("*****************************iniciando a while***************************************\n");
        
        printf("accept ok \n"); 

        strcpy(resposta,"ola bem vindo\n");
        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd, sendBuff,strlen(sendBuff)); 
               
        if(read(connfd, msg, sizeof(msg))<0)
        {
            printf("Error de leitura do socket\n");
            exit(0);
        }        
        printf("**********testando mensagem1*************\n");
        printf("mensagem: %s \n", msg);
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
        printf("texto:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));
        //limpar_pedido(pedido1);
        printf("**********testando mensagem2*************\n");
        printf("mensagem: %s \n", msg);
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
        printf("texto:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));
        pedido1 = trat_leitura(msg);
        printf("**********testando mensagem3*************\n");
        printf("mensagem: %s \n", msg);
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
        printf("texto:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));
    
       
        char temp[40];
        if(strcmp("crdir", pedido1.comando)==0){
            strcpy(resposta, "novo dir");
            strcpy(temp, "mkdir " );
            strcat(temp, pedido1.texto);
            system(temp);
        }else if(strcmp("rm", pedido1.comando)==0){
             strcpy(resposta, "deletado dir");
            strcpy(temp, "rm -r ");
            strcat(temp, pedido1.texto);
            system(temp);
        }else if(strcmp("sair", pedido1.comando)==0){
            strcpy(resposta, "saindo");
            
            close(connfd);
            //exit(1);
        }else if(strcmp("listar", pedido1.comando)==0){
            saidals(resposta);
        }else{
            printf("erro do if da conversa msg = %s  \n",msg );
            strcpy(resposta, "comando nao exite\n");
            testebug = 1;
        } 

        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd, sendBuff,strlen(sendBuff));
        
    }
    close(connfd);
}
