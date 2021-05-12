#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char marca[50];
    int contador;
} MARCA;

/**
 * Gera um relatorio simples com todas as informaçoes registradas
 * 
 * @param LISTA_CLIENTE ponteiro para lista de clientes
 * @param LISTA_ALIMENTO ponteiro para lista de alimentos
 * @param LISTA_VIAGEM ponteiro para lista de viagens
 * 
 **/
void geraRelatSimples (LISTA_CLIENTE *lc, LISTA_ALIMENTO *la, LISTA_VIAGEM *lv) {
    int i, j;
    FILE * f;
    f = fopen("relatorio_simples.txt", "w");

    fprintf(f, "---------------------------------------- CLIENTES REGISTRADOS ----------------------------------------\n\n\n");

    if ( lc->pos_livre != 0 ) {

        //Imprime todas as informaçoes de todos os clientes
        for ( i = 0; i < lc->pos_livre; i++ ) {
            fprintf(f, "ID %d\n", lc->cliente[i].id);
            fprintf(f, "Nome %s\n", lc->cliente[i].nome_completo);
            fprintf(f, "Data de nascimento: %d/%d/%d\n", lc->cliente[i].dia, lc->cliente[i].mes, lc->cliente[i].ano);
            fprintf(f, "Historico de pedidos completo: ");
            for ( j = 0; lc->cliente[i].historico[j] != 0; j++) {
                fprintf(f, "%d ", lc->cliente[i].historico[j]);
            }
            fprintf(f, "\nHistorico de pedidos atual: ");
            for ( j = 0; lc->cliente[i].historico_atual[j] != 0; j++) {
                fprintf(f, "%d ", lc->cliente[i].historico_atual[j]);
            }
            fprintf(f, "\nHistorico completo de viagens: ");
            for ( j = 0; lc->cliente[i].historico_viagem[j] != 0; j++ ) {
                fprintf(f, "%d ", lc->cliente[i].historico_viagem[j]);
            }
            fprintf(f, "\n\n");
        }
    }

    else {
        fprintf(f, "Nenhum cliente registrado\n");
    }

    fprintf(f, "\n---------------------------------------- ALIMENTOS REGISTRADOS ----------------------------------------\n\n\n");

    if ( la->pos_livre != 0 ) {

        //Imprime todas as informaçoes de todos os alimentos
        for ( i = 0; i < la->pos_livre; i++ ) {
            fprintf(f, "ID %d\n", la->alimento[i].id);
            fprintf(f, "Nome: %s\n", la->alimento[i].nome_alimento);
            fprintf(f, "Valor calorico em cal: %.2f\n", la->alimento[i].cal);
            fprintf(f, "Preco: R$%.2f\n", la->alimento[i].preco);
            fprintf(f, "Marca: %s\n\n", la->alimento[i].marca);
        }
    }

    else {
        fprintf(f, "Nenhum alimento registrado\n");
    }

    fprintf(f, "\n----------------------------------------- VIAGENS REGISTRADAS -----------------------------------------\n\n\n");


    if ( lv->pos_livre != 0 ) {

        //Imprime todas as informaçoes de todas as viagens
        for ( i = 0; i < lv->pos_livre; i++ ) {
            fprintf(f, "ID %d\n", lv->viagem[i].id);
            fprintf(f, "Origem:\n");
            fprintf(f, "Latitude (%.6f)\n", lv->viagem[i].origem_lat);
            fprintf(f, "Longitude (%.6f)\n", lv->viagem[i].origem_longit);
            fprintf(f, "Destino:\n");
            fprintf(f, "Latitude (%.6f)\n", lv->viagem[i].destino_lat);
            fprintf(f, "Longitude (%.6f)\n", lv->viagem[i].destino_longit);
            fprintf(f, "R$%.2f\n\n", lv->viagem[i].preco);
        }
    }

    else {
        fprintf(f, "Nenhuma viagem registrada\n");
    }

    fclose(f);
    printf("\nRelatorio gerado com sucesso\n");
}

/**
 * Gera um relatorio de estatisticas que informa a ocorrencia das marcas 
 * registradas e o preço medio das viagens realizadas por cada cliente
 * 
 * @param LISTA_CLIENTE ponteiro para lista de clientes
 * @param LISTA_ALIMENTO ponteiro para lista de alimentos
 * @param LISTA_VIAGEM ponteiro para lista de viagens
 * 
 **/
void geraRelatEstatisticas(LISTA_CLIENTE *lc, LISTA_ALIMENTO *la, LISTA_VIAGEM *lv) {

    MARCA vetor_marcas[la->pos_livre];

    FILE * f;
    f = fopen("relatorio_estatistica.txt", "w");

    fprintf(f, "------------------------------------ Ocorrencias de marcas registradas ------------------------------------\n\n", la->pos_livre);

    int i, j, k=0, aux;

    for( i = 0; i < la->pos_livre; i++ ) {
        vetor_marcas[i].contador = 0;
    }

    //Conta as marcas registradas e armazena num vetor MARCA
    for ( i=0; i < la->pos_livre; i++) {
        for ( j=0, aux=0; j < la->pos_livre; j++) {
            if ( (strcmp(la->alimento[i].marca, vetor_marcas[j].marca)) == 0 ) {
                vetor_marcas[j].contador++;
            }
            else {
                aux++;
            }

            if ( aux == la->pos_livre ) {
                strcpy(vetor_marcas[k].marca, la->alimento[i].marca);
                vetor_marcas[k].contador++;
                k++;
            }
        }
    }

    for ( j=0; j < k; j++) {
        if ( strcmp(vetor_marcas[j].marca, "") != 0 ) {
            fprintf(f, "%s: %d alimento(s)\n", vetor_marcas[j].marca, vetor_marcas[j].contador);
        }
    }
    fprintf(f, "\n");

    fprintf(f, "\n\n--------------------------- Preço médio das viagens realizadas por cada cliente ---------------------------\n\n");

    int idv = 1, pos;
    float calc;

    //Calcula o preço medio das viagens
    if ( lv->pos_livre != 0 ) {
        for ( i=0; i < lc->pos_livre; i++ ) {
            fprintf(f, "ID %d: ", lc->cliente[i].id);

            for ( j=0, calc=0, idv=1; idv != 0; j++ ) {
                idv = lc->cliente[i].historico_viagem[j];
                pos = foundViagemById(lv, idv);
                calc += lv->viagem[pos].preco;
            }

            calc = calc / (j-1);
            fprintf(f, "R$%.2f\n", calc);
        }
    }

    else {
        fprintf(f, "Nenhuma viagem registrada\n");
    }
    fclose(f);
    printf("\nRelatorio gerado com sucesso\n");
}

/**
 * Gera um relatorio com metadados a partir do cadastro, que informa 
 * as marcas mais ocorridas e os clientes com o maior preço medio de viagem
 * 
 * @param LISTA_CLIENTE ponteiro para lista de clientes
 * @param LISTA_ALIMENTO ponteiro para lista de alimentos
 * @param LISTA_VIAGEM ponteiro para lista de viagens
 * 
 **/
void geraRelatMetadados( LISTA_CLIENTE *lc, LISTA_ALIMENTO *la, LISTA_VIAGEM *lv ) {
    MARCA vetor_marcas[la->pos_livre];

    FILE * f;
    f = fopen("relatorio_metadados.txt", "w");

    int i, j, k=0, aux;

    for( i = 0; i < la->pos_livre; i++ ) {
        vetor_marcas[i].contador = 0;
    }

    //Conta as marcas registradas e armazena num vetor MARCA
    for ( i=0; i < la->pos_livre; i++ ) {
        for ( j=0, aux=0; j < la->pos_livre; j++) {
            if ( (strcmp(la->alimento[i].marca, vetor_marcas[j].marca)) == 0 ) {
                vetor_marcas[j].contador++;
            }
            else {
                aux++;
            }

            if ( aux == la->pos_livre ) {
                strcpy(vetor_marcas[k].marca, la->alimento[i].marca);
                vetor_marcas[k].contador++;
                k++;
            }
        }
    }

    fprintf(f, "Marca(s) com maior numero de ocorrencias:\n");
    
    int maior;
    for ( i=0, aux = 0; i < k; i++ ) {
        if ( vetor_marcas[i].contador > aux ) {
            aux = vetor_marcas[i].contador;
            maior = i;
        }
    }

    //Imprime as marcas com maior numero de ocorrencias
    for ( i=maior; i < k; i++ ) {
        if ( vetor_marcas[maior].contador == vetor_marcas[i].contador ) {
            fprintf(f, "%s\n", vetor_marcas[i].marca);
        }
    }

    int idv = 1, pos;
    float calc, vcalc[lc->pos_livre];

    if ( lv->pos_livre != 0 ) {
        for ( i=0, calc=0; i < lc->pos_livre; i++ ) {

            for ( j=0, calc=0, idv=1; idv != 0; j++ ) {
                idv = lc->cliente[i].historico_viagem[j];
                pos = foundViagemById(lv, idv);
                calc += lv->viagem[pos].preco;
            }

            calc /= j-1;
            vcalc[i] = calc;
        }

        fprintf(f, "\nCliente(s) com maior preco medio de viagens:\n");

        for ( i=0, aux=0; i < lc->pos_livre; i++) {
            if ( vcalc[i] > aux ) {
                aux = vcalc[i];
                maior = i;
            }
        }

        int idade;
        idade = 2021 - lc->cliente[maior].ano;
        if ( lc->cliente[maior].mes > 5 ) {
            idade--;
        }
        if ( lc->cliente[maior].mes == 5 && lc->cliente[maior].dia > 12) {
            idade--;
        }

        //Imprime os clientes com maior numero de ocorrencias
        fprintf(f, "ID %d\n", lc->cliente[maior].id);
        fprintf(f, "%s\n", lc->cliente[maior].nome_completo);
        fprintf(f, "Idade: %d\n", idade);

        for ( i=maior+1; i < lc->pos_livre; i++ ) {
            if ( vcalc[maior] == vcalc[i] ) {

                idade = 2021 - lc->cliente[maior].ano;
                if ( lc->cliente[i].mes > 5 ) {
                    idade--;
                }
                if ( lc->cliente[i].mes == 5 && lc->cliente[i].dia > 12) {
                    idade--;
                }
                fprintf(f, "ID %d\n", lc->cliente[i].id);
                fprintf(f, "%s\n", lc->cliente[i].nome_completo);
                fprintf(f, "Idade: %d\n", idade);
            }
        }
    }

    fclose(f);
    printf("\nRelatorio gerado com sucesso\n");
}