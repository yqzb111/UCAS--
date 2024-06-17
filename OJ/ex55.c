#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct WORD_b {
    struct WORD_b *llink;  // 头部域，指向前驱节点
    int kval;              // 块的大小的幂次
    int addr;              // 起始地址
    int size;              // 块大小
    int body;              //伙伴的地址
    struct WORD_b *rlink;  // 头部域，指向后继节点
} WORD_b;

// 打印空闲块链表
void print_free_list(WORD_b *head) {
    if (head == NULL) return;
    WORD_b *current = head;
    int current_kval = current->kval;
    printf("%d", current_kval);
    while (current != NULL) {
        if (current->kval != current_kval) {
            printf("\n%d", current->kval);
            current_kval = current->kval;
        }
        printf(" %d", current->addr);
        current = current->rlink;
    }
    printf("\n");  // 输出最后一行后换行
}

// 创建新节点
WORD_b* create_node(int kval, int addr) {
    WORD_b *new_node = (WORD_b *)malloc(sizeof(WORD_b));
    new_node->addr = addr;
    new_node->kval = kval;
    new_node->size = (int)pow(2,new_node->kval); 
    if((new_node->addr % (int)pow(2,new_node->kval+1)) == 0)
        new_node->body = new_node->addr + (int)pow(2,new_node->kval);
    else if((new_node->addr % (int)pow(2,new_node->kval+1)) == (int)pow(2,new_node->kval))
        new_node->body = new_node->addr - (int)pow(2,new_node->kval); 
    new_node->rlink = NULL;
    new_node->llink = NULL;
    return new_node;
}

// 插入节点到链表中
void insert_node(WORD_b **head, WORD_b *new_node) {
    if (*head == NULL) {
        *head = new_node;
    } else {
        WORD_b *current = *head;
        WORD_b *prev = NULL;
        while (current != NULL && current->addr < new_node->addr) {
            prev = current;
            current = current->rlink;
        }
        new_node->rlink = current;
        new_node->llink = prev;
        if (prev != NULL) {
            prev->rlink = new_node;
        } else {
            *head = new_node;
        }
        if (current != NULL) {
            current->llink = new_node;
        }
    }
}

// 合并相邻的空闲块
void merge_free_blocks(WORD_b **head) {
    WORD_b *current = *head;
    while (current != NULL && current->rlink != NULL) {
        WORD_b *next = current->rlink;
        if (current->body == next->addr && current->kval == next->kval) {
            current->size += next->size;
            current->kval++;
            current->rlink = next->rlink;
            if((current->addr % (int)pow(2,current->kval+1)) == 0)
                current->body = current->addr + (int)pow(2,current->kval);
            else if((current->addr % (int)pow(2,current->kval+1)) == (int)pow(2,current->kval))
                current->body = current->addr - (int)pow(2,current->kval); 
            if (next->rlink != NULL) {
                next->rlink->llink = current;
            }
            free(next);
            // 从头开始重新检查合并
            current = *head;
        } else {
            current = current->rlink;
        }
    }
}

// 冒泡排序链表
void sort(WORD_b **head) {
    if (*head == NULL) return;
    int swapped;
    WORD_b *ptr1;
    WORD_b *lptr = NULL;
  
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->rlink != lptr) {
            if (ptr1->kval > ptr1->rlink->kval) {
                // 交换地址和kval
                int temp_kval = ptr1->kval;
                int temp_addr = ptr1->addr;
                int temp_body = ptr1->body;
                ptr1->body = ptr1->rlink->body;
                ptr1->kval = ptr1->rlink->kval;
                ptr1->addr = ptr1->rlink->addr;
                ptr1->rlink->kval = temp_kval;
                ptr1->rlink->addr = temp_addr;
                swapped = 1;
            }
            ptr1 = ptr1->rlink;
        }
        lptr = ptr1;
    } while (swapped);
}

int main() {
    WORD_b *free_list = NULL;
    int kval, addr;
    char c;

    // 读取当前已有的空闲块链表
    while (scanf("%d %d", &kval, &addr) == 2) {
        WORD_b *new_node = create_node(kval, addr);
        insert_node(&free_list, new_node);
        while ((c = getchar()) != '\n' && c != EOF) {
            if (scanf("%d", &addr) == 1) {
                new_node = create_node(kval, addr);
                insert_node(&free_list, new_node);
            }
        }
    }
    merge_free_blocks(&free_list);
    sort(&free_list);
    // 输出回收后的空闲块状态
    print_free_list(free_list);
    // 清理
    WORD_b *current = free_list;
    while (current != NULL) {
        WORD_b *next = current->rlink;
        free(current);
        current = next;
    }
    return 0;
}
