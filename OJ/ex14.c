#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PolyTerm {
    int coef; // 系数
    int exp;  // 指数
} PolyTerm;

typedef struct PolyNode {
    PolyTerm data;
    struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

// 创建新节点
PolyNode* createNode(int coef, int exp) {
    PolyNode* newNode = (PolyNode*)malloc(sizeof(PolyNode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data.coef = coef;
    newNode->data.exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 求导函数
LinkedPoly Derivative(LinkedPoly poly) {
    PolyNode* p = poly->next; // p指向第一个节点
    PolyNode* pre = poly;     // pre始终指向p的前一个节点
    while (p != NULL) {       // 当p不为NULL时循环
        if (p->data.exp == 0) { // 如果指数为0，删除节点
            pre->next = p->next;
            free(p);
            p = pre->next;
        } else { // 如果指数不为0，求导
            p->data.coef *= p->data.exp;
            p->data.exp -= 1;
            pre = p;
            p = p->next;
        }
    }
    return poly;
}

// 排序函数：按照幂次由高到低排序
PolyLink sortPoly(PolyLink poly) {
    if (poly == NULL || poly->next == NULL) {
        return poly; // 如果链表为空或只有一个节点，则无需排序
    }
    
    PolyLink sorted = (PolyLink)malloc(sizeof(PolyNode)); // 创建一个头结点
    sorted->next = NULL; // 初始化为空链表
    PolyLink current = poly->next;

    while (current != NULL) {
        PolyLink next = current->next; // 存储下一个节点

        // 将当前节点插入排序后的链表
        PolyLink prev = sorted;
        while (prev->next != NULL && prev->next->data.exp > current->data.exp) {
            prev = prev->next;
        }
        current->next = prev->next;
        prev->next = current;

        current = next; // 移动到原始链表中的下一个节点
    }
    
    return sorted; // 返回排序后的链表，跳过头结点
}

// 打印多项式
void printPoly(LinkedPoly poly) {
    PolyNode* p = poly->next;
    int firstTerm = 1; // 标记是否为第一项
    int hasTerm = 0; // 标记是否有有效项
    while (p != NULL) {
        if (p->data.coef != 0) { // 只输出系数不为0的项
            hasTerm = 1;
            if (!firstTerm && p->data.coef > 0) {
                printf(" + ");
            } else if (!firstTerm && p->data.coef < 0) {
                printf(" - ");
            } else if (firstTerm && p->data.coef < 0){
                printf("- ");
            }
            if (abs(p->data.coef) != 1 || p->data.exp == 0) {
                printf("%d", abs(p->data.coef)); // 绝对值
            }
            if (p->data.exp > 0) {
                printf("x");
                if (p->data.exp > 1) {
                    printf("^%d", p->data.exp);
                }
            }
            firstTerm = 0;
        }
        p = p->next;
    }
    if (!hasTerm) { // 如果多项式为空
        printf("0");
    }
    printf("\n");
}


// 创建多项式
LinkedPoly createPoly() {
    LinkedPoly poly = createNode(0, 0); // 创建头节点
    return poly;
}

// 添加节点到多项式
void addNode(LinkedPoly poly, int coef, int exp) {
    PolyNode* p = poly->next;
    PolyNode* pre = poly;
    while (p != NULL) {
        if (p->data.exp == exp) {
            p->data.coef += coef;
            if (p->data.coef == 0) { // 如果系数为0，删除节点
                pre->next = p->next;
                free(p);
            }
            return;
        }
        pre = p;
        p = p->next;
    }
    // 如果没有找到相同的幂次，添加新的节点
    PolyNode* newNode = createNode(coef, exp);
    pre->next = newNode;
}

// 主函数
int main() {
    LinkedPoly poly = createPoly();
    char token[100];
    int sign = 1;
    char c;
    while (scanf("%s", token) != EOF) {
        if (strcmp(token, "+") == 0) {
            sign = 1;
        } else if (strcmp(token, "-") == 0) {
            sign = -1;
        } else {
            int coef, exp;
            char tmp[2];
            if (sscanf(token, "%d%2s%d", &coef, tmp, &exp) == 3) {
                addNode(poly, sign * coef, exp);
            } else if (sscanf(token, "%d%1s", &coef, tmp) == 2) {
                addNode(poly, sign * coef, 1);
            } else if (sscanf(token, "%d", &coef) == 1) {
                addNode(poly, sign * coef, 0);
            } else if (strcmp(token, "x") == 0) {
                addNode(poly, sign * 1, 1);
            }
        }
        if((c = getchar()) =='\n')
            break;
    }
    poly = sortPoly(poly);
    LinkedPoly derivative = Derivative(poly);
    printPoly(derivative);
    
    // Free memory
    PolyNode* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
    return 0;
}