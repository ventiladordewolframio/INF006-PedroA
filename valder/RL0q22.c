#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TOKENS 255
#define MAX_NAME_LENGTH 50

// Estrutura para coordenadas
typedef struct {
    double x, y;
} Coordenada;

// Função para verificar se uma string representa um número inteiro
int ehInteiro(const char *s) {
    if (*s == '-' || *s == '+') s++;
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    return 1;
}

// Função para verificar se uma string representa um número float
int ehFloat(const char *s) {
    int ponto = 0;
    if (*s == '-' || *s == '+') s++;
    while (*s) {
        if (*s == '.') {
            if (ponto) return 0; // Mais de um ponto
            ponto = 1;
        } else if (!isdigit(*s)) {
            return 0;
        }
        s++;
    }
    return 1;
}

// Função para verificar se uma string representa uma coordenada
int ehCoordenada(const char *s, Coordenada *coord) {
    return sscanf(s, "(%lf,%lf)", &coord->x, &coord->y) == 2;
}

// Função principal
int main() {
    // Arquivos de entrada e saída
    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");

    if (!fp_in || !fp_out) {
        printf("Erro ao abrir os arquivos.\n");
        return EXIT_FAILURE;
    }

    char linha[1000];
    char *strings[MAX_TOKENS];
    int inteiros[MAX_TOKENS];
    double floats[MAX_TOKENS];
    Coordenada coordenadas[MAX_TOKENS];

    int totalStrings = 0, totalInteiros = 0, totalFloats = 0, totalCoordenadas = 0;

    while (fgets(linha, sizeof(linha), fp_in)) {
        if (strlen(linha) <= 1) { // Linha vazia: Finaliza grupo atual
            // Escreve o grupo no arquivo de saída
            if (totalStrings > 0) {
                fprintf(fp_out, "str:");
                for (int i = 0; i < totalStrings; i++) {
                    fprintf(fp_out, "%s%s", strings[i], i == totalStrings - 1 ? "\n" : " ");
                    free(strings[i]);
                }
            }
            if (totalInteiros > 0) {
                fprintf(fp_out, "int:");
                for (int i = 0; i < totalInteiros; i++) {
                    fprintf(fp_out, "%d%s", inteiros[i], i == totalInteiros - 1 ? "\n" : " ");
                }
            }
            if (totalFloats > 0) {
                fprintf(fp_out, "float:");
                for (int i = 0; i < totalFloats; i++) {
                    fprintf(fp_out, "%.2lf%s", floats[i], i == totalFloats - 1 ? "\n" : " ");
                }
            }
            if (totalCoordenadas > 0) {
                fprintf(fp_out, "p:");
                for (int i = 0; i < totalCoordenadas; i++) {
                    fprintf(fp_out, "(%.1lf,%.1lf)%s", coordenadas[i].x, coordenadas[i].y, i == totalCoordenadas - 1 ? "\n" : " ");
                }
            }
            fprintf(fp_out, "\n");

            // Reinicia os contadores
            totalStrings = totalInteiros = totalFloats = totalCoordenadas = 0;
            continue;
        }

        char *token = strtok(linha, " \n");
        while (token) {
            Coordenada coord;
            if (ehCoordenada(token, &coord)) {
                coordenadas[totalCoordenadas++] = coord;
            } else if (ehInteiro(token)) {
                inteiros[totalInteiros++] = atoi(token);
            } else if (ehFloat(token)) {
                floats[totalFloats++] = atof(token);
            } else {
                strings[totalStrings] = strdup(token);
                totalStrings++;
            }
            token = strtok(NULL, " \n");
        }
    }

    // Finaliza o último grupo, se existir
    if (totalStrings > 0) {
        fprintf(fp_out, "str:");
        for (int i = 0; i < totalStrings; i++) {
            fprintf(fp_out, "%s%s", strings[i], i == totalStrings - 1 ? "\n" : " ");
            free(strings[i]);
        }
    }
    if (totalInteiros > 0) {
        fprintf(fp_out, "int:");
        for (int i = 0; i < totalInteiros; i++) {
            fprintf(fp_out, "%d%s", inteiros[i], i == totalInteiros - 1 ? "\n" : " ");
        }
    }
    if (totalFloats > 0) {
        fprintf(fp_out, "float:");
        for (int i = 0; i < totalFloats; i++) {
            fprintf(fp_out, "%.2lf%s", floats[i], i == totalFloats - 1 ? "\n" : " ");
        }
    }
    if (totalCoordenadas > 0) {
        fprintf(fp_out, "p:");
        for (int i = 0; i < totalCoordenadas; i++) {
            fprintf(fp_out, "(%.1lf,%.1lf)%s", coordenadas[i].x, coordenadas[i].y, i == totalCoordenadas - 1 ? "\n" : " ");
        }
    }

    fclose(fp_in);
    fclose(fp_out);

    printf("Processamento concluído. Resultados em 'L0Q1.out'.\n");
    return 0;
}
