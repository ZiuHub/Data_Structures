#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* buildBST(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = buildBST(root->left, value);
    } else {
        root->right = buildBST(root->right, value);
    }
    return root;
}

int search(Node* root, int value) {
    if (root == NULL) {
        return -1;
    }
    if (root->value == value) {
        return root->value;
    } else if (value < root->value) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->value);
    inOrder(root->right);
}

Node* delNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        root->left = delNode(root->left, value);
    } else if (value > root->value) {
        root->right = delNode(root->right, value);
    } else {
        // node yang ingin dihapus ditemukan
        // case 1: node tidak memiliki anak (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // case 2: node hanya memiliki anak kanan
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        // case 3: node hanya memiliki anak kiri
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // case 4: node memiliki dua anak
        else {
            // menggunakan predecessor (nilai maksimum di subtree kiri)
            Node* temp = root->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            // ganti value node dengan predecessor
            root->value = temp->value;
            // hapus node predecessor dari subtree kiri
            root->left = delNode(root->left, temp->value);
        }
    }
    return root;
}

int main() {
    Node* root = NULL;
    root = buildBST(root, 6);
    root = buildBST(root, 10);
    root = buildBST(root, 3);

    printf("InOrder before deletion: ");
    inOrder(root);
    printf("\n");

    // delete value dari root lalu return root
    root = delNode(root, 3);

    printf("InOrder after deletion: ");
    inOrder(root);
    printf("\n");

    return 0;
}