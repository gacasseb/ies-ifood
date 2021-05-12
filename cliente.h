#define MAX_CLIENTE_LISTA 50
#define MAX_HISTORICO_LISTA 50

typedef struct {
    int id;
    char *nome_completo;
    int dia, mes, ano;
    int historico[50];
    int historico_atual[50];
    int historico_viagem[50];
} CLIENTE;

typedef struct {
    CLIENTE cliente[MAX_CLIENTE_LISTA];
    int pos_livre;
} LISTA_CLIENTE;
