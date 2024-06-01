#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a node of the binary search tree
struct Node {
    int roll;
    char name[50];
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int roll, char* name) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    temp->roll = roll;
    strcpy(temp->name, name);
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new node into the BST
struct Node* insert(struct Node* root, int roll, char* name) {
    if (root == NULL) 
        return newNode(roll, name);
    
    if (roll < root->roll)
        root->left = insert(root->left, roll, name);
    else if (roll > root->roll)
        root->right = insert(root->right, roll, name);
    
    return root;
}

// Function to print the key value pairs in the binary search tree
void printBST(struct Node* root) {
    if (root != NULL) {
        printBST(root->left);
        printf("Roll: %d, Name: %s\n", root->roll, root->name);
        printBST(root->right);
    }
}

int main() {
    FILE *fp;
    int n, roll;
    char name[50];
    
    // Opening the file
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    // Reading the number of students
    if (fscanf(fp, "%d", &n) != 1) {
        printf("Error reading number of students.\n");
        fclose(fp);
        return 1;
    }
    
    // Creating a root node for the BST
    struct Node* root = NULL;
    
    // Reading and inserting key value pairs into the BST
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d %s", &roll, name) != 2) {
            printf("Error reading student data.\n");
            fclose(fp);
            return 1;
        }
        root = insert(root, roll, name);
    }
    
    // Closing the file
    fclose(fp);
    
    // Printing the key value pairs in the BST
    printf("Key value pairs in the binary search tree:\n");
    printBST(root);
    
    return 0;
}
e