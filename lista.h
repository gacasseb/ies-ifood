#include <cstdlib>

#include "cliente.h"

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