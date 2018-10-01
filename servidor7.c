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

pthread_mutex_t lock; // variavel do mutex

typedef struct pedido{ // estrutura do pedido
    char comando[16];
    char texto[64];
    char texto2[64];
}pedido;

void saidals(char* resposta){ // Mostra conteudo do diretorio
    printf("\n iniciando LS \n");
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
    printf("\n LS finalizado \n");
}

void saidaler(char* resposta, pedido pedido1){ // Le o conteudo do arquivo
    printf("\n iniciando leitura do arquivo \n");
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
    printf("\n leitura realizada \n");
}

pedido limpar_pedido(pedido pedido1){ // Limpa as strings do pedido
    for(int i =0 ; i < 16; i++)
    pedido1.comando[i] = 0;
    for(int j =0 ; j < 64 ; j++)
    pedido1.texto[j] = 0;
    for(int j =0 ; j < 64 ; j++)
    pedido1.texto2[j] = 0;
    printf("\n pedido limpo \n");
}

pedido trat_leitura(char msg[80]){ // Trata a leitura do buffer, e retorna uma variavel do tipo pedido
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
    printf("\n leitura tratada \n");
    return pedido1;
}

void *conexao(void *connfd){ // Função da thread
    int connfd2 = *(int*)connfd; // Faz o cast do valor recebido
    char msg[80];
    pedido pedido1;
    char resposta[1000];
    char sendBuff[1025];
    while(1){  //Inicia o loop
        pedido1 = limpar_pedido(pedido1);
        for(int i=0; i<  80;i++) // Limpa buffer de recebimento
            msg[i] = 0;
        for(int i=0; i< 1000 ;i++) // Limpa buffer de envio
            resposta[i] = 0;
        for(int i=0; i< 1025 ;i++) // Limpa buffer
            sendBuff[i] = 0;

        printf("accept ok \n");

        if(read(connfd2, msg, sizeof(msg))<0)
        {
            printf("Error de leitura do socket\n");
            exit(0);
        }

        pedido1 = trat_leitura(msg); // Converte buffer recebido em pedido

        printf("**********testando mensagem*************\n");
        printf("mensagem: %s \n", msg);
        printf("comando:%s tamanho :%d\n", pedido1.comando, strlen(pedido1.comando));
        printf("texto:%s tamanho :%d\n", pedido1.texto, strlen(pedido1.texto));
        printf("texto2:%s tamanho :%d\n", pedido1.texto2, strlen(pedido1.texto2));
        char temp[40];
        if(strcmp("crdir", pedido1.comando)==0){ //Verifica se comando é criar diretorio
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "novo dir"); //Valor a ser passado para o cliente
            strcpy(temp, "mkdir " );
            strcat(temp, pedido1.texto);
            system(temp); // executa operação no servidor
            pthread_mutex_unlock(&lock);  // Libera o mutex
            printf("diretorio criado\n");
        }else if(strcmp("rm", pedido1.comando)==0){ //Remove diretorio
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "deletado"); //Valor a ser passado para o cliente
            strcpy(temp, "rm -r ");
            strcat(temp, pedido1.texto);
            system(temp); // executa operação no servidor
            pthread_mutex_unlock(&lock);  // Libera o mutex
            printf("diretorio removido \n");
        }else if(strcmp("sair", pedido1.comando)==0){ // finaliza thread
            strcpy(resposta, "saindo"); //Valor a ser passado para o cliente
            printf("Encerrando conexao \n");
            free(connfd); // Libera conexao
            pthread_exit(NULL);
        }else if(strcmp("listar", pedido1.comando)==0){
            pthread_mutex_lock(&lock);  // Trava o mutex
            saidals(resposta);
            pthread_mutex_unlock(&lock);  // Libera o mutex
        }else if(strcmp("crarq", pedido1.comando)==0){ //cria arquivo
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "arquivo criado");  //Valor a ser passado para o cliente
            strcpy(temp, "touch " );
            strcat(temp, pedido1.texto);
            system(temp); // executa operação no servidor
            pthread_mutex_unlock(&lock);  // Libera o mutex
            printf("arquivo criado \n");
        }else if(strcmp("escrever", pedido1.comando)==0){ // escreve no arquivo
            pthread_mutex_lock(&lock);  // Trava o mutex
            strcpy(resposta, "escrito"); //Valor a ser passado para o cliente
            strcpy(temp, "echo \"" );
            strcat(temp, pedido1.texto);
            strcat(temp, "\" > ");
            strcat(temp, pedido1.texto2);
            system(temp); // executa operação no servidor
            pthread_mutex_unlock(&lock);  // Libera o mutex
            printf("escrito no arquivo \n");
        }else if(strcmp("ler", pedido1.comando)==0){ // le o conteudo do arquivo
            pthread_mutex_unlock(&lock);  // Libera o mutex
            saidaler(resposta, pedido1);
            pthread_mutex_unlock(&lock);  // Libera o mutex
            printf("leitura do arquivo realizada \n");
        }else if(strcmp("cd", pedido1.comando)==0){ // altera diretorio
            strcpy(resposta, "diretorio escolhido");  //Valor a ser passado para o cliente
            strcpy(temp, "cd " );
            strcat(temp, pedido1.texto);
            system(temp); // executa operação no servidor
        }else{ // comando não encontrado
            strcpy(resposta, "comando nao exite\n"); //Valor a ser passado para o cliente
        }

        snprintf(sendBuff, sizeof(sendBuff), "%s\n",(char*)&resposta );
        write(connfd2, sendBuff,strlen(sendBuff));
        //close(connfd2);
        printf("\n Reiciando o while \n");
    }
}


int main(int argc, char * argv[]){
    printf("\n iniciando o servidor \n");
    int listenfd=0, connfd=0, *novo_sock;
    struct sockaddr_in serv_addr;// Ã© um estrutura do sockaddr
    struct sockaddr_in sock_cli; // Ã© o socket do cliente

    socklen_t sock_novo_len;

    if( pthread_mutex_init(&lock, NULL) != 0){
      fprintf(stderr, "Erro ao criar mutex.\n");
      printf("\n Impossivel iniciar mutex, encerrando \n");
      exit(EXIT_FAILURE);
     }

    //listenfd recebe o indentificador, descritor de soccket  socket(domain, type, protocol
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
    //bind informa que o referido socket operara na porta definida por PORTA_SOCKET_SERVER
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // associa porta
    // escuta 10 clientes
    listen(listenfd,10); // Começa a escutar
    sock_novo_len = sizeof(sock_cli);
    printf("ouvindo\n");

    while(1)
    {
        printf("while ok \n");
        connfd = accept(listenfd, (struct sockaddr*)&sock_cli, &sock_novo_len); //aceita conexao
        printf("accept ok\n");
        pthread_t thread;
        novo_sock = malloc(1);
        *novo_sock = connfd;

        if( pthread_create( &thread , NULL ,  conexao , (void*) novo_sock) < 0 ) //cria a pthread
        {
            perror("could not create thread");
            return 1;
        }
        printf("\n thread criada \n");
        printf("reiciando while\n");
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
