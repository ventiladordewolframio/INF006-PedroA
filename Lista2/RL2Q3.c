#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da AVL
typedef struct No {
    int chave;
    int altura;
    struct No *esquerda, *direita;
} No;

// Função para obter a altura de um nó
int obterAltura(No *no) {
    return no ? no->altura : -1;
}

// Função para calcular o fator de balanceamento
int fatorBalanceamento(No *no) {
    return no ? obterAltura(no->esquerda) - obterAltura(no->direita) : 0;
}

// Função para criar um novo nó
No *novoNo(int chave) {
    No *no = (No *)malloc(sizeof(No));
    no->chave = chave;
    no->altura = 0;
    no->esquerda = no->direita = NULL;
    return no;
}

// Rotação simples à direita
No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T = x->direita;

    x->direita = y;
    y->esquerda = T;

    y->altura = 1 + (obterAltura(y->esquerda) > obterAltura(y->direita) ? obterAltura(y->esquerda) : obterAltura(y->direita));
    x->altura = 1 + (obterAltura(x->esquerda) > obterAltura(x->direita) ? obterAltura(x->esquerda) : obterAltura(x->direita));

    return x;
}

// Rotação simples à esquerda
No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T = y->esquerda;

    y->esquerda = x;
    x->direita = T;

    x->altura = 1 + (obterAltura(x->esquerda) > obterAltura(x->direita) ? obterAltura(x->esquerda) : obterAltura(x->direita));
    y->altura = 1 + (obterAltura(y->esquerda) > obterAltura(y->direita) ? obterAltura(y->esquerda) : obterAltura(y->direita));

    return y;
}

// Balanceamento do nó
No *balancear(No *no) {
    if (!no) return NULL;

    no->altura = 1 + (obterAltura(no->esquerda) > obterAltura(no->direita) ? obterAltura(no->esquerda) : obterAltura(no->direita));
    int fb = fatorBalanceamento(no);

    if (fb > 1) {
        if (fatorBalanceamento(no->esquerda) < 0) no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    if (fb < -1) {
        if (fatorBalanceamento(no->direita) > 0) no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Inserção na árvore AVL
No *inserir(No *raiz, int chave) {
    if (!raiz) return novoNo(chave);

    if (chave < raiz->chave) raiz->esquerda = inserir(raiz->esquerda, chave);
    else if (chave > raiz->chave) raiz->direita = inserir(raiz->direita, chave);

    return balancear(raiz);
}

// Função para encontrar o menor nó
No *menorNo(No *no) {
    while (no->esquerda) no = no->esquerda;
    return no;
}

// Remoção na árvore AVL
No *remover(No *raiz, int chave, int *presente) {
    if (!raiz) {
        *presente = 0;
        return inserir(raiz, chave);
    }

    if (chave < raiz->chave) raiz->esquerda = remover(raiz->esquerda, chave, presente);
    else if (chave > raiz->chave) raiz->direita = remover(raiz->direita, chave, presente);
    else {
        *presente = 1;
        if (!raiz->esquerda || !raiz->direita) {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            free(raiz);
            return temp;
        }
        No *temp = menorNo(raiz->direita);
        raiz->chave = temp->chave;
        raiz->direita = remover(raiz->direita, temp->chave, presente);
    }

    return balancear(raiz);
}

// Impressão em ordem
void imprimirEmOrdem(No *raiz, FILE *arquivo) {
    if (!raiz) return;
    imprimirEmOrdem(raiz->esquerda, arquivo);
    fprintf(arquivo, "%d (%d) ", raiz->chave, raiz->altura);
    imprimirEmOrdem(raiz->direita, arquivo);
}

int main() {
    FILE *entrada = fopen("L2Q3.in", "r");
    FILE *saida = fopen("L2Q3.out", "w");

    if (!entrada || !saida) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), entrada)) {
        No *raiz = NULL;
        char *token = strtok(linha, " ");
        while (token) {
            char op = token[0];
            token = strtok(NULL, " ");
            if (!token) break;
            int num = atoi(token);
            if (op == 'a') raiz = inserir(raiz, num);
            else if (op == 'r') {
                int presente = 1;
                raiz = remover(raiz, num, &presente);
            }
            token = strtok(NULL, " ");
        }
        imprimirEmOrdem(raiz, saida);
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
