#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct word {
    union {
        struct word *llink;  // ͷ����ָ��ǰ���ڵ�
        struct word *uplink; // β����ָ�򱾽���ͷ��
    };
    int tag;                 // 0��ʾ���У�1��ʾռ��
    int addr;                // ��ʼ��ַ
    int size;                // ���С
    struct word *rlink;      // ͷ����ָ���̽ڵ�
} Space;

// ��ӡ���п�����
void print_free_list(Space *head) {
    Space *current = head;
    while (current != NULL) {
        printf("%d %d %d\n", current->tag, current->addr, current->size);
        current = current->rlink;
    }
}

// �����½ڵ�
Space* create_node(int tag, int addr, int size) {
    Space *new_node = (Space *)malloc(sizeof(Space));
    new_node->tag = 0;
    new_node->addr = addr;
    new_node->size = size;
    new_node->rlink = NULL;
    new_node->llink = NULL;
    return new_node;
}

// ����ڵ㵽������
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

// �ϲ����ڵĿ��п�
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
    int tag, addr, size;
    char c,d;
    // �������еĿ��п�
    while (1) {
        int result = scanf("%d %d %d", &tag, &addr, &size);
        Space *new_node = create_node(tag, addr, size);
        insert_node(&free_list, new_node);
        if (tag == 1) {  // ������е����
            break;
        }
    }
    // ��������յ��ͷſ�
    while (scanf("%d %d %d", &tag, &addr, &size) == 3) {
        Space *new_node = create_node(tag, addr, size);
        insert_node(&free_list, new_node);
    }
    // �ϲ����ڵĿ��п�
    merge_free_blocks(free_list);
    // ������պ�Ŀ��п�״̬
    print_free_list(free_list);
    return 0;
}
