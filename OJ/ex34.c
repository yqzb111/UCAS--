#include <stdio.h>
#include <stdlib.h>

typedef char AtomType;
// 枚举类型，用于表示广义表中的元素类型
typedef enum { ATOM, LIST } ElemTag;
// 广义表结点类型的定义
typedef struct GLNode
{
	ElemTag tag; // 结点类型表示
	union
	{
		AtomType atom;
		struct GLNode *hp;
	} val;
	struct GLNode *tp; // 指向下一个元素
} GLNode;

GLNode *CreatGL(char **s)
{
	GLNode *h;
	char ch;
	ch = **s; // 取一个扫描字符
	(*s)++; // 串指针向后移动一位
	if ('\0' != ch) // 串未结束标识
	{
		h = (GLNode*)malloc(sizeof(GLNode)); // 创建一个新结点
		if ('(' == ch) // 当前字符为左括号
		{
			h->tag = LIST; // 新结点为表头结点
			h->val.hp = CreatGL(s); // 递归构造子表并链接到表头节点上
		}
		else if (')' == ch) // 当前字符为右括号
		{
			h = NULL;
		}
		else
		{
			h->tag = ATOM; // 新结点为原子结点
			h->val.atom = ch;
		}
	}
	else // 串结束，子表为空
		h = NULL;
	ch = **s;
	(*s)++;
	if (h != NULL)
	{
		if (',' == ch)
		{
			h->tp = CreatGL(s);
		}
		else
		{
			h->tp = NULL;
		}
	}
	return h;
}

void Delete(GLNode **L, AtomType x){
    if (!(*L)) {
        // 如果当前节点为空，直接返回
        return;
    }

    if ((*L)->tag == ATOM) {
        // 如果是原子节点且值等于x，则删除
        if ((*L)->val.atom == x) {
            GLNode *temp = *L;
            *L = (*L)->tp; // 跳过当前节点
            free(temp); // 释放当前节点
            Delete(L, x); // 继续检查下一个节点
        } else {
            // 如果原子值不等于x，检查下一个节点
            Delete(&((*L)->tp), x);
        }
    } else {
        // 如果是列表节点，递归删除子列表中的元素
        Delete(&((*L)->val.hp), x);
        // 如果子列表为空，删除该子列表节点
        if (!(*L)->val.hp) {
            GLNode *temp = *L;
            *L = (*L)->tp; // 跳过当前空的子列表节点
            free(temp); // 释放子列表节点
            Delete(L, x); // 继续检查下一个节点
        } else {
            // 如果子列表不为空，检查下一个节点
            Delete(&((*L)->tp), x);
        }
    }
}


void PrintGLNode(GLNode* g)
{
    if(g == NULL){
        printf("-1");
    }
    else if (g->tag == LIST) // 为表结点
    {
        printf("(");
        if (g->val.hp != NULL)
            PrintGLNode(g->val.hp); // 递归输出子表
        printf(")");
        if (g->tp != NULL)
        {
            printf(",");
            PrintGLNode(g->tp);
        }
    }
    else // 原子结点
    {
        printf("%c", g->val.atom);
        if (g->tp != NULL)
        {
            printf(",");
            PrintGLNode(g->tp);
        }
    }
}

int main(){
	char S[1000];
    char x;
    char *ps = S;
    scanf("%s %c",S,&x);
    GLNode *L;
    L = CreatGL(&ps);
    Delete(&L,x);
    PrintGLNode(L);
    printf("\n");
    return 0;
}