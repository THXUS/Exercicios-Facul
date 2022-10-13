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
    while (op != 's') // equanto o usuário não apertar s o bash não finaliza
    {

        switch (op)
        {
        case 'd': //data
        {
            int x = vfork();
            if (x == 0)
            {
                execlp("/bin/date", "date", NULL);
            }
            break;
        }

        case 'C': //calendário
        {
            int x = vfork();
            if (x == 0)
            {
                execlp("/usr/bin/cal", "cal", NULL);
            }
            break;
        }

        case 'l': //ls
        {
            int x = vfork();
            if (x == 0)
            {
                execlp("/bin/ls", "ls", "-h", NULL);
            }
            break;
        }
        case 'i': //ip access
        {
            int x = vfork();
            if (x == 0)
            {
                execlp("/bin/ip", "ip", "a", NULL);
            }
            break;
        }
        case 'c': //clear
        {
            int x = vfork();
            if (x == 0)
            {
                execlp("/usr/bin/clear", "clear", NULL);
            }
            break;
        }
        default:
            wait(NULL);
            break;
        }
        op = menu();
    }
    return 0;
}