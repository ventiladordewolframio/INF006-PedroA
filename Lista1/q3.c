#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para lista simplesmente ligada circular
typedef struct NodoReal {
    float valor;
    struct NodoReal* proximo;
} NodoReal;

// Estrutura para lista duplamente ligada
typedef struct NodoInteiro {
    int chave;
    NodoReal* listaReais;  // Ponteiro para a lista circular associada
    struct NodoInteiro* proximo;
    struct NodoInteiro* anterior;
} NodoInteiro;

// Função para criar um novo nó para a lista de inteiros
NodoInteiro* criarNodoInteiro(int chave) {
    NodoInteiro* novoNodo = (NodoInteiro*)malloc(sizeof(NodoInteiro));
    novoNodo->chave = chave;
    novoNodo->listaReais = NULL;
    novoNodo->proximo = NULL;
    novoNodo->anterior = NULL;
    return novoNodo;
}

// Função para criar um novo nó para a lista de reais
NodoReal* criarNodoReal(float valor) {
    NodoReal* novoNodo = (NodoReal*)malloc(sizeof(NodoReal));
    novoNodo->valor = valor;
    novoNodo->proximo = NULL;
    return novoNodo;
}

// Inserção ordenada na lista duplamente ligada
void inserirOrdenadoInteiro(NodoInteiro** cabeca, int chave) {
    NodoInteiro* novoNodo = criarNodoInteiro(chave);
    if (*cabeca == NULL || (*cabeca)->chave > chave) {
        novoNodo->proximo = *cabeca;
        if (*cabeca != NULL) (*cabeca)->anterior = novoNodo;
        *cabeca = novoNodo;
        return;
    }
    NodoInteiro* atual = *cabeca;
    while (atual->proximo != NULL && atual->proximo->chave < chave) {
        atual = atual->proximo;
    }
    novoNodo->proximo = atual->proximo;
    if (atual->proximo != NULL) atual->proximo->anterior = novoNodo;
    atual->proximo = novoNodo;
    novoNodo->anterior = atual;
}

// Inserção ordenada na lista circular
void inserirOrdenadoReal(NodoReal** cabeca, float valor) {
    NodoReal* novoNodo = criarNodoReal(valor);
    if (*cabeca == NULL) {
        novoNodo->proximo = novoNodo;
        *cabeca = novoNodo;
        return;
    }
    NodoReal *atual = *cabeca, *anterior = NULL;
    do {
        if (valor < atual->valor) break;
        anterior = atual;
        atual = atual->proximo;
    } while (atual != *cabeca);

    novoNodo->proximo = atual;
    if (anterior == NULL) {
        NodoReal* cauda = *cabeca;
        while (cauda->proximo != *cabeca) cauda = cauda->proximo;
        cauda->proximo = novoNodo;
        *cabeca = novoNodo;
    } else {
        anterior->proximo = novoNodo;
    }
}

// Associação de lista de reais a cada nó da lista duplamente ligada
void associarListaReais(NodoInteiro* cabeca, float* vetorReais, int tamanhoReais) {
    NodoInteiro* atual = cabeca;
    while (atual != NULL) {
        for (int i = 0; i < tamanhoReais; i++) {
            if (fabs(atual->chave - vetorReais[i]) <= 0.99) {
                inserirOrdenadoReal(&atual->listaReais, vetorReais[i]);
            }
        }
        atual = atual->proximo;
    }
}

// Função para imprimir as listas no arquivo de saída
void imprimirListas(NodoInteiro* cabeca, FILE* arquivoSaida) {
    fprintf(arquivoSaida, "[");
    NodoInteiro* atual = cabeca;
    while (atual != NULL) {
        fprintf(arquivoSaida, "%d(", atual->chave);
        NodoReal* atualReal = atual->listaReais;
        if (atualReal != NULL) {
            NodoReal* inicio = atualReal;
            do {
                fprintf(arquivoSaida, "%.2f", atualReal->valor);
                atualReal = atualReal->proximo;
                if (atualReal != inicio) {
                    fprintf(arquivoSaida, " − >");
                }
            } while (atualReal != inicio);
        }
        fprintf(arquivoSaida, ")");
        if (atual->proximo != NULL) {
            fprintf(arquivoSaida, " − >");
        }
        atual = atual->proximo;
    }
    fprintf(arquivoSaida, "]\n");
}

int main() {
    FILE* arquivoEntrada = fopen("L1Q3.in", "r");
    if (!arquivoEntrada) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    FILE* arquivoSaida = fopen("L1Q3.out", "w");
    if (!arquivoSaida) {
        perror("Erro ao criar o arquivo de saída");
        fclose(arquivoEntrada);
        return 1;
    }

    char tipo;
    int vetorInteiros[100], tamanhoInteiros = 0;
    float vetorReais[100];
    int tamanhoReais = 0;

    // Leitura do arquivo de entrada
    while (fscanf(arquivoEntrada, "%c", &tipo) != EOF) {
        if (tipo == 'L') {
            char subtipo;
            fscanf(arquivoEntrada, "%c", &subtipo);
            if (subtipo == 'E') {
                int valor;
                while (fscanf(arquivoEntrada, "%d", &valor) == 1) {
                    vetorInteiros[tamanhoInteiros++] = valor;
                }
            } else if (subtipo == 'I') {
                float valor;
                while (fscanf(arquivoEntrada, "%f", &valor) == 1) {
                    vetorReais[tamanhoReais++] = valor;
                }
            }
        }
    }
    fclose(arquivoEntrada);

    // Construção da lista duplamente ligada
    NodoInteiro* cabeca = NULL;
    for (int i = 0; i < tamanhoInteiros; i++) {
        inserirOrdenadoInteiro(&cabeca, vetorInteiros[i]);
    }

    // Associação das listas de reais
    associarListaReais(cabeca, vetorReais, tamanhoReais);

    // Impressão das listas no arquivo de saída
    imprimirListas(cabeca, arquivoSaida);

    fclose(arquivoSaida);
    return 0;
}
