#define MAX_CLIENTE_LISTA 100

typedef struct {
    int id;
    char *nome_completo;
} CLIENTE;

typedef struct {
    CLIENTE cliente[MAX_CLIENTE_LISTA];
    int pos_livre;
} LISTA_CLIENTE;

LISTA_CLIENTE * criaListaCliente()
{
    LISTA_CLIENTE * nova_lista = (LISTA_CLIENTE*) malloc(sizeof(LISTA_CLIENTE));
    nova_lista->pos_livre = 0;
    nova_lista->cliente[0].id = 0;
    return nova_lista;
}

CLIENTE registraCliente( LISTA_CLIENTE *l, int altera )
{
    char nome[255];

    CLIENTE cliente;
    int id;

    if ( altera == 0 ) {

        printf("Voce deseja inserir um id? caso nao, sera inserido automaticamente\n");
        printf("0 - Nao\n");
        printf("1 - Sim\n");

        char entrada;
        scanf("%c", &entrada);
        getchar();

        // Faz a inserção do id
        if ( entrada == '1' ) {
            printf("Insira um ID\n");
            scanf("%d", &id);
            getchar();
        } else {
            id = buscaUltimoId(l);
            id++;
        }

        cliente.id = id;
    }


    // Faz a inserção do nome
    printf("Insira o nome\n");
    gets(nome);
    cliente.nome_completo = (char*) malloc(sizeof(nome));
    strcpy(cliente.nome_completo, nome);

    return cliente;
}

void insereCliente( LISTA_CLIENTE *l )
{
    CLIENTE c;

    c = registraCliente(l, 0);

    push(l, c);
}

void alteraCliente( LISTA_CLIENTE *l )
{
    int id, pos;
    printf("Insira o ID do cliente que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();

    pos = foundById(l, id);

    if ( pos >= 0 ) {
        // Altera o cliente
        l->cliente[pos] = registraCliente(l, 1);
        l->cliente[pos].id = id;
    }
}

void removeCliente( LISTA_CLIENTE *l )
{
    if ( l->pos_livre == 0 ) {
        printf("Erro - Nao ha registro de pessoas.\n");
        return;
    }
    int id;
    printf("Insira o ID do cliente que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    if ( removeById(l, id) ) {
        printf("Cliente removido com sucesso.\n");
    } else {
        printf("Erro: cliente nao removido.\n");
    }
}

void imprimeClientes( LISTA_CLIENTE *l )
{
    if ( l->pos_livre == 0 ) {
        return;
    }
    
    printf("---------------------------------------- PESSOAS REGISTRADAS ----------------------------------------\n\n");

    int i;
    for ( i = 0; i < l->pos_livre; i++ ) {
        printf("ID %d\n", l->cliente[i].id);
        printf("Nome %s\n", l->cliente[i].nome_completo);
        printf("\n");
    }

    printf("\n");
    printf("\n");
}

void consultarCliente( LISTA_CLIENTE *l)
{
    int id;
    printf("Insira o ID do cliente que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    imprimeCliente(l, id);
}

void imprimeCliente( LISTA_CLIENTE *l, int id )
{
    int pos;
    pos = foundById(l, id);

    if ( pos >= 0 ) {
        printf("ID: %d\n", l->cliente[pos].id);
        printf("Nome completo: %s\n", l->cliente[pos].nome_completo);
    }
}

int removeById( LISTA_CLIENTE *l, int id )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int pos, i;
    pos = foundById(l, id);
    if ( pos >= 0 ) {

        // Percorre a lista de clientes
        for ( i = pos; i < l->pos_livre; i++ ) {
            l->cliente[i] = l->cliente[i+1];
        }
        l->pos_livre--;
        return 1;
    }
}

int foundById( LISTA_CLIENTE *l, int id)
{
    if ( l->pos_livre == 0 ) {
        printf("Erro - lista de clientes vazia.\n");
        return -1;
    }
    int pos = 0;

    while ( pos < l->pos_livre && id != l->cliente[pos].id)
        pos++;

    if ( pos == l->pos_livre ) {
        printf("Erro - cliente nao encontrado.\n");
        return -1;
    }

    return pos;
}

int buscaUltimoId( LISTA_CLIENTE *l )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int i, id = 0;
    for ( i = 0; i < l->pos_livre; i++ ) {
        if ( l->cliente[i].id > id )
            id = l->cliente[i].id;
    }

    return id;
}

int push( LISTA_CLIENTE *l, CLIENTE c )
{
    // Lista cheia
    if ( l->pos_livre >= MAX_CLIENTE_LISTA ) {
        return 0;

    // Adiciona cliente na lista e incrementa um na posicao livre da lista
    } else {
        l->cliente[l->pos_livre] = c;
        l->pos_livre += 1;

        return 1;
    }
}
