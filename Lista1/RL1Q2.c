#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
FILE *fp_out = NULL;
int firsttime = 0;
// Definindo a pilha
typedef struct Stack {
    char data[MAX_SIZE][100];
    int top;
} Stack;

// Funções auxiliares para a pilha
void initStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, const char *value) {
    if (isFull(stack)) {
        printf("Stack is full.\n");
        return;
    }
    strcpy(stack->data[++stack->top], value);
}

void pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    stack->top--;
}

void printStack(FILE *fp_out, Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        fprintf(fp_out, "%s ", stack->data[i]);
    }
    fprintf(fp_out, "\n");
}

// Função para processar o push e pop com o devido logging
void processPush(FILE *fp_out, Stack *stack, const char *value) {
    Stack tempStack;
    initStack(&tempStack);
    int popCount = 0;

    // Desempilhar até encontrar a posição correta para o novo valor
    while (!isEmpty(stack) && strcmp(stack->data[stack->top], value) > 0) {
        push(&tempStack, stack->data[stack->top]);
        pop(stack);  // Desempilhar o topo da pilha original
        popCount++;  // Conta os pops
    }

    // Se houve pops, imprime o número total de pops
    if (popCount > 0) {
        fprintf(fp_out, "%dx-pop ", popCount);
    }

    // Loga a operação de push do novo valor
    if (firsttime == 1) {
        fprintf(fp_out, "push-%s ", value);
        firsttime = 0;
    } else {
        fprintf(fp_out, "push-%s ", value);
    }
    push(stack, value);  // Empilha o valor no topo da pilha

    // Reempilhar os itens da pilha temporária de volta para a pilha principal
    while (!isEmpty(&tempStack)) {
        // Log cada push ao reempilhar
        fprintf(fp_out, "push-%s ", tempStack.data[tempStack.top]);
        push(stack, tempStack.data[tempStack.top]);
        tempStack.top--;  // Remove da pilha temporária
    }
}

// Função principal para processar a entrada e saída esperada
int main() {
    FILE *fp_in = fopen("L1Q2.in", "r");
    FILE *fp_out = fopen("L1Q2.out", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n");
        return EXIT_FAILURE;
    }

    // Entrada de dados, com a linha única fornecida
    char input[1000];
    int QTDX = 0;
    bool condicao = fgets(input, sizeof(input), fp_in) != NULL;
    bool umavezporlinha = true;
    while (condicao) {
        Stack stack;
        initStack(&stack);

        // Entrada fornecida: "Bruno Dani Carla Antônia Walter Maria João"
        // const char *input = "Bruno Dani Carla Antônia Walter Maria João";

        // Copiar a entrada para uma string mutável
        char inputCopy[1000];  // Assumindo que o tamanho da entrada não ultrapasse 1000 caracteres
        strcpy(inputCopy, input);

        // Separar os nomes pela string
        char *token = strtok(inputCopy, " ");
        char *nxttoken = NULL;
        do {
            char *thistoken = token;
            nxttoken = strtok(NULL, " ");
            if (nxttoken == NULL && umavezporlinha) {
                firsttime = 1;
                umavezporlinha = false;
            }

            processPush(fp_out, &stack, thistoken);  // Processa cada nome com operações de push e pop

            token = nxttoken;
        } while (token != NULL);

        // Print final da pilha
        printf("\nFinal stack order:\n");
        // printStack(fp_out,&stack);

        if (fgets(input, sizeof(input), fp_in) != NULL) {
            condicao == true;
            umavezporlinha = true;
        } else {
            condicao == false;
            QTDX++;
            // fprintf(fp_out, "%s\n", "strgaugds");
            //  Libera a memória
            // free(listas);
            // liberarLista(listaCabeça);
            return 0;
        }
    }
    return 0;
}
