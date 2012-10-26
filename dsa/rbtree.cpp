#include <iostream>

// TMP
template <class T>
void pr(T m) {
    std::cout << m << std::endl;
}

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

void dump(Node* root, std::string offset = "") {
    if (!root) {
        return;
    }
    dump(root->right, offset + "r\t");
    std::cout << offset << (root->color == BLACK ? "b" : "r") << root->data << std::endl;
    dump(root->left, offset + "l\t");
}

void rotate_right(Node* n) {
    pr("rotating over");
    pr(n->data);
    Node *pivot = n->left;
    n->left = pivot->right;
    pivot->right = n;
    pivot->parent = n->parent;
    n->parent = pivot;
    Node *parent = pivot->parent;
    if (!parent) return;
    if (parent->left == n) {
        parent->left = pivot;
    } else {
        parent->right = pivot;
    }
}

void rotate_left(Node* n) {
    pr("rotating over");
    pr(n->data);
    Node *pivot = n->right;
    n->right = pivot->left;
    pivot->left = n;
    pivot->parent = n->parent;
    n->parent = pivot;
    Node *parent = pivot->parent;
    if (!parent) return;
    if (parent->left == n) {
        parent->left = pivot;
    } else {
        parent->right = pivot;
    }
}

// Rebalance tree afte insert
// Warn: tree head may be actually changed after rebalance
void balance(Node* n) {
    n->color = RED;
    if (!n->parent) {
        // It's a tree head
        pr("head!");
        n->color = BLACK;
        return;
    }
    if (n->parent->color == BLACK) {
        // tree is still valid
        pr("tree valid");
        return;
    }
    Node *u = n->uncle();
    Node *g = n->grandparent();
    if (u && u->color == RED) {
        // parent and uncle are RED
        pr("parent and uncle are RED");
        n->parent->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        balance(g);
        return;
    }
    // RED parent and BLACK uncle
    pr("RED parent and BLACK uncle");
    // Perform rotation to line-up red nodes if needed
    if ((n == n->parent->left) && (n->parent == g->right)) {
        pr("right!!!");
        rotate_right(n->parent);
        n = n->right;
    } else if ((n == n->parent->right) && (n->parent == g->left)) {
        pr("left!!!");
        rotate_left(n->parent);
        n = n->left;
    }
    // Nodes are lined-up
    // Rotate grandparent
    pr("rotation after line-up");
    n->parent->color = BLACK;
    g->color = RED;
    if (n == n->parent->left) {
        pr("right");
        rotate_right(g);
    } else {
        pr("left");
        rotate_left(g);
    }
}

Node* insert(Node** root, const int data, Node* parent = NULL) {
    if (!*root) {
        *root = new Node();
        Node *n = *root;
        n->data = data;
        n->parent = parent;
        balance(n);
        return n;
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
    pr("insert 1000");
    insert(&root, 1000);
    while(root->parent) root = root->parent;
    dump(root);
    pr("insert 1100");
    insert(&root, 1100);
    while(root->parent) root = root->parent;
    dump(root);
    pr("insert 1120");
    insert(&root, 1120);
    while(root->parent) root = root->parent;
    dump(root);
    insert(&root, 1130);
    while(root->parent) root = root->parent;
    dump(root);
    insert(&root, 1200);
    while(root->parent) root = root->parent;
    dump(root);
    insert(&root, 500);
    while(root->parent) root = root->parent;
    dump(root);
    insert(&root, 1500);
    while(root->parent) root = root->parent;
    dump(root);
    insert(&root, 1700);
    while(root->parent) root = root->parent;
    dump(root);
}

