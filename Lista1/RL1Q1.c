#include <math.h>
#include <stdbool.h>
#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h>  // Inclui a biblioteca padrão com funções gerais, incluindo atoi e EXIT_FAILURE/SUCCESS
#include <string.h>

void insertionSort(int arr[], int n) {
    int i, key, j;

    // Loop through each element starting from index 1
    for (i = 1; i < n; i++) {
        key = arr[i];  // The element to be inserted into the sorted portion
        j = i - 1;     // Index of the last element in the sorted portion

        // Shift elements of the sorted portion of the array that are greater than key
        // to the right by one position to make room for key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // Shift element to the right
            j = j - 1;            // Move to the next element in the sorted portion
        }

        arr[j + 1] = key;  // Place the key at its correct position
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int sumArray(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = result + arr[i];
    }
    return result;
}

int main() {
    // Ponteiros para os arquivos de entrada e saída
    FILE *fp_in = fopen("L1Q1.in", "r");
    FILE *fp_out = fopen("L1Q1.out", "w");

    // Verifica se os arquivos foram abertos com sucesso
    if (fp_in == NULL || fp_out == NULL) {
        printf("Arquivos não podem ser abertos.\n");
        return EXIT_FAILURE;
    }

    typedef struct SubNo {
        int conteudo;
        bool vazio;
        struct SubNo *prox;
    } SubNo;

    typedef struct No {
        struct SubNo *conteudo;
        int largura;
        bool vazio;
        int valorTotal;
        struct No *prox;
    } No;

    No *MainVect = malloc(sizeof(No));

    if (MainVect == NULL) {
        printf("nao pode criar o MainVect");
        return -1;
    }

    MainVect->largura = 0;
    MainVect->vazio = true;
    MainVect->prox = NULL;
    MainVect->conteudo = NULL;
    MainVect->valorTotal = 0;

    char line[1000] = "";
    No *tempNo = MainVect;
    SubNo *tempSubNo = NULL;

    int qtdObject = 0;
    while (fgets(line, 1000, fp_in) != NULL) {  // cada linha
        printf("\n%s\n", line);
        char *tok = strtok(line, " ");
        // printf("\n|%s|\n", tok);

        while (tok != NULL) {  // cada elemento da linha
            if (strcmp(tok, "start") == 0) {
                if (tempNo->vazio) {  // primeiro start
                    tempNo->conteudo = malloc(sizeof(SubNo));
                    tempNo->vazio = false;
                    tempSubNo = tempNo->conteudo;
                    qtdObject++;
                } else {  // start subsequente
                    tempNo->prox = malloc(sizeof(No));
                    tempNo = tempNo->prox;

                    tempNo->largura = 0;
                    tempNo->vazio = false;

                    tempNo->conteudo = malloc(sizeof(SubNo));
                    tempSubNo = tempNo->conteudo;
                    qtdObject++;
                }
            } else {
                tempSubNo->conteudo = atoi(tok);
                tempSubNo->vazio = false;

                tempNo->valorTotal = tempNo->valorTotal + atoi(tok);

                tempSubNo->prox = malloc(sizeof(SubNo));
                // printf(">%d< ", tempSubNo->conteudo);

                tempSubNo->prox->vazio = true;
                tempSubNo->prox->prox = NULL;
                tempSubNo->prox->conteudo = 0;

                tempSubNo = tempSubNo->prox;
                tempNo->largura = tempNo->largura + 1;
                // nem precisa da outra condicao pis comoe ssa funcao apenas escreve e nao le isso nunca vaia contecer (eu acho)
            }

            tok = strtok(NULL, " ");
        }

        //////! NODE SORTING
        ////tempNo = MainVect;
        ////bool swapped;
        ////No *UltimoObj = NULL;
        ////for (int i = 0; i < qtdObject - 1; i++) {
        ////    printf("i = |%d/%d|%d|%d|%d|\n", i, qtdObject, tempNo == NULL, tempNo == NULL, tempNo->prox == NULL);
        ////    swapped = false;
        ////
        ////    for (int j = 0; j < qtdObject - i - 1; j++) {
        ////        printf("TEST1\n");
        ////        if (tempNo != NULL && tempNo->prox != NULL) {
        ////            printf("%d > %d\n", tempNo->valorTotal, tempNo->prox->valorTotal);
        ////        } else if (tempNo != NULL && tempNo->prox == NULL) {
        ////            printf("%d > NULL\n", tempNo->valorTotal);
        ////        } else {
        ////            printf("ERRO ESTRANHO NA COMPARACAO\n");
        ////        }
        ////        printf("TEST2\n");
        ////        if (tempNo->prox == NULL) {
        ////            printf("swap NOT activated (NEXT == NULL)\n");
        ////            UltimoObj == NULL;
        ////            tempNo = MainVect;
        ////            continue;
        ////        }
        ////        if (tempNo->valorTotal > tempNo->prox->valorTotal) {
        ////            // Swap the elements if they are in the wrong order
        ////            printf("swap activated\n");
        ////            No *tempProx = tempNo->prox;
        ////            No *tempAtual = tempNo;
        ////            // printf("KG|%d|", UltimoObj);
        ////            if (UltimoObj == NULL) {
        ////                printf("equals NULL\n");
        ////                tempProx = tempNo->prox;
        ////                tempAtual = tempNo;
        ////                tempNo->prox = tempNo->prox->prox;
        ////                tempProx->prox = tempAtual;
        ////
        ////                // previnir problemas caso o no atual seja o no inicial (deveria ter usado head)
        ////                if (tempAtual == MainVect) {
        ////                    MainVect = tempProx;
        ////                    // printf("activated1");
        ////                }
        ////            } else {
        ////                printf("DOES NOT equals NULL\n");
        ////                tempProx = tempNo->prox;            // proximo elemento
        ////                tempAtual = tempNo;                 // elemento atual
        ////                tempNo->prox = tempNo->prox->prox;  // pointer atual aponta pro pointer do proximo
        ////                tempProx->prox = tempAtual;         // pointer do proximo aponta para o lugar do atual
        ////                UltimoObj->prox = tempProx;
        ////                // printf("foi");
        ////                //  previnir problemas caso o no atual seja o no inicial (deveria ter usado head)
        ////                if (tempAtual == MainVect) {
        ////                    MainVect = tempProx;
        ////                    // printf("activated2");
        ////                }
        ////            }
        ////            // printf("foi2");
        ////            UltimoObj = tempAtual;
        ////            // printf("K|%d|", UltimoObj);
        ////            //  tempNo = tempNo->prox;
        ////            //  arr[j + 1] = temp;
        ////            swapped = true;
        ////        } else {
        ////            printf("swap NOT activated\n");
        ////            UltimoObj = tempNo;
        ////            tempNo = tempNo->prox;
        ////        }
        ////        // printf("foi3");
        ////        // tempNo = tempNo->prox;
        ////        // printf("foi4");
        ////    }
        ////
        ////    // If no elements were swapped, the list is already sorted, so break early
        ////    if (!swapped) {
        ////        break;
        ////    }
        ////    // printf("CHEGOU2");
        ////}
        ////// printf("CHEGOU");
        //! DEBUG PRINTING ++
        printf("QTD(%d)", qtdObject);
        int *ARRelem[qtdObject];
        tempNo = MainVect;
        int j = 0;
        do {
            printf("strt0(%d)",tempNo == NULL);
            int largVect = tempNo->largura;
            int SubVect[largVect];
            tempSubNo = tempNo->conteudo;
            printf(" LEN(%d) ", tempNo->largura);
            for (int i = 0; i < largVect; i++) {
                SubVect[i] = tempSubNo->conteudo;
                tempSubNo = tempSubNo->prox;
            }

            int *TMParr = (int *)malloc(largVect * sizeof(int));
            ARRelem[j] = TMParr;
            j++;

            for (int i = 0; i < largVect; i++) {
                printf(" |%d| ", SubVect[i]);
                TMParr[i] = SubVect[i];
            }
            tempNo = tempNo->prox;
             printf("finish(%d)",tempNo != NULL);
        } while (tempNo != NULL);
         printf("finish2");

        //! VARIABLES RESET
        for (int i = 0; i < 1000; i++) {
            line[i] = '\0';
        }

        tempNo = MainVect;
        tempSubNo = NULL;

        for (int j = 0; true; j++) {
            if (tempNo->prox == NULL && j != 0) {
                free(tempNo);
                break;
            }
             printf("finish3");
            tempSubNo = tempNo->conteudo;
            SubNo *temptempSubNo = NULL;
            while (true) {  // mata todos os subno
                if (tempSubNo->prox == NULL) {
                    free(tempSubNo);
                    break;
                }
                // printf("finish3.5");
                temptempSubNo = tempSubNo->prox;
                free(tempSubNo);
                tempSubNo = temptempSubNo;
            }
            // printf("finish3.8");
            if (j != 0) {
                No *temptempNo = tempNo->prox;
                free(tempNo);
                tempNo = temptempNo;
                // printf("finish3.9");
            } else {
                tempNo = tempNo->prox;
            }
        }
         printf("finish4");
        tempNo = MainVect;
        tempNo->largura = 0;
        tempNo->vazio = true;
        tempNo->prox = NULL;
        tempNo->conteudo = NULL;

        tempSubNo = NULL;

        qtdObject = 0;

        //! REORGANIZAR E PREPARAR SAIDA
        // int TotalArrays[qtdObject];
        // for (int i = 0; i < qtdObject; i++) {
        //     TotalArrays[i] = sumArray(int arr[], int n)
        // }
        printf("TERMINOU2\n");
    }

    printf("TERMINOU\n");
    return 0;
}

// for (int i = 0; i < 1000; i++) {
//     if (line[i] == 's' && i != 0) {
//         i = i + 5;
//         temp->prox = malloc(sizeof(No));
//         temp = temp->prox;
//         temp->conteudo = malloc(sizeof(SubNo));
//         int num = scanf(" %d", &line[i]);
//         do {
//         } while ();
//     }
// }