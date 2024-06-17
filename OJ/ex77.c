#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node {
    int data;  // 节点存储的数据
    struct Node* next;  // 指向下一个节点的指针
} Node;

// 创建新的链表节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 分配内存空间
    newNode->data = data;  // 设置节点数据
    newNode->next = NULL;  // 设置下一个节点为NULL
    return newNode;  // 返回新创建的节点
}

// 将节点添加到链表的末尾
void append(Node** head, int data) {
    Node* newNode = createNode(data);  // 创建新节点
    if (*head == NULL) {  // 如果链表为空
        *head = newNode;  // 新节点就是头节点
        return;
    }
    Node* current = *head;  // 从头节点开始
    while (current->next != NULL) {  // 遍历链表，找到最后一个节点
        current = current->next;
    }
    current->next = newNode;  // 将新节点添加到最后一个节点的后面
}

// 2-路归并排序函数
Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {  // 如果链表为空或只有一个节点
        return head;  // 直接返回头节点
    }
    Node* slow = head;  // 慢指针，每次移动一步
    Node* fast = head->next;  // 快指针，每次移动两步
    while (fast != NULL && fast->next != NULL) {  // 当快指针没有到达链表尾部时
        slow = slow->next;  // 慢指针移动一步
        fast = fast->next->next;  // 快指针移动两步
    }
    Node* head1 = head;  // 第一个子链表的头节点
    Node* head2 = slow->next;  // 第二个子链表的头节点
    slow->next = NULL;  // 将链表分割成两个子链表
    Node* left = mergeSort(head1);  // 对第一个子链表进行归并排序
    Node* right = mergeSort(head2);  // 对第二个子链表进行归并排序
    Node dummy;  // 创建一个哑节点，用于方便操作
    Node* current = &dummy;  // 创建一个当前节点，初始化为哑节点
    while (left != NULL && right != NULL) {  // 当两个子链表都不为空时
        if (left->data < right->data) {  // 如果左子链表的头节点小于右子链表的头节点
            current->next = left;  // 将左子链表的头节点添加到当前节点的后面
            left = left->next;  // 左子链表的头节点向后移动一步
        } else {  // 否则
            current->next = right;  // 将右子链表的头节点添加到当前节点的后面
            right = right->next;  // 右子链表的头节点向后移动一步
        }
        current = current->next;  // 当前节点向后移动一步
    }
    if (left != NULL) {  // 如果左子链表还有剩余节点
        current->next = left;  // 将剩余节点添加到当前节点的后面
    } else {  // 否则
        current->next = right;  // 将右子链表的剩余节点添加到当前节点的后面
    }
    return dummy.next;  // 返回排序后的链表的头节点
}

// 打印链表
void printList(Node* head) {
    Node* current = head;  // 从头节点开始
    while (current != NULL) {  // 当当前节点不为空时
        printf("%d ", current->data);  // 打印当前节点的数据
        current = current->next;  // 当前节点向后移动一步
    }
    printf("\n");  // 打印一个换行符
}

int main() {
    Node* head = NULL;  // 创建一个空链表
    int n, data;
    scanf("%d", &n);  // 读取数据元素的个数
    for (int i = 0; i < n; i++) {  // 对于每个数据元素
        scanf("%d", &data);  // 读取数据元素
        append(&head, data);  // 将数据元素添加到链表的末尾
    }
    head = mergeSort(head);  // 对链表进行2-路归并排序
    printList(head);  // 打印排序后的链表
    return 0;
}
