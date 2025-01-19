#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definição das estruturas
typedef struct NoListaSimples {
    float valor;
    struct NoListaSimples* prox;
} NoListaSimples;

typedef struct NoListaDupla {
    int chave;
    NoListaSimples* listaSimples;
    struct NoListaDupla* prox;
    struct NoListaDupla* ant;
} NoListaDupla;

// Funções auxiliares
NoListaSimples* inserirOrdenadoListaSimples(NoListaSimples* lista, float valor) {
    NoListaSimples* novo = malloc(sizeof(NoListaSimples));
    novo->valor = valor;

    if (!lista) {
        novo->prox = novo; // Circular
        return novo;
    }

    NoListaSimples* atual = lista;
    NoListaSimples* anterior = NULL;

    do {
        if (valor <= atual->valor) break;
        anterior = atual;
        atual = atual->prox;
    } while (atual != lista);

    novo->prox = atual;
    if (anterior) {
        anterior->prox = novo;
    } else {
        // Inserção na cabeça
        NoListaSimples* ultimo = lista;
        while (ultimo->prox != lista) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo;
        return novo;
    }

    return lista;
}

NoListaDupla* inserirOrdenadoListaDupla(NoListaDupla* lista, int chave) {
    NoListaDupla* novo = malloc(sizeof(NoListaDupla));
    novo->chave = chave;
    novo->listaSimples = NULL;
    novo->prox = NULL;
    novo->ant = NULL;

    if (!lista) return novo;

    NoListaDupla* atual = lista;
    while (atual->prox && atual->chave < chave) {
        atual = atual->prox;
    }

    if (atual->chave >= chave) {
        if (atual->ant) atual->ant->prox = novo;
        novo->ant = atual->ant;
        novo->prox = atual;
        atual->ant = novo;
        return lista->chave < chave ? lista : novo;
    } else {
        atual->prox = novo;
        novo->ant = atual;
        return lista;
    }
}

void imprimirListaDupla(NoListaDupla* lista, FILE* saida) {
    fprintf(saida, "[");
    while (lista) {
        fprintf(saida, "%d(", lista->chave);
        NoListaSimples* listaSimples = lista->listaSimples;
        if (listaSimples) {
            NoListaSimples* inicio = listaSimples;
            do {
                fprintf(saida, "%.2f", listaSimples->valor);
                listaSimples = listaSimples->prox;
                if (listaSimples != inicio) fprintf(saida, "->");
            } while (listaSimples != inicio);
        }
        fprintf(saida, ")");
        lista = lista->prox;
        if (lista) fprintf(saida, "->");
    }
    fprintf(saida, "]\n");
}

// Função principal
int main() {
    FILE* entrada = fopen("L1Q3.in", "r");
    FILE* saida = fopen("L1Q3.out", "w");

    if (!entrada || !saida) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), entrada)) {
        NoListaDupla* listaDupla = NULL;
        char* token = strtok(linha, " ");

        // Processa a parte "LE"
        if (strcmp(token, "LE") == 0) {
            while ((token = strtok(NULL, " ")) && strcmp(token, "LI") != 0) {
                int chave = atoi(token);
                listaDupla = inserirOrdenadoListaDupla(listaDupla, chave);
            }
        }

        // Processa a parte "LI"
        while ((token = strtok(NULL, " "))) {
            float valor = atof(token);
            NoListaDupla* atual = listaDupla;
            while (atual) {
                if (fabs(valor - atual->chave) <= 0.99) {
                    atual->listaSimples = inserirOrdenadoListaSimples(atual->listaSimples, valor);
                    break;
                }
                atual = atual->prox;
            }
        }

        imprimirListaDupla(listaDupla, saida);

        // Liberação de memória
        while (listaDupla) {
            NoListaDupla* temp = listaDupla;
            listaDupla = listaDupla->prox;

            NoListaSimples* listaSimples = temp->listaSimples;
            while (listaSimples) {
                NoListaSimples* tempSimples = listaSimples;
                listaSimples = listaSimples->prox;
                if (listaSimples == temp->listaSimples) break;
                free(tempSimples);
            }
            free(temp);
        }
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}

