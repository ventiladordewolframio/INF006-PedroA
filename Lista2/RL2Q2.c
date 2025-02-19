#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IndexElemento = 0;
int TotalElementos = 0;
int AlturaAtual = 0;
int MaiorAltura = -1;
int SegundaMaiorAltura = -1;
int CompararMaiorAltura = 0;
struct Node* MaiorNode = NULL;
struct Node* SegundoMaiorNode = NULL;

// Define the structure for a node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to create a new node
struct Node* newNode(int data, int height) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data;
    node->height = height;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a new node in the binary search tree
struct Node* insert(struct Node* root, int data) {
    // If the tree is empty, return a new node
    if (root == NULL) {
        struct Node* NewNode = newNode(data, AlturaAtual);

        if (CompararMaiorAltura > MaiorAltura) {
            SegundaMaiorAltura = MaiorAltura;
            SegundoMaiorNode = MaiorNode;
            MaiorAltura = CompararMaiorAltura;
            MaiorNode = NewNode;
        }

        return NewNode;
    }
    AlturaAtual++;
    CompararMaiorAltura++;
    // Otherwise, recur down the tree
    if (data < root->data) {
        // Data is smaller, insert in the left subtree
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        // Data is greater, insert in the right subtree
        root->right = insert(root->right, data);
    }

    // Return the (unchanged) node pointer
    return root;
}

void preOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    TotalElementos++;
    printf("\nIns>%d", root->data);
    preOrder(root->left);
    preOrder(root->right);
}
void preOrderInsertArray(struct Node* root, int* array) {
    if (root == NULL) {
        return;
    }
    array[IndexElemento] = root->data;
    IndexElemento++;
    preOrderInsertArray(root->left, array);
    preOrderInsertArray(root->right, array);
}
void preOrderTotalSum_LEFT(struct Node* root, int* result) {
    if (root == NULL) {
        return;
    }
    *result = *result - root->data;
    preOrderTotalSum_LEFT(root->left, result);
    preOrderTotalSum_LEFT(root->right, result);
}
void preOrderTotalSum_RIGHT(struct Node* root, int* result) {
    if (root == NULL) {
        return;
    }
    *result = *result + root->data;
    preOrderTotalSum_RIGHT(root->left, result);
    preOrderTotalSum_RIGHT(root->right, result);
}
void preOrderTotalSum(struct Node* root, int* result) {
    if (root == NULL) {
        return;
    }
    preOrderTotalSum_LEFT(root->left, result);
    preOrderTotalSum_RIGHT(root->right, result);
}
void deleteTree(struct Node* root) {
    if (root == NULL) return;

    /* first delete both subtrees */
    deleteTree(root->left);
    deleteTree(root->right);

    /* then delete the root */
    printf("\nDel>%d", root->data);
    free(root);
}
void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
struct Node* binSearch(struct Node* root, int data) {  // caso o elemento nao exista isso aqui vai ficar num loop infinito mas nao e necessario para esse caso
    while (root->data != data) {
        if (root->data > data) {
            root = root->left;
        } else if (root->data < data) {
            root = root->right;
        }
    }
    return root;
}
int diferencaNode(struct Node* root) {
}

int main() {
    FILE* file = fopen("L2Q2.in", "r+");
    FILE* file_out = fopen("L2Q2.out", "w");
    if (!file) {
        return 0;
    }
    printf("File exists.\n\n");
    struct Node* root = NULL;
    char buff[10000];
    char* token;
    char* save1 = NULL;

    int firstTime = 1;
    while (fgets(buff, sizeof(buff), file)) {  // enquanto houver linhas, pegue elas
        if (!firstTime) {
            fprintf(file_out, "\n");
        }
        firstTime = 0;

        int len = strlen(buff);
        if (len > 0 && buff[len - 1] == '\n') {  // se o ultimo caractere for "\n" remova. (a ultima linha nao tem "\n")
            buff[len - 1] = '\0';
        }
        printf("|%s| > str buff\n", buff);

        token = strtok_r(buff, " ", &save1);  // pega o primeiro dos tokens de forma segura (pode usar nested pq é recursivo, so mudar o &save)

        while (token != NULL) {  // enquanto houver tokens
            int number = atoi(token);
            printf("|%d", number);
            //* <codigo que processa os tokens>
            root = insert(root, number);
            // fprintf(file_out, "%d ", AlturaAtual);
            AlturaAtual = 0;
            CompararMaiorAltura = 0;
            //* </codigo que processa os tokens>
            token = strtok_r(NULL, " ", &save1);  // pega o proximo
        }

        //* <vizualiza e limpa a arvore binaria>
        printf("| > int\n\n");
        // if (SegundoMaiorNode != NULL) {
        //     fprintf(file_out, "max %d alt %d pred %d", MaiorNode->data, MaiorAltura, SegundoMaiorNode->data);
        // } else {
        //     fprintf(file_out, "max %d alt %d pred NaN", MaiorNode->data, MaiorAltura);
        // }
        MaiorAltura = -1;
        SegundaMaiorAltura = -1;
        MaiorNode = NULL;
        SegundoMaiorNode = NULL;
        printf("Pre-order Traversal of the BST: ");
        preOrder(root);
        //* <prepara os dados>
        printf("\n\nQTD ELEMENTOS |%d|\n", TotalElementos);
        int* arrayElementos = (int*)malloc(TotalElementos * sizeof(int));
        preOrderInsertArray(root, arrayElementos);
        insertionSort(arrayElementos, TotalElementos);
        int firstTime2 = 1;
        for (int i = 0; i < TotalElementos; i++) {
            // printf("ARRAY=>|%d|\n", arrayElementos[i]);
            int somaTotal = 0;
            struct Node* NodeElemento = binSearch(root, arrayElementos[i]);
            preOrderTotalSum(NodeElemento, &somaTotal);
            ////somaTotal = somaTotal - NodeElemento->data;
            if (!firstTime2) {
                fprintf(file_out, " %d (%d)", arrayElementos[i], somaTotal);
            } else {
                fprintf(file_out, "%d (%d)", arrayElementos[i], somaTotal);
            }
            firstTime2 = 0;
        }
        //* </prepara os dados>
        free(arrayElementos);
        printf("\n\nPost-order Deletion Traversal of the BST: ");
        deleteTree(root);
        printf("\n\n");
        root = NULL;
        TotalElementos = 0;
        IndexElemento = 0;
        //* </vizualiza e limpa a arvore binaria>
    }
    return 0;
}
