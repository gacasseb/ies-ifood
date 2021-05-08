#include <stdio.h>

#define MAX_VIAGEM_LISTA 100

typedef struct {
    int id;
    float origem_lat;
    float origem_longit;
    float destino_lat;
    float destino_longit;
    float preco;
} VIAGEM;

typedef struct {
    VIAGEM viagem[MAX_ALIMENTO_LISTA];
    int pos_livre;
} LISTA_VIAGEM;

/**
 * Cria uma ponteiro para o tipo de estrutura LISTA_VIAGEM
 * 
 * @return LISTA_VIAGEM *
 **/
LISTA_VIAGEM * criaListaViagem() {
    LISTA_VIAGEM * nova_lista = (LISTA_VIAGEM*) malloc(sizeof(LISTA_VIAGEM));
    nova_lista->pos_livre = 0;
    nova_lista->viagem[0].id = 0;
    return nova_lista;
}

/**
 *  Recebe os dados do teclado do usuario e insere na estrutura ALIMENTO
 * 
 * @param LISTA_ALIMENTO ponteiro para lista de alimentos
 * @param altera indica para a funcao se o registro sera para alterar ou apenas inserir
 * 
 * @return ALIMENTO retorna uma variavel do tipo struct ALIMENTO
 **/
VIAGEM registraViagem( LISTA_ALIMENTO *l, int altera ) {
    VIAGEM viagem;
    int id;
    float origem_lat, origem_longit, destino_lat, destino_longit, preco;

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
            while ( foundViagemById(l, id) >= 0 ) {
                printf("Um alimento com este ID ja foi cadastrado, insira outro id.\n");
                scanf("%d", &id);
                getchar();
            }

        } else {
            id = buscaUltimoIdViagem(l);
            id++;
        }

        viagem.id = id;
    }
    
    printf("Local de origem\nInsira a latitude do local de origem\n");
    scanf("%f", &origem_lat);
    getchar();
    viagem.origem_lat = origem_lat;

    printf("Insira a longitude do local de origem\n");
    scanf("%f", &origem_longit);
    getchar();
    viagem.origem_longit = origem_longit;

    printf("Local de destino\nInsira a latitude do local de destino\n");
    scanf("%f", &destino_lat);
    getchar();
    viagem.destino_lat = destino_lat;

    printf("Insira a longitude do local de destino\n");
    scanf("%f", &destino_longit);
    getchar();
    viagem.destino_longit = destino_longit;

    printf("Insira o preco da viagem.\n");
    scanf("%f", &preco);
    getchar();
    viagem.preco = preco;

    return viagem;
}

/**
 * Faz o registro pelo teclado do usuario para a impressao de um alimento
 * 
 * @param LISTA_ALIMENTO ponteiro para a lista de alimentos
 **/
void consultarViagem( LISTA_VIAGEM *l )
{
    int id;
    printf("Insira o ID da viagem que deseja consultar (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();
    imprimeViagem(l, id);
}

/**
 * Insere um alimento e faz a validacao
 * 
 * @param LISTA_ALIMENTO *l
 * @param FILE
 **/
void insereViagem ( LISTA_VIAGEM *l, FILE * log) {
    VIAGEM v;

    v = registraViagem(l, 0);

    pushViagem(l, v);
    
    // if ( validaAlimento(v) == 0 ) {
    //     pushAlimento(l, v);
    // }
    // if ( validaAlimento(v) == -1 ) {
    //     logErrorAlimento(v.id, -1, log);
    // }
    // if ( validaAlimento(v) == -2 ) {
    //     logErrorAlimento(v.id, -2, log);
    // }
    // if ( validaAlimento(v) == -3 ) {
    //     logErrorAlimento(v.id, -3, log);
    // }
}

/**
 * @param LISTA_VIAGEM *l
 **/
void alteraViagem( LISTA_VIAGEM *l ) {
    int id, pos;
    printf("Insira o ID da viagem que deseja alterar (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();

    pos = foundViagemById(l, id);
    
    if ( pos >= 0 ) {
        l->viagem[pos] = registraViagem(l, 1);
        l->viagem[pos].id = id;
    }
}

/**
* Registra o id da viagem que será removida da lsita
*
*   @param LISTA_VIAGEM ponteiro para a lista de viagem
**/
void removeViagem( LISTA_VIAGEM *l )
{
    if ( l->pos_livre == 0 ) {
        printf("Erro - Nao ha registro de alimentos.\n");
        return;
    }
    int id;
    printf("Insira o ID do alimento que deseja remover (apenas com digitos)\n");
    scanf("%d", &id);
    getchar();

    if ( removeViagemById(l, id) ) {
        printf("Viagem removida com sucesso.\n");
    } else {
        printf("Erro: viagem nao removida.\n");
    }
}

/**
 * Remove uma viagem dado o id da viagem
 * 
 * @param LISTA_VIAGEM ponteiro para a lista de viagens
 * @param id inteiro que refenrecia o id da viagem que sera removida
 * 
 * @return integer retorna 1 casa viagem for removida com sucesso da lista
 **/
int removeViagemById( LISTA_VIAGEM *l, int id )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int pos, i;
    pos = foundViagemById(l, id);
    if ( pos >= 0 ) {

        // Percorre a lista de alimentos
        for ( i = pos; i < l->pos_livre; i++ ) {
            l->viagem[i] = l->viagem[i+1];
        }
        l->pos_livre--;
        return 1;
    } else {
        printf("Erro - Viagem nao encontrada.\n");
    }
}

/**
 * Faz a impressao de todas informacoes de uma determinada viagem, busca a viagem pelo id
 * 
 * @param LISTA_VIAGEM ponteiro para a lista de viagens
 * @param id inteiro que referencia o id da viagem que sera impressa
 **/
void imprimeViagem( LISTA_VIAGEM *l, int id )
{
    int pos;
    pos = foundViagemById(l, id);

    if ( pos >= 0 ) {
        printf("ID: %d\n", l->viagem[pos].id);
        printf("Localizacao de origem: latitude %.2f - longitude %.2f\n", l->viagem[pos].origem_lat, l->viagem[pos].origem_longit);
        printf("Localizacao de destino: latitude %.2f - longitude %.2f\n", l->viagem[pos].destino_lat, l->viagem[pos].destino_longit);
        printf("Preco da viagem: %.2f\n", l->viagem[pos].preco);
    } else {
        printf("Erro - Viagem nao encontrada.\n");
    }
}

/**
 * Insere uma viagem no final da lista de viagens
 * 
 * @param LISTA_VIAGEM ponteiro para a lista de viagens
 * @param VIAGEM variavel do tipo viagem para ser inserida
 * 
 * @return Retorna 1 se foi inserido com sucesso
 **/
int pushViagem( LISTA_VIAGEM *l, VIAGEM v )
{
    // Lista cheia
    if ( l->pos_livre >= MAX_VIAGEM_LISTA ) {
        return 0;

    // Adiciona alimento na lista e incrementa um na posicao livre da lista
    } else {
        l->viagem[l->pos_livre] = v;
        l->pos_livre += 1;

        return 1;
    }
}

/**
 * Faz a impressao na tela das informacoes basicas de todas as viagens na lista
 * 
 * @param LISTA_VIAGEM ponteiro para a lista de alimentos
 **/
void imprimeViagens( LISTA_VIAGEM *l )
{
    if ( l->pos_livre == 0 ) {
        return;
    }
    
    printf("---------------------------------------- VIAGENS REGISTRADAS ----------------------------------------\n\n");

    int i;
    for ( i = 0; i < l->pos_livre; i++ ) {
        printf("ID: %d\n", l->viagem[i].id);
        printf("\n");
    }

    printf("\n");
    printf("\n");
}

/**
 * Busca o id de maior numero na lista de viagens
 * 
 * @param LISTA_VIAGEM ponteiro para a lista de viagens
 * 
 * @return integer id buscado
 **/
int buscaUltimoIdViagem( LISTA_VIAGEM *l )
{
    if ( l->pos_livre == 0 ) {
        return 0;
    }

    int i, id = 0;
    for ( i = 0; i < l->pos_livre; i++ ) {
        if ( l->viagem[i].id > id )
            id = l->viagem[i].id;
    }

    return id;
}

/**
 * Busca uma viagem pelo id na lista de viagens
 * 
 * @param LISTA_VIAGEM ponteiro para a lista de alimentos
 * @param id inteiro que referencia o id da viagem a ser procurada na lista
 * 
 * @return integer Retorna a posicao da viagem na lista de viagens (-1 se nao foi encontrado)
 **/
int foundViagemById( LISTA_VIAGEM *l, int id)
{
    if ( l->pos_livre == 0 ) {
        return -1;
    }
    int pos = 0;

    while ( pos < l->pos_livre && id != l->viagem[pos].id)
        pos++;

    if ( pos == l->pos_livre ) {
        return -1;
    }

    return pos;
}