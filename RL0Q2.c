#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1024
#define MAX_ITENS 100

typedef struct {
    double x, y;
    double distOrigem;  // Para armazenar a distância da origem
} Coordenada;

// Função para calcular a distância da origem
double calcularDistanciaOrigem(double x, double y) {
    return sqrt(x * x + y * y);
}

// Função de merge sort para strings
void mergeSortStrings(char *vetor[], int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;
    mergeSortStrings(vetor, inicio, meio);
    mergeSortStrings(vetor, meio + 1, fim);

    int n1 = meio - inicio + 1, n2 = fim - meio;
    char *esquerdaArray[n1], *direitaArray[n2];
    for (int i = 0; i < n1; i++) esquerdaArray[i] = vetor[inicio + i];
    for (int i = 0; i < n2; i++) direitaArray[i] = vetor[meio + 1 + i];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (strcmp(esquerdaArray[i], direitaArray[j]) <= 0)
            vetor[k++] = esquerdaArray[i++];
        else
            vetor[k++] = direitaArray[j++];
    }
    while (i < n1) vetor[k++] = esquerdaArray[i++];
    while (j < n2) vetor[k++] = direitaArray[j++];
}

// Função de merge sort para inteiros
void mergeSortInts(int vetor[], int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;
    mergeSortInts(vetor, inicio, meio);
    mergeSortInts(vetor, meio + 1, fim);

    int n1 = meio - inicio + 1, n2 = fim - meio;
    int esquerdaArray[n1], direitaArray[n2];
    for (int i = 0; i < n1; i++) esquerdaArray[i] = vetor[inicio + i];
    for (int i = 0; i < n2; i++) direitaArray[i] = vetor[meio + 1 + i];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esquerdaArray[i] <= direitaArray[j])
            vetor[k++] = esquerdaArray[i++];
        else
            vetor[k++] = direitaArray[j++];
    }
    while (i < n1) vetor[k++] = esquerdaArray[i++];
    while (j < n2) vetor[k++] = direitaArray[j++];
}

// Função de merge sort para floats
void mergeSortFloats(double vetor[], int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;
    mergeSortFloats(vetor, inicio, meio);
    mergeSortFloats(vetor, meio + 1, fim);

    int n1 = meio - inicio + 1, n2 = fim - meio;
    double esquerdaArray[n1], direitaArray[n2];
    for (int i = 0; i < n1; i++) esquerdaArray[i] = vetor[inicio + i];
    for (int i = 0; i < n2; i++) direitaArray[i] = vetor[meio + 1 + i];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esquerdaArray[i] <= direitaArray[j])
            vetor[k++] = esquerdaArray[i++];
        else
            vetor[k++] = direitaArray[j++];
    }
    while (i < n1) vetor[k++] = esquerdaArray[i++];
    while (j < n2) vetor[k++] = direitaArray[j++];
}

// Função de merge sort para coordenadas
void mergeSortCoordenadas(Coordenada vetor[], int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;
    mergeSortCoordenadas(vetor, inicio, meio);
    mergeSortCoordenadas(vetor, meio + 1, fim);

    int n1 = meio - inicio + 1, n2 = fim - meio;
    Coordenada esquerdaArray[n1], direitaArray[n2];
    for (int i = 0; i < n1; i++) esquerdaArray[i] = vetor[inicio + i];
    for (int i = 0; i < n2; i++) direitaArray[i] = vetor[meio + 1 + i];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esquerdaArray[i].distOrigem <= direitaArray[j].distOrigem)
            vetor[k++] = esquerdaArray[i++];
        else
            vetor[k++] = direitaArray[j++];
    }
    while (i < n1) vetor[k++] = esquerdaArray[i++];
    while (j < n2) vetor[k++] = direitaArray[j++];
}

// Função para processar uma linha
void processarLinha(char *linha, FILE *saida) {
    char *strings[MAX_ITENS];
    int inteiros[MAX_ITENS];
    double floats[MAX_ITENS];
    Coordenada coordenadas[MAX_ITENS];

    int qtdStrings = 0, qtdInteiros = 0, qtdFloats = 0, qtdCoords = 0;

    char *token = strtok(linha, " ");
    while (token != NULL) {
        if (sscanf(token, "(%lf,%lf)", &coordenadas[qtdCoords].x, &coordenadas[qtdCoords].y) == 2) {
            coordenadas[qtdCoords].distOrigem = calcularDistanciaOrigem(coordenadas[qtdCoords].x, coordenadas[qtdCoords].y);
            qtdCoords++;
        } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            if (strchr(token, '.')) {
                floats[qtdFloats++] = atof(token);
            } else {
                inteiros[qtdInteiros++] = atoi(token);
            }
        } else {
            strings[qtdStrings] = strdup(token);
            qtdStrings++;
        }
        token = strtok(NULL, " ");
    }

    // Ordenar os elementos
    mergeSortStrings(strings, 0, qtdStrings - 1);
    mergeSortInts(inteiros, 0, qtdInteiros - 1);
    mergeSortFloats(floats, 0, qtdFloats - 1);
    mergeSortCoordenadas(coordenadas, 0, qtdCoords - 1);

    // Escrever os elementos no arquivo de saída
    fprintf(saida, "str:");
    for (int i = 0; i < qtdStrings; i++) {
        fprintf(saida, "%s%s", strings[i], (i == qtdStrings - 1) ? " " : " ");
        free(strings[i]);
    }
    if (qtdStrings == 0) {
        fprintf(saida, " ");
    }

    fprintf(saida, "int:");
    for (int i = 0; i < qtdInteiros; i++) {
        fprintf(saida, "%d%s", inteiros[i], (i == qtdInteiros - 1) ? " " : " ");
    }

    int secondDecimal = 0;
    fprintf(saida, "float:");
    for (int i = 0; i < qtdFloats; i++) {
        secondDecimal = (int)((floats[i] * 100)) % 10;
        if (secondDecimal == 0) {
            fprintf(saida, "%.1f%s", floats[i], (i == qtdFloats - 1) ? " " : " ");
        } else {
            fprintf(saida, "%.2f%s", floats[i], (i == qtdFloats - 1) ? " " : " ");
        }
    }

    fprintf(saida, "p:");
    for (int i = 0; i < qtdCoords; i++) {
        if (fabs(coordenadas[i].x - (int)coordenadas[i].x) < 1e-9){
            fprintf(saida, "(%d,", (int)coordenadas[i].x);
        }
        else{
            secondDecimal = (int)((coordenadas[i].x * 100)) % 10;
            if(secondDecimal == 0){
                fprintf(saida, "(%.1f,", coordenadas[i].x);
            }else{
                fprintf(saida, "(%.2f,", coordenadas[i].x);
            }
        }

        if (fabs(coordenadas[i].y - (int)coordenadas[i].y) < 1e-9){
            fprintf(saida, "%d)%s", (int)coordenadas[i].y, (i == qtdCoords - 1) ? "" : " ");
        }
        else{
            secondDecimal = (int)((coordenadas[i].y * 100)) % 10;
            if(secondDecimal == 0){
                fprintf(saida, "%.1f)%s", coordenadas[i].y, (i == qtdCoords - 1) ? "" : " ");
            }else{
                fprintf(saida, "%.2f)%s", coordenadas[i].y, (i == qtdCoords - 1) ? "" : " ");
            }
        }
    }
}

// Função principal
int main() {
    FILE *entrada = fopen("L0Q2.in", "r");
    FILE *saida = fopen("L0Q2.out", "w");

    if (!entrada || !saida) {
        perror("Erro ao abrir os arquivos");
        return EXIT_FAILURE;
    }

    bool firstRun = false;
    char linha[MAX_LINHA];
    while (fgets(linha, sizeof(linha), entrada)) {
        if (firstRun) {
            fprintf(saida, "\n");
        }
        firstRun = true;  // preciso de setar essa flag para a formatação sair correta e nao colocar um \n extra no final
        linha[strcspn(linha, "\n")] = '\0';
        processarLinha(linha, saida);
    }

    fclose(entrada);
    fclose(saida);

    // printf("Processamento concluído. Saída em 'L0Q2.out'.\n");
    return EXIT_SUCCESS;
}
