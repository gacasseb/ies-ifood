#define MAX_CLIENTE_LISTA 100

typedef struct {
    int id;
    char *nome_completo;
    int dia, mes, ano;
    int qtd_viagem;
    int historico[50];
    int historico_atual[50];
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
    int d, m, a;
    char viagens[15];
    char historico[255];
    char historico_atual[255];
    char entrada;

    CLIENTE cliente;
    int id;

    if ( altera == 0 ) {

        printf("Voce deseja inserir um id? caso nao, sera inserido automaticamente\n");
        printf("0 - Nao\n");
        printf("1 - Sim\n");

        scanf("%c", &entrada);
        getchar();

        // Faz a inserção do id
        if ( entrada == '1' ) {

            printf("Insira um ID\n");
            scanf("%d", &id);
            getchar();
            while ( foundById(l, id) >= 0 ) {
                printf("Um cliente com este ID ja foi cadastrado, insira outro id.\n");
                scanf("%d", &id);
                getchar();
            }

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

    // Faz a inserção data de nascimento
    printf("Insira sua data de nascimento (dd/mm/aaaa)\n");
    scanf("%d/%d/%d", &d, &m, &a);
    getchar();
    cliente.dia = d;
    cliente.mes = m;
    cliente.ano = a;

    // Faz a inserção da quantidade de viagens
    printf("Voce deseja inserir a quantidade de viagens?\n");
    printf("0 - Nao\n");
    printf("1 - Sim\n");
    scanf("%c", &entrada);
    getchar();

    if ( entrada == '1' ) {
        printf("Insira a quantidade de viagens. (apenas digitos).\n");
        int qtd_viagem;
        scanf("%d", &qtd_viagem);
        getchar();
        cliente.qtd_viagem = qtd_viagem;
    } else {
        cliente.qtd_viagem = 0;
    }

    // Faz a inserção da quantidade de viagens
    printf("Voce deseja inserir a o historico de pedidos?\n");
    printf("0 - Nao\n");
    printf("1 - Sim\n");
    scanf("%c", &entrada);
    getchar();

    if ( entrada == '1' ) {
        int i = 0;
        int aux = 1;

        while ( aux != 0 ) {
            printf("Insira o ID do alimento a ser inserido no historico. (apenas digitos)\n");
            printf("Digite 0 para prosseguir com o cadastro.\n");
            scanf("%d", &aux);
            getchar();
            cliente.historico[i] = aux;
            if ( altera == 0 ) {
                cliente.historico_atual[i] = aux;
            }
            i++;
        }
    }

    return cliente;
}

void insereCliente( LISTA_CLIENTE *l, FILE * log )
{
    CLIENTE c;

    c = registraCliente(l, 0);

    if ( validaCliente(c) == 0 ) {
        push(l, c);
    }
    if ( validaCliente(c) == -1 ) {
        logErrorCliente(c.id, -1, log);
    }
    if ( validaCliente(c) == -2 ) {
        logErrorCliente(c.id, -2, log);
    }
    if ( validaCliente(c) == -3 ) {
        logErrorCliente(c.id, -3, log);
    }
}

void alteraCliente( LISTA_CLIENTE *l )
{
    int id, pos;
    printf("Insira o ID do cliente que deseja alterar (apenas com digitos)\n");
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
    printf("Insira o ID do cliente que deseja consultar (apenas com digitos)\n");
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
        printf("Data de nascimento: %d/%d/%d\n", l->cliente[pos].dia, l->cliente[pos].mes, l->cliente[pos].ano);
        if ( l->cliente[pos].qtd_viagem > 0 ) {
            printf("Quantidade de viagens: %d\n", l->cliente[pos].qtd_viagem);
        }
        int i = 0;
        printf("Historico do cliente: ");
        while (l->cliente[pos].historico[i] != 0 ) {
            printf("%d ", l->cliente[pos].historico[i]);
            i++;
        }
        printf("\n");
        printf("Historico atual do cliente: ");
        i = 0;
        while (l->cliente[pos].historico_atual[i] != 0 ) {
            printf("%d ", l->cliente[pos].historico_atual[i]);
            i++;
        }
        printf("\n");
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
        return -1;
    }
    int pos = 0;

    while ( pos < l->pos_livre && id != l->cliente[pos].id)
        pos++;

    if ( pos == l->pos_livre ) {
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

int validaCliente( CLIENTE c ) {
    int erro1 = 0;
    int erro2 = 0;

    if ( !validaId(c) ) {
        erro2 = -2;
    }
    if ( !validaViagem(c) ) {
        erro2 = -2;
    }
    if ( !validaData(c) ) {
        erro2 = -2;
    }
    if ( !validaNome(c) ) {
        erro1 = -1;
    }

    return (erro1 + erro2);
}

int validaId ( CLIENTE c ) {
    if ( c.id < 0 ) {
        return 0;
    }
    return 1;
}

int validaViagem ( CLIENTE c ) {
    if ( c.qtd_viagem < 0 ) {
        return 0;
    }
    return 1;
}

int validaData ( CLIENTE c ) {
    if ( c.dia > 31 || c.dia < 0) {
        return 0;
    }
    if ( c.mes > 12 || c.mes < 0) {
        return 0;
    }
    if ( c.ano < 1900 || c.ano > 2021) {
        return 0;
    }
    return 1;
}

int validaNome ( CLIENTE c ) {
    if ( strcmp(c.nome_completo, "") == 0 ) {
        return 0;
    }
    return 1;
}

void logErrorCliente( int id, int error, FILE * log ) {
    log = fopen("erros.txt", "a");

    fprintf(log, "Cliente do ID:%d nao registrado:\n", id);
    if ( error == -1 ) {
        fprintf(log, "Regra 1 desrespeitada\n");
    }
    if ( error == -2 ) {
        fprintf(log, "Regra 2 desrespeitada\n");
    }
    if ( error == -3 ) {
        fprintf(log, "Regras 1 e 2 desrespeitadas\n");
    }
    fprintf(log, "\n");
    fclose(log);
}