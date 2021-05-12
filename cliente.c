#define MAX_CLIENTE_LISTA 50
#define MAX_HISTORICO_LISTA 50

/**
 * Cria uma ponteiro para o tipo de estrutura LISTA_CLIENTE
 * 
 * @return LISTA_CLIENTE *
 **/
LISTA_CLIENTE * criaListaCliente()
{
    LISTA_CLIENTE * nova_lista = (LISTA_CLIENTE*) malloc(sizeof(LISTA_CLIENTE));
    nova_lista->pos_livre = 0;
    nova_lista->cliente[0].id = 0;
    return nova_lista;
}

/**
 *  Recebe os dados do teclado do usuario e insere na estrutura CLIENTE
 * 
 * @param LISTA_CLIENTE ponteiro para lista de clientes
 * @param altera indica para a funcao se o registro sera para alterar ou apenas inserir
 * 
 * @return CLIENTE retorna uma variavel do tipo struct CLIENTE
 **/
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

    // // Faz a inserção da quantidade de viagens
    // printf("Voce deseja inserir a quantidade de viagens?\n");
    // printf("0 - Nao\n");
    // printf("1 - Sim\n");
    // scanf("%c", &entrada);
    // getchar();

    // if ( entrada == '1' ) {
    //     printf("Insira a quantidade de viagens. (apenas digitos).\n");
    //     int qtd_viagem;
    //     scanf("%d", &qtd_viagem);
    //     getchar();
    //     cliente.qtd_viagem = qtd_viagem;
    // } else {
    //     cliente.qtd_viagem = 0;
    // }

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
            // if ( altera == 0 ) {
            //     cliente.historico_atual[i] = aux;
            // }
            i++;
        }
    } else if ( entrada == '0' ) {
        int x;
        for ( x = 0; x < 50; x++ ) {
            cliente.historico[x] = 0;
            // cliente.historico_atual[x] = 0;
        }
    }

    // Faz a inserção da quantidade de viagens
    printf("Voce deseja inserir a o historico atual de pedidos?\n");
    printf("0 - Nao\n");
    printf("1 - Sim\n");
    scanf("%c", &entrada);
    getchar();

    if ( entrada == '1' ) {
        int i = 0;
        int aux = 1;

        while ( aux != 0 ) {
            printf("Insira o ID do alimento a ser inserido no historico atual. (apenas digitos)\n");
            printf("Digite 0 para prosseguir com o cadastro.\n");
            scanf("%d", &aux);
            getchar();
            cliente.historico_atual[i] = aux;
            if ( altera == 0 ) {
                cliente.historico_atual[i] = aux;
            }
            i++;
        }

        // Seta como 0 o resto do array de historico atual
        for ( ; i < 50; i++ ) {
            cliente.historico_atual[i] = 0;
        }

    } else if ( entrada == '0' ) {
        int x;
        for ( x = 0; x < 50; x++ ) {
            cliente.historico_atual[x] = 0;
        }
    }

    // Faz a inserção da quantidade de viagens
    printf("Voce deseja inserir a o historico de viagens?\n");
    printf("0 - Nao\n");
    printf("1 - Sim\n");
    scanf("%c", &entrada);
    getchar();

    if ( entrada == '1' ) {
        int i = 0;
        int aux = 1;

        while ( aux != 0 ) {
            printf("Insira o ID da viagem a ser inserido no historico. (apenas digitos)\n");
            printf("Digite 0 para prosseguir com o cadastro.\n");
            scanf("%d", &aux);
            getchar();
            cliente.historico_viagem[i] = aux;
            i++;
        }

        // Seta como 0 o resto do array de historico atual
        for ( ; i < 50; i++ ) {
            cliente.historico_viagem[i] = 0;
        }

    } else if ( entrada == '0' ) {
        int x;
        for ( x = 0; x < 50; x++ ) {
            cliente.historico_viagem[x] = 0;
        }
    }

    return cliente;
}

/**
 * Insere um cliente e faz a validacao
 * 
 * @param LISTA_CLIENTE *l
 * @param FILE
 **/
void insereCliente( LISTA_CLIENTE *l, FILE * log, LISTA_ALIMENTO *la )
{
    CLIENTE c;

    c = registraCliente(l, 0);

    int res;
    res = validaCliente(c, la);

    if ( res == 0 ) {
        push(l, c);
    }
    if ( res == -1 ) {
        logErrorCliente(c.id, -1, log);
    }
    if ( res == -2 ) {
        logErrorCliente(c.id, -2, log);
    }
    if ( res == -3 ) {
        logErrorCliente(c.id, -3, log);
    }
    if ( res == -4 ) {
        logErrorCliente(c.id, -4, log);
    }
}

/**
 * Registra o ID pelo usuario e altera o cliente
 * 
 * @param LISTA_CLIENTE *l
 **/
void alteraCliente( LISTA_CLIENTE *l, FILE *log, LISTA_ALIMENTO *la )
{
    int id, pos;
    printf("Insira o ID do cliente que deseja alterar (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();

    pos = foundById(l, id);

    if ( pos >= 0 ) {
        CLIENTE c;
        c = registraCliente(l, 1);
        int res;
        res = validaCliente(c, la);
        if ( res == 0 ) {
            l->cliente[pos] = c;
            l->cliente[pos].id = id;
        }
        if ( res == -1 ) {
            logErrorCliente(c.id, -1, log);
        }
        if ( res == -2 ) {
            logErrorCliente(c.id, -2, log);
        }
        if ( res == -3 ) {
            logErrorCliente(c.id, -3, log);
        }
        if ( res == -4 ) {
            logErrorCliente(c.id, -4, log);
        }
    }
}

/**
 * Remove um cliente
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 **/
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

/**
 * Faz a impressao das informacoes basicas de todos os clientes na tela
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 **/
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

/**
 * Faz o registro pelo teclado do usuario para a impressao de um cliente
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 **/
void consultarCliente( LISTA_CLIENTE *l)
{
    int id;
    printf("Insira o ID do cliente que deseja consultar (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    imprimeCliente(l, id);
}

/**
 * Faz a impressao de todas informacoes de um determinado cliente, busca o cliente pelo id
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 * @param id inteiro que referencia o id do cliente que sera impresso
 **/
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
        printf("Historico de pedidos do cliente: ");
        while (l->cliente[pos].historico[i] != 0 ) {
            printf("%d ", l->cliente[pos].historico[i]);
            i++;
        }
        printf("\n");
        printf("Historico atual de pedidos do cliente: ");
        i = 0;
        while (l->cliente[pos].historico_atual[i] != 0 ) {
            printf("%d ", l->cliente[pos].historico_atual[i]);
            i++;
        }
        printf("\n");
        printf("Historico atual de viagens do cliente: ");
        i = 0;
        while (l->cliente[pos].historico_viagem[i] != 0 ) {
            printf("%d ", l->cliente[pos].historico_viagem[i]);
            i++;
        }
        printf("\n");
    } else {
        printf("Erro - Cliente nao encontrado.\n");
    }
}

/**
 * Remove um cliente dado o id do cliente
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 * @param id inteiro que refenrecia o id do cliente que sera removido
 * 
 * @return integer retorna 1 caso o cliente for removido com sucesso da lista
 **/
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

    return -1;
}

/**
 * Busca um cliente pelo id na lista de clientes
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 * @param id inteiro que referencia o id do usuario a ser procurado na lista
 * 
 * @return Retorna a posicao do cliente na lista de clientes
 **/
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

/**
 * Busca o id de maior numero na lista de clientes
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 * 
 * @return integer id buscado
 **/
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

/**
 * Insere um cliente no final da lista de clientes
 * 
 * @param LISTA_CLIENTE ponteiro para a lista de clientes
 * @param CLIENTE variavel do tipo cliente para ser inserida
 * 
 * @return Retorna 1 se foi inserido com sucesso
 **/
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

/**
 * Faz a validacao de um cliente
 * 
 * @param CLIENTE variavel do tipo estrutura CLIENTE
 * 
 * @return Retorna o valor do erro
 **/
int validaCliente( CLIENTE c, LISTA_ALIMENTO *la ) {
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
    if ( !validaHistoricoAtual(c, la) ) {
        return -4;
    }

    return (erro1 + erro2);
}

/**
 * Faz a validacao do id do cliente
 * 
 * @param CLIENTE variavel do tipo estrutura CLIENTE
 * 
 * @return Retorna 1 caso for valido
 **/
int validaId ( CLIENTE c ) {
    if ( c.id < 0 ) {
        return 0;
    }
    return 1;
}

/**
 * Faz a validacao da quantidade de viagens do cliente
 * 
 * @param CLIENTE variavel do tipo estrutura CLIENTE
 * 
 * @return Retorna 1 caso for valido
 **/
int validaViagem ( CLIENTE c ) {
    if ( c.qtd_viagem < 0 ) {
        return 0;
    }
    return 1;
}

/**
 * Faz a validacao da data inserida no cadastro do cliete
 * 
 * @param CLIENTE variavel do tipo estrutura CLIENTE
 * 
 * @return Retorna 1 caso for valido
 **/
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

/**
 * Faz a validacao do nome do cliente
 * 
 * @param CLIENTE variavel do tipo estrutura CLIENTE
 * 
 * @return Retorna 1 caso for valido
 **/
int validaNome ( CLIENTE c ) {
    if ( strcmp(c.nome_completo, "") == 0 ) {
        return 0;
    }
    return 1;
}

/**
 * Faz a validacao do historico atual de pedidos do cliente
 * 
 * @param CLIENTE variavel do tipo estrutura CLIENTE
 * 
 * @return Retorna 1 caso for valido
 **/
int validaHistoricoAtual ( CLIENTE c, LISTA_ALIMENTO *la ) {
    int i;
    for ( i = 0; i < 50 ; i++ ) {
        if ( c.historico_atual[i] != 0 && foundAlimentoById(la, c.historico_atual[i]) == -1 ) {
            // Id não existe
            return 0;
        }
    }

    // Id existe na lista
    return 1;
} 

/**
 * Faz o registro de erros dentro do arquivo de LOG
 * 
 * @param id ID que sera referenciado no registro do erro
 * @param error valor do erro que sera registrado
 * @param FILE ponteiro para a variavel que armazena o arquivo de log
 **/
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
    if ( error == -4 ) {
        fprintf(log, "Regra 3 desrepeitada, foi inserido um ID no historico de pedidos nao existente");
    }
    fprintf(log, "\n");
    fclose(log);
}