#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cliente.h"
#include "alimento.h"
#include "viagem.h"

#include "cliente.c"

void cliente( LISTA_CLIENTE *l, FILE * log, LISTA_ALIMENTO *la )
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
            imprimeClientes(l);
            consultarCliente(l);
        }

        if ( entrada == '2' ) {
            insereCliente(l, log, la);
            imprimeClientes(l);
        }

        if ( entrada == '3' ) {
            alteraCliente(l, log, la);
            imprimeClientes(l);
        }

        if ( entrada == '4' ) {
            removeCliente(l);
            imprimeClientes(l);
        }
    }
}

void alimento( LISTA_ALIMENTO *l, FILE * log, LISTA_CLIENTE *lc)
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

        if ( entrada == '1' ) {
            imprimeAlimentos(l);
            consultarAlimento(l);
        }

        if ( entrada == '2' ) {
            insereAlimento(l, log);
            imprimeAlimentos(l);
        }

        if ( entrada == '3' ) {
            alteraAlimento(l);
            imprimeAlimentos(l);
        }

        if ( entrada == '4' ) {
            removeAlimento(l, lc);
            imprimeAlimentos(l);
        }
    }
}

void viagem( LISTA_VIAGEM *l, FILE * log )
{
    char entrada = 'a';

    while ( entrada != '0' ) {

        printf("---------------------------------------- VIAGEM ----------------------------------------\n\n");

        // Imprime o menu
        printf("0 - Voltar\n");
        printf("1 - Consultar uma viagem\n");
        printf("2 - Inserir uma viagem\n");
        printf("3 - Alterar uma viagem\n");
        printf("4 - Remover uma viagem\n");
        printf("\n");

        scanf("%c", &entrada);
        getchar();

        if ( entrada == '1' ) {
            imprimeViagens(l);
            consultarViagem(l);
        }

        if ( entrada == '2' ) {
            insereViagem(l, log);
            imprimeViagens(l);
        }

        if ( entrada == '3' ) {
            imprimeViagens(l);
            alteraViagem(l);
            imprimeViagens(l);
        }
        
        if ( entrada == '4' ) {
            imprimeViagens(l);
            removeViagem(l);
            imprimeViagens(l);
        }
    }
}

int main()
{
    char entrada;
    LISTA_CLIENTE *l = NULL;
    LISTA_ALIMENTO *la = NULL;
    LISTA_VIAGEM *lv = NULL;
    la = criaListaAlimento();
    l = criaListaCliente();
    lv = criaListaViagem();

    FILE * log;
    log = fopen("erros.txt", "w");
    fclose(log);

    while ( entrada != '0' ) {
        printf("---------------------------------------- MENU ----------------------------------------\n\n");

        // Imprime o menu
        printf("0 - Sair\n");
        printf("1 - Menu de clientes\n");
        printf("2 - Menu de alimentos\n");
        printf("3 - Menu de viagens\n");

        // Recebe a entrada
        scanf("%c", &entrada);
        getchar();

        if ( entrada == '1' ) {
            cliente(l, log, la);
        }
        if ( entrada == '2' ) {
            alimento(la, log, l);
        }
        if ( entrada == '3' ) {
            viagem(lv, log);
        }
    }

    return 1;
}
