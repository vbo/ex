#include <stdlib.h>
#include <stdio.h>

// Implementing stack in vanilla C via linked list
// to understand the difference from C++ (see stack.cpp)

typedef struct NodeT {
    int data;
    struct NodeT* next;
} Node;

int push(Node** head, int data) {
    Node *new_head = malloc(sizeof(Node));
    if (!new_head) {
        return 0;
    }
    new_head->data = data;
    new_head->next = *head;
    *head = new_head;
    return 1;
}

int pop(Node** head, int* data) {
    Node *old_head = *head;
    if (!old_head) {
        return 0;
    }
    Node *new_head = old_head->next;
    *data = old_head->data;
    *head = new_head;
    free(old_head);
    return 1;
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
        printf("%d\n", tmp);
    }

    return (int) head > 0;
}

