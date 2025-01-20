#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

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

void printStack(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%s ", stack->data[i]);
    }
    printf("\n");
}

// Função para processar o push e pop com o devido logging
void processPush(Stack *stack, const char *value) {
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
        printf("%dx-pop ", popCount);
    }

    // Loga a operação de push do novo valor
    printf("push-%s ", value);
    push(stack, value);  // Empilha o valor no topo da pilha

    // Reempilhar os itens da pilha temporária de volta para a pilha principal
    while (!isEmpty(&tempStack)) {
        // Log cada push ao reempilhar
        printf("push-%s ", tempStack.data[tempStack.top]);
        push(stack, tempStack.data[tempStack.top]);
        tempStack.top--;  // Remove da pilha temporária
    }
}

// Função principal para processar a entrada e saída esperada
int main() {
    Stack stack;
    initStack(&stack);

    // Entrada fornecida: "Bruno Dani Carla Antônia Walter Maria João"
    const char *input = "Bruno Dani Carla Antônia Walter Maria João";
    
    // Copiar a entrada para uma string mutável
    char inputCopy[1000];  // Assumindo que o tamanho da entrada não ultrapasse 1000 caracteres
    strcpy(inputCopy, input);

    // Separar os nomes pela string
    char *token = strtok(inputCopy, " ");
    while (token != NULL) {
        processPush(&stack, token);  // Processa cada nome com operações de push e pop
        token = strtok(NULL, " ");
    }

    // Print final da pilha
    printf("\nFinal stack order:\n");
    printStack(&stack);

    return 0;
}
