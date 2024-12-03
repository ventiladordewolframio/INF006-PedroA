#include <math.h>
#include <stdbool.h>
#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h>  // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h>  // Inclui a biblioteca de manipulação de strings (para strtok, embora não diretamente usada neste código).
typedef struct {
    int x;
    int y;
    float distOrigem;
} Point;

float distOrigem(int xInt, int yInt);
float distCustom(float xSrc, float ySrc, float xDst, float yDst);
void insertionSortCustom(Point Points[], int arr[], int n);

int main() {
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L0Q1.in", "r");
    FILE *fp_out = fopen("L0Q1.out", "w");

    // Verifica se os arquivos foram abertos com sucesso
    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n");
        return EXIT_FAILURE;
    }

    char line[1000] = "";
    bool firstRun = false;  // preciso dessa variavel para poder printar corretamente as quebras de linhas no final do código
    // Loop para ler cada linha do arquivo de entrada
    while (fgets(line, 1000, fp_in) != NULL) {
        //! (1) É thread-safe (2) NÃO modifica a string original :)

        Point Points[500];

        int PointCount = 0;
        char xString[30] = "";  // automaticamente seta todos os valores para '\0'
        int xStringCount = 0;
        char yString[30] = "";  // automaticamente seta todos os valores para '\0'
        int yStringCount = 0;

        bool triggerPointStart = false;
        bool triggerPointComma = false;

        // Loop para processar cada ponto na linha
        for (int i = 0; line[i] != '\n' && line[i] != '\0'; i++) {
            if (line[i] == '(') {
                triggerPointStart = true;
                continue;  // pula esse caractere
            }
            if (line[i] == ',') {
                triggerPointComma = true;
                continue;  // pula esse caractere
            }
            if (line[i] == ')') {
                // reseta os valores
                triggerPointStart = false;
                triggerPointComma = false;
                xStringCount = 0;
                yStringCount = 0;
                ////printf("(%s,%s) ", xString, yString);
                int xInt = atoi(xString);
                int yInt = atoi(yString);
                ////printf("(%d,%d) ", xInt, yInt);
                memset(xString, 0, sizeof(xString));  // seta todos os valores da string para \0
                memset(yString, 0, sizeof(yString));  // seta todos os valores da string para \0
                Points[PointCount].x = xInt;
                Points[PointCount].y = yInt;
                Points[PointCount].distOrigem = distOrigem(xInt, yInt);
                ////printf(" dist origin(%.2f) ", Points[PointCount].distOrigem);
                PointCount++;
                continue;  // pula esse caractere
            }
            if (triggerPointStart && !triggerPointComma) {
                xString[xStringCount] = line[i];
                xStringCount++;
            }
            if (triggerPointStart && triggerPointComma) {
                yString[yStringCount] = line[i];
                yStringCount++;
            }
        }
        ////printf("\n");

        // calcula sa distancias
        float EuclidianDistance = 0;
        float xStart = Points[0].x;
        float yStart = Points[0].y;
        for (int p = 1; p < PointCount && PointCount > 1; p++) {
            float distance = distCustom(xStart, yStart, Points[p].x, Points[p].y);
            EuclidianDistance = EuclidianDistance + distance;
            xStart = Points[p].x;
            yStart = Points[p].y;
        }
        /////printf("Euclidian Distance = %.2f\n", EuclidianDistance);

        float EuclidianShortcut = 0;
        if (PointCount > 1) {
            EuclidianShortcut = distCustom(Points[0].x, Points[0].y, Points[PointCount - 1].x, Points[PointCount - 1].y);
        }
        ////printf("Euclidian Shortcut = %.2f\n", EuclidianShortcut);

        // Dynamically allocate memory for an array of 'n' integers
        int *p_PointList = (int *)malloc(PointCount * sizeof(int));

        // Verifica se foi possivel alocar memoria
        if (p_PointList == NULL) {
            printf("Memory allocation failed.\n");
            return EXIT_FAILURE;
        }

        // Inicializa os valores da array em ordem numerica (nao faz diferenca a ordem pois vais er organizado depois)(sim isso e apenas uma array com valores [0,1,2,3,4...])
        for (int i = 0; i < PointCount; i++) {
            p_PointList[i] = i;
        }

        insertionSortCustom(Points, p_PointList, PointCount);  // organiza a arr p_PointList com base nos valores de cada um dos structs.distOrigem

        // escreve todos os resultados no arquivo de saida
        if (firstRun) {
            fprintf(fp_out, "\n");
        }
        firstRun = true;  // preciso de setar essa flag para a formatação sair correta e nao colocar um \n extra no final
        fprintf(fp_out, "points ");
        for (int n = 0; n < PointCount; n++) {
            fprintf(fp_out, "(%d,%d) ", Points[p_PointList[n]].x, Points[p_PointList[n]].y);
        }
        fprintf(fp_out, "distance %.2f ", EuclidianDistance);
        fprintf(fp_out, "shortcut %.2f", EuclidianShortcut);

        free(p_PointList);
    }

    fclose(fp_in);        // Fecha o arquivo de entrada
    fclose(fp_out);       // Fecha o arquivo de saída
    return EXIT_SUCCESS;  // Retorna um código de sucesso
}

float distOrigem(int xInt, int yInt) {
    int A = xInt * xInt;
    int B = yInt * yInt;
    int C = A + B;
    float result = sqrt(C);
    return result;
}

float distCustom(float xSrc, float ySrc, float xDst, float yDst) {
    float xDiff = xDst - xSrc;
    float yDiff = yDst - ySrc;

    float A = xDiff * xDiff;
    float B = yDiff * yDiff;
    float C = A + B;
    float result = sqrt(C);
    return result;
}

void insertionSortCustom(Point Points[], int arr[], int n) {
    //! mestre GePeTo
    int i, j, key;

    // Traverse through 1 to n-1
    for (i = 1; i < n; i++) {
        key = arr[i];  // The index of the current point to be inserted
        j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key (based on distOrigem), one position ahead of their current position
        while (j >= 0 && Points[arr[j]].distOrigem > Points[key].distOrigem) {
            arr[j + 1] = arr[j];  // Shift the index to the right
            j = j - 1;
        }
        // Insert the key at the correct position in the arr
        arr[j + 1] = key;
    }

    ////for (int k = 0; k < n; k++) {
    ////    printf("Point (%d, %d), Distance: %.2f\n", Points[arr[k]].x, Points[arr[k]].y, Points[arr[k]].distOrigem);
    ////}
    ////printf("\n");
}
