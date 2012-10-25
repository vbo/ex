#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;

    Node* grandparent() {
        if (!parent) {
            return NULL;
        }
        return parent->parent;
    }
    Node* uncle() {
        Node *grand = grandparent();
        if (!grand) {
            return NULL;
        }
        if (grand->left == parent) {
            return grand->right;
        }
        return grand->left;
    }
};

void balance(Node** root);

Node* insert(Node** root, const int data, Node* parent = NULL) {
    if (!*root) {
        *root = new Node();
        (*root)->data = data;
        (*root)->parent = parent;
        balance(root);
        return *root;
    }
    int val = (*root)->data;
    if (val == data) {
        return *root;
    }
    Node **place;
    if (val < data) {
        place = &((*root)->right);
    } else {
        place = &((*root)->left);
    }
    return insert(place, data, *root);
}

void balance(Node** root) {
    (*root)->color = RED;
    if (!(*root)->parent) {
        (*root)->color = BLACK;
        return;
    }
    if ((*root)->parent->color == BLACK) {
        // tree is still valid
        return;
    }
    Node *u = uncle(*root);
    if (u && u->color == RED) {
        // parent and uncle is RED
    }
}

Node* find(Node* root, const int data) {
    if (!root) {
        return NULL;
    }
    int val = root->data;
    if (val == data){
        return root;
    }
    if (val < data) {
        return find(root->right, data);
    } else {
        return find(root->left, data);
    }
}

int main() {
    Node *root = NULL;
    insert(&root, 1000);
    insert(&root, 1100);
    insert(&root, 1120);
}

