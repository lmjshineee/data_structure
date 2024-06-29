#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createList(int n) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    Node* current = head;
    for (int i = 0; i < n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i + 1;
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}

void printList(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    int n;
    printf("Enter the size of the list: ");
    scanf("%d", &n);

    Node* head = createList(n);
    printf("Created list: ");
    printList(head);

    return 0;
}