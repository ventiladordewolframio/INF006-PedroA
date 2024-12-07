#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TOKENS 100
#define MAX_NAME_LENGTH 50

// Estrutura para coordenadas
typedef struct {
    double x, y;
    double distOrigem;
} Coordenada;

// Função para calcular a distância da origem
double calculaDistancia(double x, double y) {
    return sqrt(x * x + y * y);
}

// Função para ordenar números reais
int comparaNumeros(const void *a, const void *b) {
    double num1 = *(double *)a;
    double num2 = *(double *)b;
    return (num1 > num2) - (num1 < num2);
}

// Função para ordenar coordenadas pela distância da origem
int comparaCoordenadas(const void *a, const void *b) {
    Coordenada *c1 = (Coordenada *)a;
    Coordenada *c2 = (Coordenada *)b;
    return (c1->distOrigem > c2->distOrigem) - (c1->distOrigem < c2->distOrigem);
}

// Função para ordenar nomes
int comparaNomes(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");

    // Verifica se os arquivos foram abertos com sucesso
    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n");
        return EXIT_FAILURE;
    }

    char linha[1024];
    char *nomes[MAX_TOKENS];
    double numeros[MAX_TOKENS];
    Coordenada coordenadas[MAX_TOKENS];

    int totalNomes = 0, totalNumeros = 0, totalCoordenadas = 0;

    while (fgets(linha, sizeof(linha), fp_in)) {
        char *token = strtok(linha, " \n");

        while (token != NULL) {
            if (isalpha(token[0])) { // Nome
                nomes[totalNomes] = strdup(token);
                totalNomes++;
            } else if (strchr(token, '(') && strchr(token, ')')) { // Coordenada
                Coordenada coord;
                sscanf(token, "(%lf,%lf)", &coord.x, &coord.y);
                coord.distOrigem = calculaDistancia(coord.x, coord.y);
                coordenadas[totalCoordenadas++] = coord;
            } else { // Número real
                numeros[totalNumeros++] = atof(token);
            }
            token = strtok(NULL, " \n");
        }
    }

    fclose(fp_in);

    // Ordenar os dados
    qsort(nomes, totalNomes, sizeof(char *), comparaNomes);
    qsort(numeros, totalNumeros, sizeof(double), comparaNumeros);
    qsort(coordenadas, totalCoordenadas, sizeof(Coordenada), comparaCoordenadas);

    // Exibir os resultados
    printf("Nomes ordenados:\n");
    for (int i = 0; i < totalNomes; i++) {
        printf("%s\n", nomes[i]);
        free(nomes[i]);
    }

    printf("\nNúmeros reais ordenados:\n");
    for (int i = 0; i < totalNumeros; i++) {
        printf("%.2lf\n", numeros[i]);
    }

    printf("\nCoordenadas ordenadas pela distância da origem:\n");
    for (int i = 0; i < totalCoordenadas; i++) {
        printf("(%.2lf, %.2lf) - Distância: %.2lf\n",
               coordenadas[i].x, coordenadas[i].y, coordenadas[i].distOrigem);
    }

    return 0;
}

