
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 33331

#define TAMANHO_LIMITE_PARAMETRO 100

#define BYTES_INICIAL_RESPOSTA 58 * sizeof(char)

int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char tamanho_da_resposta[3];
  
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

        char *char_aux = malloc(sizeof(char));
            
        char *cabecalho_da_resposta = malloc(BYTES_INICIAL_RESPOSTA);

        char *parametro =  malloc(100 * sizeof(char));

        
        for (int i = 0; i < TAMANHO_LIMITE_PARAMETRO; i++) 
        {
            if(buffer[5+i] == ' ' || i >= TAMANHO_LIMITE_PARAMETRO) break;
            *char_aux = buffer[5+i];
            strcat(parametro, char_aux);
        }

        //  criando a variável ponteiro para o arquivo
        FILE *pont_arq;
        
          //abrindo o arquivo
        pont_arq = fopen(&parametro[0], "a+");

        fputs(parametro, pont_arq);

        fseek(pont_arq, 0, SEEK_END);

        int tamanho = ftell(pont_arq);

        rewind(pont_arq);

        char *resposta = malloc(sizeof(char) * (tamanho + 1));

        fread(resposta, sizeof(char), tamanho, pont_arq);

        resposta[tamanho] = '\0';

        fclose(pont_arq);

        strcpy(cabecalho_da_resposta, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: ");

        sprintf(tamanho_da_resposta, "%ld", strlen(resposta));

        strcat(tamanho_da_resposta, "\n");

        cabecalho_da_resposta = realloc(cabecalho_da_resposta, BYTES_INICIAL_RESPOSTA +  3 + strlen(resposta) * sizeof(char));


        strcat(cabecalho_da_resposta, tamanho_da_resposta);

        strcat(cabecalho_da_resposta, "\n");
        //TODO VERIFICAR PQ O TEXTO QUEBRA DPS DO PRIMEIRO ENVIO
        strcat(cabecalho_da_resposta, resposta);

        printf("Cabecalho de Resposta: %s\n", cabecalho_da_resposta);

        write(new_socket , cabecalho_da_resposta , strlen(cabecalho_da_resposta));
        printf("Resposta Enviada");
        close(new_socket);
        free(cabecalho_da_resposta);
        free(resposta);
        free(parametro);
    }
    return 0;
}