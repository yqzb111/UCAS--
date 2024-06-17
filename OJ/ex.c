#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int elem;
    struct node* next;
} Node;

typedef struct {
    Node* h;
    Node* t;
} SSTable;

// 创建新节点
Node* createNode(int elem) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->elem = elem;
    newNode->next = NULL;
    return newNode;
}

// 初始化循环链表
SSTable* initTable() {
    SSTable* table = (SSTable*)malloc(sizeof(SSTable));
    table->h = table->t = NULL;
    return table;
}

// 插入节点到循环链表
void insert(SSTable* table, int elem) {
    Node* newNode = createNode(elem);
    if (table->h == NULL) {
        table->h = table->t = newNode;
        newNode->next = newNode;  // 自己指向自己形成循环
    } else {
        newNode->next = table->t->next;
        table->t->next = newNode;
        table->t = newNode;
    }
}

// 查找函数
int SearchSSTable(SSTable* table, int key) {
    if (table->h == NULL) return 0; // 空表

    if (table->t->elem == key) return 1;

    Node* start = (key < table->t->elem) ? table->h : table->t->next;
    Node* current = start;

    do {
        if (current->elem == key) {
            table->t = current;
            return 1;
        }
        current = current->next;
    } while (current != start);

    return 0;
}

int main() {
    SSTable* table = initTable();
    int e;
    char c;

    // 读入顺序表中的元素
    while (scanf("%d", &e) != EOF) {
        insert(table, e);
        c = getchar();
        if (c == '\n') break;
    }

    // 处理查找请求
    while (scanf("%d", &e) != EOF) {
        int result = SearchSSTable(table, e);
        printf("%d", result);
        c = getchar();
        if (c == '\n') {
            printf("\n");
            break;
        } else {
            printf(" ");
        }
    }

    return 0;
}
