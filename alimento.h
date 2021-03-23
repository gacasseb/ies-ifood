#include <stdio.h>

#define MAX_ALIMENTO_LISTA 100

typedef struct {
    int id;
    float cal;
    float preco;
    char *marca;
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
    char nome_marca[255];

    ALIMENTO alimento;
    int id;
    float vcal, preco;

    // Faz a insercao do ID apenas se nao estiver na rotina de alteracao
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
            while ( foundAlimentoById(l, id) >= 0 ) {
                printf("Um alimento com este ID ja foi cadastrado, insira outro id.\n");
                scanf("%d", &id);
                getchar();
            }

        } else {
            id = buscaUltimoIdAlimento(l);
            id++;
        }

        alimento.id = id;
    }
    
    // Faz a inserçao do alimento
    printf("Insira o alimento\n");
    gets(nome_alimento);
    alimento.nome_alimento = (char*) malloc(sizeof(nome_alimento));
    strcpy(alimento.nome_alimento, nome_alimento);

    // Faz a inserçao do valor calorico
    printf("Insira o valor calorico\n");
    scanf("%f", &vcal);
    getchar();
    alimento.cal = vcal;

    // Faz a inserçao do preco
    printf("Insira o preco\n");
    scanf("%f", &preco);
    getchar();
    alimento.preco = preco;

    // Faz a inserçao da marca
    printf("Insira a marca\n");
    gets(nome_marca);
    alimento.marca = (char*) malloc(sizeof(nome_marca));
    strcpy(alimento.marca, nome_marca);

    return alimento;
}

void insereAlimento ( LISTA_ALIMENTO *l, FILE * log) {
    ALIMENTO a;

    a = registraAlimento(l, 0);
    
    if ( validaAlimento(a) == 0 ) {
        pushAlimento(l, a);
    }
    if ( validaAlimento(a) == -1 ) {
        logErrorAlimento(a.id, -1, log);
    }
    if ( validaAlimento(a) == -2 ) {
        logErrorAlimento(a.id, -2, log);
    }
    if ( validaAlimento(a) == -3 ) {
        logErrorAlimento(a.id, -3, log);
    }
    
}

void alteraAlimento( LISTA_ALIMENTO *l ) {
    int id, pos;
    printf("Insira o ID do alimento que deseja alterar (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();

    pos = foundById(l, id);
    
    if ( pos >= 0 ) {
        // Altera o alimento
        l->alimento[pos] = registraAlimento(l, 1);
        l->alimento[pos].id = id;
    }
}

void removeAlimento( LISTA_ALIMENTO *l, LISTA_CLIENTE *lc )
{
    if ( l->pos_livre == 0 ) {
        printf("Erro - Nao ha registro de alimentos.\n");
        return;
    }
    int id;
    printf("Insira o ID do alimento que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    if ( removeAlimentoById(l, id) ) {
        // Percorre todos os clientes
        int i;
        for ( i = 0; i < lc->pos_livre ; i++ ) {
            int aux[50], pos = -1, j = 0;
            // Procura se o historico do cliente contem o id do alimento removido
            while( lc->cliente[i].historico_atual[j] != 0 ) {
                if ( lc->cliente[i].historico_atual[j] == id ) {
                    pos = j;
                    break;
                }
                j++;
            }
            // Encontrou um ID
            if ( pos >= 0 ) {
                int k = pos;
                while ( lc->cliente[i].historico_atual[k] != 0 ) {
                    lc->cliente[i].historico_atual[k] = lc->cliente[i].historico_atual[k+1];
                    k++;
                }
            }

        }
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
        printf("ID: %d\n", l->alimento[i].id);
        printf("Nome: %s\n", l->alimento[i].nome_alimento);
        printf("\n");
    }

    printf("\n");
    printf("\n");
}

void consultarAlimento( LISTA_ALIMENTO *l )
{
    int id;
    printf("Insira o ID do alimento que deseja consultar (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    imprimeAlimento(l, id);
}

void imprimeAlimento( LISTA_ALIMENTO *l, int id )
{
    int pos;
    pos = foundAlimentoById(l, id);

    if ( pos >= 0 ) {
        printf("ID: %d\n", l->alimento[pos].id);
        printf("Alimento: %s\n", l->alimento[pos].nome_alimento);
        printf("Valor calorico: %.2f\n", l->alimento[pos].cal);
        printf("Preco: %.2f\n", l->alimento[pos].preco);
        printf("Marca: %s\n", l->alimento[pos].marca);
    } else {
        printf("Erro - Alimento nao encontrado.\n");
    }
}

int removeAlimentoById( LISTA_ALIMENTO *l, int id )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int pos, i;
    pos = foundAlimentoById(l, id);
    if ( pos >= 0 ) {

        // Percorre a lista de alimentos
        for ( i = pos; i < l->pos_livre; i++ ) {
            l->alimento[i] = l->alimento[i+1];
        }
        l->pos_livre--;
        return 1;
    } else {
        printf("Erro - Alimento nao encontrado.\n");
    }
}

int foundAlimentoById( LISTA_ALIMENTO *l, int id)
{
    if ( l->pos_livre == 0 ) {
        return -1;
    }
    int pos = 0;

    while ( pos < l->pos_livre && id != l->alimento[pos].id)
        pos++;

    if ( pos == l->pos_livre ) {
        return -1;
    }

    return pos;
}

int buscaUltimoIdAlimento( LISTA_ALIMENTO *l )
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

int pushAlimento( LISTA_ALIMENTO *l, ALIMENTO a )
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

int validaAlimento( ALIMENTO a ) {
    int erro1 = 0;
    int erro2 = 0;

    if ( !validaIdAlimento(a) ) {
        erro2 = -2;
    }
    if ( !validaCalAlimento(a) ) {
        erro2 = -2;
    }
    if ( !validaPrecoAlimento(a) ) {
        erro2 = -2;
    }
    if ( !validaNomeAlimento(a) ) {
        erro1 = -1;
    }

    return (erro1 + erro2);
}

int validaIdAlimento ( ALIMENTO a ) {
    if ( a.id < 0 ) {
        return 0;
    }
    return 1;
}

int validaCalAlimento ( ALIMENTO a ) {
    if ( a.cal < 0 ) {
        return 0;
    }
    return 1;
}

int validaPrecoAlimento ( ALIMENTO a ) {
    if ( a.preco < 0 ) {
        return 0;
    }
    return 1;
}

int validaNomeAlimento ( ALIMENTO a ) {
    if ( strcmp(a.nome_alimento, "") == 0) {
        return 0;
    }
    return 1;
}

int validaMarcaAlimento ( ALIMENTO a ) {
    if ( strcmp(a.marca, "\0") != 0 ) {
        return 0;
    }
    return 1;
}

void logErrorAlimento( int id, int error, FILE * log ) {
    log = fopen("erros.txt", "a");

    fprintf(log, "Alimento do ID:%d nao registrado:\n", id);
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