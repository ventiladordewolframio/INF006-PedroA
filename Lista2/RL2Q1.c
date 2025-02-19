#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a new node in the binary search tree
struct Node* insert(struct Node* root, int data) {
    // If the tree is empty, return a new node
    if (root == NULL) {
        struct Node* NewNode = newNode(data);

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
    } else if (data >= root->data) {
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
    printf("\nIns>%d", root->data);
    preOrder(root->left);
    preOrder(root->right);
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

int main() {
    FILE* file = fopen("L2Q1.in", "r+");
    FILE* file_out = fopen("L2Q1.out", "w");
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
        if(!firstTime){
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
            fprintf(file_out, "%d ", AlturaAtual);
            AlturaAtual = 0;
            CompararMaiorAltura = 0;
            //* </codigo que processa os tokens>
            token = strtok_r(NULL, " ", &save1);  // pega o proximo
        }

        //* <vizualiza e limpa a arvore binaria>
        printf("| > int\n\n");
        if (SegundoMaiorNode != NULL) {
            fprintf(file_out, "max %d alt %d pred %d", MaiorNode->data, MaiorAltura, SegundoMaiorNode->data);
        } else {
            fprintf(file_out, "max %d alt %d pred NaN", MaiorNode->data, MaiorAltura);
        }
        MaiorAltura = -1;
        SegundaMaiorAltura = -1;
        MaiorNode = NULL;
        SegundoMaiorNode = NULL;
        printf("Pre-order Traversal of the BST: ");
        preOrder(root);
        printf("\n\nPost-order Deletion Traversal of the BST: ");
        deleteTree(root);
        printf("\n\n");
        root = NULL;
        //* </vizualiza e limpa a arvore binaria>
    }
    return 0;
}
