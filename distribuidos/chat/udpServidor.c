#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>


#define negrito "\033[1m"
#define amarelo "\x1B[33m"
#define branco  "\x1B[37m"



int main(int argc, char *argv[]) 
{ 

    int sock, length, fromlen, n; 
    struct sockaddr_in server;//endereco do servidor 
    struct sockaddr_in from;//endereco do destino 
    char entrada[256]; //mensagem recebida do cliente
    char saida[1024]; 

    if (argc < 2) { 
        fprintf(stderr, "\nERRO: porta n�o informada! \nDigite: ./udpserver <porta>\n\n"); 
        exit(0); 
   		 } 


//cria o socket

    sock=socket(PF_INET, SOCK_DGRAM, 0); 
    if (sock < 0){ 
        printf("Erro em socket()"); 
        exit(0);}

//define as estruturas de end para socket   
    length = sizeof(server); // tamanho do end
    bzero(&server,length); 
//elimina espacos nulos da struct de end
    server.sin_family=AF_INET;// define a familia de protocolos 
    server.sin_addr.s_addr=INADDR_ANY; 
//associa ao end local
    server.sin_port=htons(atoi(argv[1])); 
//porta forneciada pelo usuario

//associa end ao socket

    if (bind(sock,(struct sockaddr *)&server,length)<0) 
        { printf("Erro em bind ()");
          close (sock);
          exit(0);}
   
   fromlen = sizeof(struct sockaddr_in);

   printf("\n%sServidor iniciado, aguardando msgs dos clientes...\n",negrito); 

//faz leitura
    while (1) {
        bzero(entrada,256); 
        n = recvfrom(sock,entrada,256,0,(struct sockaddr *)&from,&fromlen); 
        if (n < 0) 
            {printf(" Erro em recvfrom()"); 
             close(sock);
             exit(0);}

       printf("\nMensagem: %s", amarelo);
       printf("%s", entrada);
       printf("%s", branco);
       printf("\nRecebida de: %s   Porta: %d\n",inet_ntoa(from.sin_addr), ntohs(from.sin_port));

        char str []="sair";
        while (strncmp(str,entrada,4) == 0)
           {close(sock);
            exit(0);}       



        printf("\n%sDigite a Mensagem de Resposta: ", negrito);
        bzero(saida, 1024);
        fgets(saida,1024,stdin);
        //envia resposta
            n = sendto(sock,saida,256,0,(struct sockaddr *)&from,fromlen);
            if (n < 0){ 
                    printf("sendto");
                    close (sock);
                    exit(0);}

            printf("\n%sAguardando msgs dos clientes...\n", negrito);
    } 

}