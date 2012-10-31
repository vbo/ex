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

class RBTree {
    Node* root;

public:
    RBTree() : root(NULL) {}
    ~RBTree() { free(root); }

    void dump() {
        return dump(root, "");
    }

    Node* insert(const int data) {
        return insert(&(root), data, NULL);
    }

    Node* find(const int data) {
        return find(root, data);
    }

private:
    Node* insert(Node** node, const int data, Node* parent) {
        if (!*node) {
            *node = new Node();
            Node *n = *node;
            n->data = data;
            n->parent = parent;
            balance_after_insert(n);
            return n;
        }
        int val = (*node)->data;
        if (val == data) {
            return *node;
        }
        Node **place;
        if (val < data) {
            place = &((*node)->right);
        } else {
            place = &((*node)->left);
        }
        return insert(place, data, *node);
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
        }
        return find(root->left, data);
    }

    void dump(Node* node, std::string offset) {
        if (offset.length() == 0) {
            node = this->root;
        }
        if (!node) {
            return;
        }
        dump(node->right, offset + "r\t");
        std::cout << offset << (node->color == BLACK ? "b" : "r") << node->data << std::endl;
        dump(node->left, offset + "l\t");
    }

    void rotate_right(Node* n) {
        Node *pivot = n->left;
        n->left = pivot->right;
        pivot->right = n;
        pivot->parent = n->parent;
        n->parent = pivot;
        Node *parent = pivot->parent;
        if (!parent) {
            root = pivot;
            return;
        }
        if (parent->left == n) {
            parent->left = pivot;
        }
        parent->right = pivot;
    }

    void rotate_left(Node* n) {
        Node *pivot = n->right;
        n->right = pivot->left;
        pivot->left = n;
        pivot->parent = n->parent;
        n->parent = pivot;
        Node *parent = pivot->parent;
        if (!parent) {
            root = pivot;
            return;
        }
        if (parent->left == n) {
            parent->left = pivot;
        }
        parent->right = pivot;
    }

    void free(Node* n) {
        if (!n) {
            return;
        }
        free(n->left);
        free(n->right);
        delete n;
    }

    void balance_after_insert(Node* n) {
        n->color = RED;
        if (!n->parent) {
            n->color = BLACK;
            return;
        }
        if (n->parent->color == BLACK) {
            return;
        }
        // If we are here our parent is RED
        // so we probably need to repaint it
        // Checking the uncle
        Node *u = n->uncle();
        Node *g = n->grandparent();
        if (u && u->color == RED) {
            // Parent and uncle are both RED
            // Repainting both to black and begin a recursion
            n->parent->color = BLACK;
            u->color = BLACK;
            g->color = RED;
            balance_after_insert(g);
            return;
        }
        // RED parent and BLACK(!) uncle
        // We need to rotate it, but sometimes it can be done in two steps
        // Perform rotation to line-up red nodes first if needed
        if ((n == n->parent->left) && (n->parent == g->right)) {
            rotate_right(n->parent);
            n = n->right;
        } else if ((n == n->parent->right) && (n->parent == g->left)) {
            rotate_left(n->parent);
            n = n->left;
        }
        // Nodes are lined-up
        // Rotate grandparent
        n->parent->color = BLACK;
        g = n->grandparent();
        g->color = RED;
        if (n == n->parent->left) {
            rotate_right(g);
        } else {
            rotate_left(g);
        }
    }
};

int main() {
    RBTree tree;
    tree.insert(800);
    tree.insert(1500);
    tree.insert(2000);
    tree.insert(900);
    tree.insert(1900);
    tree.insert(500);
    tree.insert(5900);
    tree.insert(8900);
    tree.dump();
}

