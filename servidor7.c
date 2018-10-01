#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define porta 5001

pthread_mutex_t lock;

typedef struct pedido{
    char comando[16];
    char texto[64];
    char texto2[64];
}pedido;

void saidals(char* resposta)
{
    FILE *fp;
    char path[1035];
    char c;
    char total[10000];
    for(int i=0; i < 1035;i++)
        path[i] = 0;

    for(int i=0; i < 10000;i++)
        total[i] = 0;

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

void saidaler(char* resposta, pedido pedido1)
{
    printf("\ndegub 0\n");
    FILE *fp;
    char path[1035];
    char c;
    char total[10000];
    char temp2[8000];
    printf("\ndegub 1\n");
    strcat(temp2, "cat ");
    strcat(temp2, pedido1.texto);
    //strcpy(temp2, "cat teste.txt");
    printf("\ndegub 2\n");
    fp = popen(temp2, "r");
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

pedido limpar_pedido(pedido pedido1)
{
    for(int i =0 ; i < 16; i++)
    pedido1.comando[i] = 0;
    for(int j =0 ; j < 64 ; j++)
    pedido1.texto[j] = 0;
    for(int j =0 ; j < 64 ; j++)
    pedido1.texto2[j] = 0;
}

pedido trat_leitura(char msg[80])
{
    pedido pedido1;
    int i = 0, teste = 0, j=0;
    int ultimo = strlen(msg);
    msg[ultimo-1] = 0;

    char *pch;
    pch = strtok (msg," ");
    if(pch != NULL){
        strcpy(pedido1.comando, pch);
        pch = strtok (NULL, " ");
    }if(pch != NULL){
        strcpy(pedido1.texto, pch);
        pch = strtok (NULL, " ");
    }if(pch != NULL){
        strcpy(pedido1.texto2, pch);
        pch = strtok (NULL, " ");
    }
    return pedido1;
}

void *conexao(void *connfd)
{
    int connfd2 = *(int*)connfd;
    char msg[80];
    pedido pedido1;
    char resposta[1000];
    char sendBuff[1025];
    while(1)
    {
        //apaga mensagem
        pedido1 = limpar_pedido(pedido1);
        for(int i=0; i<  80;i++)
            msg[i] = 0;
        for(int i=0; i< 1000 ;i++)
            resposta[i] = 0;
        for(int i=0; i< 1025 ;i++)
            sendBuff[i] = 0;

        printf("accept ok \n");

        if(read(connfd2, msg, sizeof(msg))<0)
        {
            printf("Error de leitura do socket\n");
            exit(0);
        }

        pedido1 = trat_leitura(msg);

        printf("**********testando mensagem*************\n");
        printf("mensagem: %s \n", msg);
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
        printf("texto:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));
        printf("texto2:%s tamanho :%d\n", pedido1.texto2, strlen(pedido1.texto2));
        char temp[40];
        if(strcmp("crdir", pedido1.comando)==0){
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "novo dir");
            strcpy(temp, "mkdir " );
            strcat(temp, pedido1.texto);
            system(temp);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("rm", pedido1.comando)==0){
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "deletado");
            strcpy(temp, "rm -r ");
            strcat(temp, pedido1.texto);
            system(temp);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("sair", pedido1.comando)==0){
            strcpy(resposta, "saindo");
            //close(connfd2);
            //return 0;
            pthread_exit(NULL);
        }else if(strcmp("listar", pedido1.comando)==0){
            pthread_mutex_lock(&lock);  // Trava o mutex
            saidals(resposta);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("crarq", pedido1.comando)==0){
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "arquivo criado");
            strcpy(temp, "touch " );
            strcat(temp, pedido1.texto);
            system(temp);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("escrever", pedido1.comando)==0){
            pthread_mutex_unlock(&lock);  // Libera o mutex
            strcpy(resposta, "escrito");
            strcpy(temp, "echo \"" );
            strcat(temp, pedido1.texto);
            strcat(temp, "\" > ");
            strcat(temp, pedido1.texto2);
            system(temp);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("ler", pedido1.comando)==0){
            pthread_mutex_unlock(&lock);  // Libera o mutex
            saidaler(resposta, pedido1);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("cd", pedido1.comando)==0){
            strcpy(resposta, "diretorio escolhido");
            strcpy(temp, "cd " );
            strcat(temp, pedido1.texto);
            system(temp);
        }else{
            strcpy(resposta, "comando nao exite\n");
        }

        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd2, sendBuff,strlen(sendBuff));
        //close(connfd2);
    }
    free(connfd);
    return 0;
}



int main(int argc, char * argv[])
{
    int listenfd=0, connfd=0, *novo_sock;
    struct sockaddr_in serv_addr;// Ã© um estrutura do sockaddr
    struct sockaddr_in sock_cli; // Ã© o socket do cliente

    socklen_t sock_novo_len;

    if( pthread_mutex_init(&lock, NULL) != 0){
      fprintf(stderr, "Erro ao criar mutex.\n");
      exit(EXIT_FAILURE);
     }

// listenfd recebe o indentificador, descritor de soccket  socket(domain, type, protocol
    listenfd = socket(AF_INET, SOCK_STREAM,0);
// memset prenche uma variavel por um valor
    memset(&serv_addr, '0', sizeof(serv_addr));
    // printf(" serv _aadrs: %s \n",&serv_addr);
   // memset(sendBuff, '0', sizeof(sendBuff));
    //printf(" serv _aadrs: %s \n",&sendBuff);
// atribuo valores para a estrutura socket serv_affr
    serv_addr.sin_family = AF_INET; // tipo de conexao
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);// nao sei
    serv_addr.sin_port = htons(porta); //porta do servidor
// bind(s, name, namelen);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    // escuta 10 clientes
    listen(listenfd,10);
    sock_novo_len = sizeof(sock_cli);
    printf("ouvindo\n");

    while(1)
    {
        printf("while ok \n");
        connfd = accept(listenfd, (struct sockaddr*)&sock_cli, &sock_novo_len);
        printf("accept ok\n");
        pthread_t thread;
        novo_sock = malloc(1);
        *novo_sock = connfd;

        if( pthread_create( &thread , NULL ,  conexao , (void*) novo_sock) < 0 )
        {
            perror("could not create thread");
            return 1;
        }

    printf("fimmm\n");
    }
    pthread_mutex_destroy(&lock);
}
