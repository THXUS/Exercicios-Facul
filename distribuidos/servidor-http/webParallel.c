
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <resolv.h>
#include <arpa/inet.h>


#define PORT 33333

/*
   comando para ver os ppids
   ps  xao pid,ppid,pgid,sid,comm | tail
*/

void Child(void* arg)
{   
        char buffer[30000] = {0};

        int client = *(int *) arg;

        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 15\n\nAULA DE CMP1190";

        long valread = read( client , buffer, 30000);
        write(client , hello , strlen(hello));
        printf("Resposta Enviada\n");
        close(client);
        // exit(0);
}


void sig_handler(int sig)
{
    if ( sig == SIGCHLD )
    {   int retval;
        wait(&retval);
    }
}


int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
	struct sigaction act;
    struct sockaddr_in address;
    int addrlen = sizeof(address);


    bzero(&act, sizeof(act));
    act.sa_handler = sig_handler;
    act.sa_flags = SA_NOCLDSTOP;
    sigaction(SIGCHLD, &act, 0);
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind()");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 20) != 0)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        int client, addr_size = sizeof(address);
        printf("\nServidor Iniciado\n\n");

        client = accept(server_fd, (struct sockaddr *)&address, &addr_size);
        
        if (client < 0)
        {
            printf("Codigo do Erro: %d\n",client);
            perror("accept()");
        } 
        else 
        {
            printf("Conectado por: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
            if (fork()) {
                close(client);
            } 
            else 
            {
                Child(&client);
                // exit(0);
            }
        }

    }
    return 0;
}