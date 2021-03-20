#include <iostream>

#include "cliente.h"

using namespace std;

void cliente() {

    char entrada;

    while ( entrada != '0' ) {
        cout << "0 - Voltar" << "\n";
        cout << "1 - Consultar cliente" << "\n";
        cout << "2 - Inserir cliente" << "\n";
        cout << "3 - Alterar cliente" << "\n";
        cout << "4 - Remover cliente" << "\n";

        cin >> entrada;
    }
}

void alimento() {

    char entrada;

    while ( entrada != '0' ) {
        cout << "0 - Voltar" << "\n";
        cout << "1 - Consultar alimento" << "\n";
        cout << "2 - Inserir alimento" << "\n";
        cout << "3 - Alterar alimento" << "\n";
        cout << "4 - Remover alimento" << "\n";

        cin >> entrada;
    }
}

int main()
{
    char entrada;
    
    while ( entrada != '0' ) {
        // Imprime o menu
        cout << "0 - Sair" << "\n";
        cout << "1 - Menu de clientes" << "\n";
        cout << "2 - Menu de alimentos" << "\n";

        // Recebe a entrada
        cin >> entrada;

        if ( entrada == '1' ) {
            cliente();
        }

        if ( entrada == '2' ) {
            alimento();
        }
    }

    return 1;
}