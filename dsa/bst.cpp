#include <iostream>
#include <string>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* find_recursive(Node* root, const int data) {
    if (!root) {
        return NULL;
    }
    int val = root->data;
    if (val == data){
        return root;
    }
    if (val < data) {
        return find_recursive(root->right, data);
    } else {
        return find_recursive(root->left, data);
    }
}

Node* find_imperative(Node* root, const int data) {
    Node *current = root;
    int val;
    while(current) {
        val = current->data;
        if (val == data) {
            return current;
        }
        if (val < data) {
            current = current->right;
            continue;
        }
        if (val > data) {
            current = current->left;
        }
    }
    return NULL;
}

Node* insert(Node** root, const int data) {
    if (!*root) {
        *root = new Node();
        (*root)->data = data;
        return *root;
    }
    int val = (*root)->data;
    if (val == data) {
        return *root;
    }
    if (val < data) {
        return insert(&((*root)->right), data);
    } else {
        return insert(&((*root)->left), data);
    }
}

void dump(Node* root, std::string offset = "") {
    if (!root) {
        return;
    }
    std::cout << offset << root->data << std::endl;
    dump(root->right, offset + "r\t");
    dump(root->left, offset + "l\t");
}

int main() {
    Node *root = NULL;
    insert(&root, 1000);
    insert(&root, 700);
    Node *one_thousand_hundred = insert(&root, 1100);
    insert(&root, 950);
    Node *nine_hundred = insert(&root, 900);
    insert(&root, 960);
    dump(root);

    Node *tmp;
    if (one_thousand_hundred != (tmp = find_recursive(root, 1100))) {
        std::cout << "recursive search failed" << std::endl;
    }
    std::cout << "TMP: " << tmp->data << std::endl;
    if (nine_hundred != (tmp = find_imperative(root, 900))) {
        std::cout << "imperative search failed" << std::endl;
    }
    std::cout << "TMP: " << tmp->data << std::endl;
    if (find_recursive(root, 100500)) {
        std::cout << "recursion is magic" << std::endl;
    }
    if ((tmp = find_imperative(root, 100500))) {
        std::cout << "imperative is magic" << std::endl;
    }
    return (int) tmp;
}
