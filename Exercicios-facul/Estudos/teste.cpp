#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout.put('a'); //alternativa de cout para imprimir char
    cout << 'c';
    cout.put('abd'); //se colocarmos mais de um caractere (string) a função irá ler apenas o último caractere
    cout << "\n";
    cout << setw(10); //próximo linha começara numa largura de 10px
    cout.put('g');    //a função put ignora esses tipos de falha
    cout << "\n";
    cout.put('a').put('b').put('c').put('d').put('.').put('.').put('.'); //concatenação usando put
}