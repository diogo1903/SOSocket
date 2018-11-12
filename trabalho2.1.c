//trabalho2.1.c





#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
 #include <unistd.h>

// estrutura arquivos livres
// estrutura i-nodes
// estrutura arquivos
// criar o arquivo bin com truncate
// funcao de leitura do arquivo bin
// funcao de escrita do arquivo bin
// funcao de localizacao do aquivo desejado
// funcao de criacao de um arquivo desejado 
// funcao de diretorios 


int main()
{

    FILE *arquivo = fopen("arquivo","wb") // modo binario rb wb ab
    
    return 0;
}




/*
Etapa 2

Estenda o trabalho desenvolvendo a estrutura de alocação e organização 
de arquivos do servidor de arquivos. Mais precisamente, agora a 
aplicação servidor utilizará um arquivo em disco que simulará 
o sistema de arquivos EXT3. Dentro deste arquivo haverá no mínimo 
três regiões: uma região para o controle de espaço livre, 
uma região para armazenar inodes e uma região para armazenar 
dados de arquivos e diretórios. As operações devem ser implementadas 
usando o arquivo que simula o sistema de arquivos. Por exemplo, 
assuma que o arquivo que simula o sistema de arquivos se chama sa.bin 
e que um usuário quer criar um arquivo chamado teste.txt no servidor 
contendo os caracteres "abcd" (4 bytes). Então, dentro de sa.bin o 
servidor deve encontrar um inode livre, atribuir o nome teste.txt ao 
inode e associar um bloco livre de 4 bytes para conter "abcd". 
Ainda dentro de sa.bin, grava-se "abcd" no bloco livre associado e 
se deduz espaço utilizado para guardar "abcd" do espaço livre.

A thread no servidor deve receber uma solicitação do cliente e então repassá-la 
a um novo processo via pipe nomeado e este deverá executar a ação solicitada 
e devolver ao servidor uma mensagem de status, informando se a solicitação foi 
realizada com sucesso ou com erro.
*/
