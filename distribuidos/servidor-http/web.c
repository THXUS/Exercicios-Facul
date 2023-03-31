
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 33333
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char resposta[5];
    char chr;
    
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 15\n\nAULA DE CMP1190";
  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind()");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\nServidor Iniciado\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept()");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer);


        char uri[10];

        for (int i = 0; i < 5; i++) {
            uri[i] = buffer[5+i];
        }

         // criando a variável ponteiro para o arquivo
        FILE *pont_arq;
        
          //abrindo o arquivo
        pont_arq = fopen(uri, "a");

        for (int i = 0; i < 5; i++) {
            fputc(uri[i], pont_arq);
        }

        int indiceResposta = 0;

        do {
            chr = fgetc(pont_arq);
            resposta[indiceResposta] = chr;
        } while(chr != EOF);

        fclose(pont_arq);

        printf("TESTEEE %s\n", resposta);

        //TODO fazer a parte do anexo
        write(new_socket , hello , strlen(hello));
        printf("Resposta Enviada");
        close(new_socket);
    }
    return 0;
}