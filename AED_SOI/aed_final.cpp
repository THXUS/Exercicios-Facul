//Autor: Matheus Guilherme Souza Santana

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

char menu()
{
    char opcao;
    cout << "-> ";
    cin >> opcao;
    return opcao;
}

int main()
{
    char op;
    op = menu();
    while (op != 'e') //exit
    {
        //cout << "Processo Pai: " << getpid() << "\n";
        int x = vfork();
        if (x == 0)
        {
            //cout << "Processo Filho: " << getpid() << "\n";
            switch (op)
            {
            case 'd': //comando df
                execlp("/bin/df", "df", NULL);
                break;
            case 'i': //comando ip access
                execlp("/bin/ip", "ip", "a", NULL);
                break;
            case 'l': //comando ls
                execlp("/bin/ls", "ls", "-h", NULL);
                break;
            case 'c': //comando clear
                execlp("/usr/bin/clear", "clear", NULL);
                break;
            case 'p': //comando pwd
                execlp("/bin/pwd", "pwd", NULL);
                break;
            }
        }
        else
        {
            wait(NULL);
            //cout << "Processo pai: " << getpid() << "\n";
        }
        op = menu();
    }
    return 0;
}