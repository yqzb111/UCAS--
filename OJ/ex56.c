#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct word {
    union {
        struct word *llink;  // 头部域，指向前驱节点
        struct word *uplink; // 尾部域，指向本结点的头部
    };
    int tag;                 // 0表示空闲，1表示占用
    int addr;                // 起始地址
    int size;                // 块大小
    struct word *rlink;      // 头部域，指向后继节点
} Space;

// 打印空闲块链表
void print_free_list(Space *head, int num) {
    Space *current = head;
    int count = 0;
    while (current != NULL) {
        if(current->tag == 0){
            printf("%d %d %d\n", current->tag, current->addr, current->size);
        }
        else if(current->tag == 1){
            count++;
        }
        current = current->rlink;
    }
    if(count == num)
        printf("0 0 0\n");
}

// 创建新节点
Space* create_node(int tag, int addr, int size) {
    Space *new_node = (Space *)malloc(sizeof(Space));
    new_node->tag = tag;
    new_node->addr = addr;
    new_node->size = size;
    new_node->rlink = NULL;
    new_node->llink = NULL;
    return new_node;
}

// 插入节点到链表中
void insert_node(Space **head, Space *new_node) {
    if (*head == NULL) {
        *head = new_node;
    } else {
        Space *current = *head;
        while (current->rlink != NULL && current->addr <= new_node->addr) {
            current = current->rlink;
        }
        if(!current->rlink && current->addr <= new_node->addr){
            current->rlink = new_node;
            new_node->llink = current;
        }
        else if(current->addr > new_node->addr){
            new_node->llink = current->llink;
            new_node->rlink = current;
            current->llink->rlink = new_node;
            current->llink = new_node;
        }
    }
}

// 合并相邻的空闲块
void merge_free_blocks(Space *head) {
    Space *current = head;
    while (current != NULL && current->rlink != NULL) {
        Space *next = current->rlink;
        if (current->tag == 0 && next->tag == 0) {
            if (current->addr + current->size == next->addr) {
                current->size += next->size;
                current->rlink = next->rlink;
                if (next->rlink != NULL) {
                    next->rlink->llink = current;
                }
                free(next);
            } else {
                current = current->rlink;
            }
        } else {
            current = current->rlink;
        }
    }
}

int main() {
    Space *free_list = NULL;
    int size;
    int highbound,lowbound;
    int tag[20];
    int i;
    scanf("%d%d%d",&highbound,&lowbound,&size);
    for(i=0;i<20;i++)
        tag[i] = -1;
    for(i=0;i<(lowbound-highbound)/size;i++){
        scanf("%d",&tag[i]);
        Space *new_node = create_node(tag[i], highbound+size*i, size);
        insert_node(&free_list, new_node);
    }
    // 合并相邻的空闲块
    merge_free_blocks(free_list);
    // 输出回收后的空闲块状态
    print_free_list(free_list, (lowbound-highbound)/size);
    return 0;
}