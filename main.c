#include <stdio.h>

#include "cliente.h"

void cliente( LISTA_CLIENTE *l )
{
    char entrada = 'a';

    while ( entrada != '0' ) {

        printf("---------------------------------------- CLIENTE ----------------------------------------\n\n");

        // Imprime o menu
        printf("0 - Voltar\n");
        printf("1 - Consultar um cliente\n");
        printf("2 - Inserir um cliente\n");
        printf("3 - Alterar um cliente\n");
        printf("4 - Remover um cliente\n");
        printf("\n");

        scanf("%c", &entrada);
        getchar();

        if ( entrada == '1' ) {
            consultarCliente(l);
        }

        if ( entrada == '2' ) {
            insereCliente(l);
            imprimeClientes(l);
        }

        if ( entrada == '3' ) {
            alteraCliente(l);
            imprimeClientes(l);
        }

        if ( entrada == '4' ) {
            removeCliente(l);
            imprimeClientes(l);
        }
    }
}

void alimento()
{
    char entrada = 'a';

    while ( entrada != '0' ) {
        
        printf("---------------------------------------- ALIMENTO ----------------------------------------\n\n");

        // Imprime o menu
        printf("0 - Voltar\n");
        printf("1 - Consultar um alimento\n");
        printf("2 - Inserir um alimento\n");
        printf("3 - Alterar um alimento\n");
        printf("4 - Remover um alimento\n");
        printf("\n");

        scanf("%c", &entrada);
        getchar();
    }
}

int main()
{
    char entrada;
    LISTA_CLIENTE *l = NULL;
    l = criaListaCliente();

    while ( entrada != '0' ) {
        printf("---------------------------------------- MENU ----------------------------------------\n\n");

        // Imprime o menu
        printf("0 - Sair\n");
        printf("1 - Menu de clientes\n");
        printf("2 - Menu de alimentos\n");

        // Recebe a entrada
        scanf("%c", &entrada);
        getchar();

        if ( entrada == '1' ) {
            cliente(l);
        }
    }

    return 1;
}