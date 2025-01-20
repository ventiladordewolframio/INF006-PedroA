#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar cada lista de números
typedef struct No {
    int *valores;     // Array para armazenar os números
    int tamanho;      // Tamanho da lista
    int valorTotal;   // Soma dos valores da lista
    struct No *prox;  // Ponteiro para a próxima lista
} No;

// Função para ordenar a lista de números
void ordenarLista(int *lista, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (lista[i] > lista[j]) {
                int temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
}

// Função para comparar as listas com base no valor total
int compararListas(const void *a, const void *b) {
    No *listaA = *(No **)a;
    No *listaB = *(No **)b;
    return listaA->valorTotal - listaB->valorTotal;
}

// Função para criar e preencher uma nova lista
No *criarNo(int *valores, int tamanho) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valores = (int *)malloc(tamanho * sizeof(int));
    memcpy(novoNo->valores, valores, tamanho * sizeof(int));
    novoNo->tamanho = tamanho;
    novoNo->valorTotal = 0;
    for (int i = 0; i < tamanho; i++) {
        novoNo->valorTotal += valores[i];
    }
    novoNo->prox = NULL;
    return novoNo;
}

// Função para liberar a memória de uma lista
void liberarLista(No *head) {
    No *temp;
    while (head != NULL) {
        temp = head;
        head = head->prox;
        free(temp->valores);
        free(temp);
    }
}

int main() {
    FILE *fp_in = fopen("L1Q1.in", "r");
    FILE *fp_out = fopen("L1Q1.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n");
        return EXIT_FAILURE;
    }

    // Entrada de dados, com a linha única fornecida
    char linha[1000];
    int QTDX = 0;
    bool condicao = fgets(linha, sizeof(linha), fp_in) != NULL;

    while (condicao) {
        // Variáveis auxiliares para processamento da linha
        int valores[100];        // Array temporário para armazenar valores de uma lista
        int tamanho = 0;         // Tamanho atual da lista de valores
        No *listaCabeça = NULL;  // Cabeça da lista de listas
        No *listaAtual = NULL;   // Ponteiro para a lista atual

        // Tokeniza a linha de entrada para processar cada número
        char *token = strtok(linha, " ");
        while (token != NULL) {
            if (strcmp(token, "start") == 0) {
                // Se encontrou um "start", processa a lista atual
                if (tamanho > 0) {
                    // Cria um novo nó (lista) com os valores armazenados
                    No *novoNo = criarNo(valores, tamanho);

                    // Se for a primeira lista, inicializa o ponteiro da cabeça
                    if (listaCabeça == NULL) {
                        listaCabeça = novoNo;
                        listaAtual = listaCabeça;
                    } else {
                        listaAtual->prox = novoNo;
                        listaAtual = novoNo;
                    }
                }
                // Reseta a lista temporária e o tamanho
                tamanho = 0;
            } else {
                // Adiciona o valor à lista temporária
                valores[tamanho++] = atoi(token);
            }

            // Avança para o próximo token
            token = strtok(NULL, " ");
        }

        // Cria o último nó após o loop
        if (tamanho > 0) {
            No *novoNo = criarNo(valores, tamanho);
            if (listaCabeça == NULL) {
                listaCabeça = novoNo;
            } else {
                listaAtual->prox = novoNo;
            }
        }

        // Ordena cada lista individualmente
        No *current = listaCabeça;
        while (current != NULL) {
            ordenarLista(current->valores, current->tamanho);
            current = current->prox;
        }

        // Ordena as listas em ordem crescente do valor total
        int numListas = 0;
        No *temp = listaCabeça;
        while (temp != NULL) {
            numListas++;
            temp = temp->prox;
        }

        // Coloca as listas em um array para ordenar
        No **listas = (No **)malloc(numListas * sizeof(No *));
        temp = listaCabeça;
        for (int i = 0; i < numListas; i++) {
            listas[i] = temp;
            temp = temp->prox;
        }

        qsort(listas, numListas, sizeof(No *), compararListas);

        // Imprime o resultado ordenado
        for (int i = 0; i < numListas; i++) {
            printf("start ");
            if (i == 0) {
                fprintf(fp_out, "start ");
            } else {
                fprintf(fp_out, " start");
            }

            for (int j = 0; j < listas[i]->tamanho; j++) {
                printf("%d ", listas[i]->valores[j]);
                fprintf(fp_out, " %d", listas[i]->valores[j]);
            }
            printf("\n");
        }

        if (fgets(linha, sizeof(linha), fp_in) != NULL) {
            condicao == true;
        } else {
            condicao == false;
            QTDX++;
            // fprintf(fp_out, "%s\n", "strgaugds");
            //  Libera a memória
            free(listas);
            liberarLista(listaCabeça);
            return 0;
        }

        fprintf(fp_out, "\n");
        printf("oquediaboeesiso\n");

        QTDX++;
        // fprintf(fp_out, "%s\n", "strgaugds");
        //  Libera a memória
        free(listas);
        liberarLista(listaCabeça);
    }

    return 0;
}
