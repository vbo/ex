#include <iostream>

// Implementing stack via linked list

struct Node {
    int data;
    Node* next;
};

bool push(Node** head, int data) {
    Node *new_head = new Node();
    if (!new_head) {
        return false;
    }
    new_head->data = data;
    new_head->next = *head;
    *head = new_head;
    return true;
}

bool pop(Node** head, int* data) {
    Node *old_head = *head;
    if (!old_head) {
        return false;
    }
    Node *new_head = old_head->next;
    *data = old_head->data;
    delete old_head;
    *head = new_head;
    return true;
}

int main() {
    Node *head = NULL;
    int tmp;

    push(&head, 1);
    push(&head, 10);
    push(&head, 100);
    push(&head, 1000);

    pop(&head, &tmp);

    push(&head, 10000);

    while(pop(&head, &tmp)) {
        std::cout << tmp << std::endl;
    }

    return (int) head > 0;
}
