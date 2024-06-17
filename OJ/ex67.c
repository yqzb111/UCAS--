#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新的链表节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 将节点添加到链表的末尾
void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// 实现简单选择排序
void selectionSort(Node* head) {
    Node *a, *b, *min;
    int temp;
    for (a = head; a->next != NULL; a = a->next) {
        min = a;
        for (b = a->next; b != NULL; b = b->next) {
            if (b->data < min->data) {
                min = b;
            }
        }
        temp = a->data;
        a->data = min->data;
        min->data = temp;
    }
}

// 打印链表
void printList(Node* head) {
    Node* current = head;
    while (current->next != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("%d\n",current->data);
}

int main() {
    Node* head = NULL;
    char line[400];
    fgets(line, sizeof(line), stdin);
    char *token = strtok(line, " ");
    while (token != NULL) {
        append(&head, atoi(token));
        token = strtok(NULL, " ");
    }
    selectionSort(head);
    printList(head);
    return 0;
}
