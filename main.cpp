#include <iostream>
#include <cstdlib>

#include "cliente.h"

using namespace std;

typedef struct {
    Cliente model_cliente[50];
    int prox;
} LISTA;

LISTA* cria_lista_cliente() {
    LISTA *lista;
    lista = (LISTA *) malloc(sizeof(LISTA));
    lista->prox = 0;
    return lista;
}

void cliente(LISTA* l) {

    char entrada;

    while ( entrada != '0' ) {
        cout << "0 - Voltar" << "\n";
        cout << "1 - Consultar cliente" << "\n";
        cout << "2 - Inserir cliente" << "\n";
        cout << "3 - Alterar cliente" << "\n";
        cout << "4 - Remover cliente" << "\n";

        cin >> entrada;

        if ( entrada == '2' ) {
            l->model_cliente[l->prox].insereCliente();
            cout << l->model_cliente[l->prox].nome_cliente;
            l->prox++;
        }
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

    LISTA *l = NULL;
    l = cria_lista_cliente();

    while ( entrada != '0' ) {
        // Imprime o menu
        cout << "0 - Sair" << "\n";
        cout << "1 - Menu de clientes" << "\n";
        cout << "2 - Menu de alimentos" << "\n";

        // Recebe a entrada
        cin >> entrada;

        if ( entrada == '1' ) {
            cliente(l);
        }

        if ( entrada == '2' ) {
            alimento();
        }
    }

    free(l);

    return 1;
}