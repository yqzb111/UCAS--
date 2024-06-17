#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Error! Unable to create a new node\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void sortedInsert(Node** head, Node* newNode) {
    Node* current;
    if (*head == NULL || (*head)->data >= newNode->data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        current = *head;
        while (current->next != NULL && current->next->data < newNode->data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void insertionSort(Node **head) {
    Node *sorted = NULL;
    Node *current = *head;
    while (current != NULL) {
        Node *next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *head = sorted;
}

void printList(Node *head) {
    Node *temp = head;
    while(temp->next != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n",temp->data);
}

int main() {
    Node *head = NULL;
    int n, i, data;
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d", &data);
        Node *newNode = createNode(data);
        newNode->next = head;
        head = newNode;
    }
    insertionSort(&head);
    printList(head);
    return 0;
}
