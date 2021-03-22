#define MAX_ALIMENTO_LISTA 100

typedef struct {
    int id;
    char *nome_alimento;
} ALIMENTO;

typedef struct {
    ALIMENTO alimento[MAX_ALIMENTO_LISTA];
    int pos_livre;
} LISTA_ALIMENTO;

LISTA_ALIMENTO * criaListaAlimento() {
    LISTA_ALIMENTO * nova_lista = (LISTA_ALIMENTO*) malloc(sizeof(LISTA_ALIMENTO));
    nova_lista->pos_livre = 0;
    nova_lista->alimento[0].id = 0;
    return nova_lista;
}

ALIMENTO registraAlimento( LISTA_ALIMENTO *l, int altera ) {
    char nome_alimento[255];

    ALIMENTO alimento;
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

        alimento.id = id;

    // Faz a inserçao do alimento
    printf("Insira o alimento\n");
    gets(nome_alimento);
    alimento.nome_alimento = (char*) malloc(sizeof(nome_alimento));
    strcpy(alimento.nome_alimento, nome_alimento);

    return alimento;
    }
}

void insereAlimento ( LISTA_ALIMENTO *l ) {
    ALIMENTO a;

    a = registraAlimento(l, 0);

    push(l, a);
}

void alteraAlimento( LISTA_ALIMENTO *l ) {
    int id, pos;
    printf("Insira o ID do alimento que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();

    pos = foundById(l, id);
    
    if ( pos >= 0 ) {
        // Altera o alimento
        l->alimento[pos] = registraAlimento(l, 1);
        l->alimento[pos].id = id;
    }
}

void removeAlimetno( LISTA_ALIMENTO *l )
{
    if ( l->pos_livre == 0 ) {
        printf("Erro - Nao ha registro de alimentos.\n");
        return;
    }
    int id;
    printf("Insira o ID do alimento que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    if ( removeById(l, id) ) {
        printf("Alimento removido com sucesso.\n");
    } else {
        printf("Erro: alimento nao removido.\n");
    }
}

void imprimeAlimentos( LISTA_ALIMENTO *l )
{
    if ( l->pos_livre == 0 ) {
        return;
    }
    
    printf("---------------------------------------- ALIMENTOS REGISTRADOS ----------------------------------------\n\n");

    int i;
    for ( i = 0; i < l->pos_livre; i++ ) {
        printf("ID %d\n", l->alimento[i].id);
        printf("Alimento %s\n", l->alimento[i].nome_completo);
        printf("\n");
    }

    printf("\n");
    printf("\n");
}

void cosultarAlimento( LISTA_ALIMENTO *l)
{
    int id;
    printf("Insira o ID do alimento que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    imprimeAlimento(l, id);
}

void imprimeAlimento( LISTA_ALIMENTO *l, int id )
{
    int pos;
    pos = foundById(l, id);

    if ( pos >= 0 ) {
        printf("ID: %d\n", l->alimento[pos].id);
        printf("Alimento: %s\n", l->alimento[pos].nome_alimento);
    }
}

int removeById( LISTA_ALIMENTO *l, int id )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int pos, i;
    pos = foundById(l, id);
    if ( pos >= 0 ) {

        // Percorre a lista de alimentos
        for ( i = pos; i < l->pos_livre; i++ ) {
            l->alimento[i] = l->alimento[i+1];
        }
        l->pos_livre--;
        return 1;
    }
}

int foundById( LISTA_ALIMENTO *l, int id)
{
    if ( l->pos_livre == 0 ) {
        printf("Erro - lista de alimentos vazia.\n");
        return -1;
    }
    int pos = 0;

    while ( pos < l->pos_livre && id != l->alimento[pos].id)
        pos++;

    if ( pos == l->pos_livre ) {
        printf("Erro - alimento nao encontrado.\n");
        return -1;
    }

    return pos;
}

int buscaUltimoId( LISTA_ALIMENTO *l )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int i, id = 0;
    for ( i = 0; i < l->pos_livre; i++ ) {
        if ( l->alimento[i].id > id )
            id = l->alimento[i].id;
    }

    return id;
}

int push( LISTA_ALIMENTO *l, ALIMENTO a )
{
    // Lista cheia
    if ( l->pos_livre >= MAX_ALIMENTO_LISTA ) {
        return 0;

    // Adiciona alimento na lista e incrementa um na posicao livre da lista
    } else {
        l->alimento[l->pos_livre] = a;
        l->pos_livre += 1;

        return 1;
    }
}