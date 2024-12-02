#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h> // Inclui a biblioteca de manipulação de strings (para strtok, embora não diretamente usada neste código).
#include <math.h>

typedef struct {
    int x;
    int y;
    float distOrigem;
} Coordenada;

void distOrigem(Coordenada coodenadas[]);

int main() {
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L0Qteste.in", "r");
    FILE *fp_out = fopen("saida.txt", "w");

    // Verifica se os arquivos foram abertos com sucesso
    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n");
        return EXIT_FAILURE;
    }

    char line[255];
    const char comma[] = ",";
    char *slice;
    //coloquei isso aqui
    //Coordenada coordenadas[100];

    // Loop para ler cada linha do arquivo de entrada
    while (fgets(line, 255, fp_in) != NULL) {
        // strtok: (1) não é thread-safe (2) modifica a string original
        slice = strtok(line, comma);
        int soma = 0;
        int value;
        char text[20];

        // Loop para processar cada número na linha
        while (slice != NULL) {
            value = atoi(slice);
            soma = soma + value;
            slice = strtok(NULL, comma);
        }
        //printf("soma: %d ", soma); // linha para debug
        //sprintf(text, "%d\n", soma); // Formata a soma como string, adicionando uma nova linha
        //sprintf(text, "%s%s",text, "\n"); // alternativa sem sprintf
        //printf("texto: %s", text); // linha para debug

        //fputs(text, fp_out); // Escreve a soma formatada no arquivo de saída
    }

    fclose(fp_in); // Fecha o arquivo de entrada
    fclose(fp_out); // Fecha o arquivo de saída
    return EXIT_SUCCESS; // Retorna um código de sucesso
}

//fiz essa função

void distOrigem(Coordenada coordenadas[]){
    int tamanho;
    for (int i = 0; i < tamanho; i++) {
        // Distância = sqrt(x^2 + y^2)
        coordenadas[i].distOrigem = sqrt(coordenadas[i].x * coordenadas[i].x +
                                         coordenadas[i].y * coordenadas[i].y);
    }
}
