#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITSTRLEN 100
#define INCREASE 10
#define ERROR 0
#define OK 1

typedef struct {
    char *ch;
    int strsize;
    int length;
} HString;

typedef int Status;

Status StrInit(HString *s) {
    s->ch = (char *)malloc(INITSTRLEN * sizeof(char));
    if (!s->ch)
        return ERROR;
    s->ch[0] = '\0';
    s->length = 0;
    s->strsize = INITSTRLEN;
    return OK;
}

Status StrInsert(HString *s, char x) {
    if (s->length >= s->strsize - 1) { // -1 为了留出空间给空字符结束符
        s->strsize += INCREASE;
        s->ch = (char *)realloc(s->ch, s->strsize * sizeof(char));
        if (!s->ch)
            return ERROR;
    }
    s->ch[s->length] = x;
    s->length++;
    s->ch[s->length] = '\0'; // 在字符串末尾添加空字符结束符
    return OK;
}

Status StrSubstr(HString *subs,HString *s,int i,int j){
    int k;
    if(i<=0 || i>s->length || j<0 || j>s->length-i+1)
        return ERROR;
    if(subs->strsize<j+1){
        subs->ch = (char *)realloc(subs->ch,(j+1)*sizeof(char));
        if(!subs->ch)
            return ERROR;
        subs->strsize = j+1;
    }
    for(k=0;k<j;k++)
        subs->ch[k] = s->ch[i-1+k];
    subs->ch[j]='\0';
    subs->length = j;
    return OK;
}

Status IsStrEqual(HString *s1,HString *s2){
    int i;
    for(i=0;i<s1->length && i<s2->length;i++){
        if(s1->ch[i]!=s2->ch[i])
            return ERROR;
    }
    if(i<s1->length || i<s2->length)
        return ERROR;
    else
        return OK;
}

Status StrIndex(HString *s,int i,HString *t){
    int m,n;
    HString sub;
    StrInit(&sub);
    n=s->length;
    m=t->length;
    while(i<=n-m+1){
        StrSubstr(&sub,s,i,m);
        if(!IsStrEqual(&sub,t))
            i++;
        else
            return i;
    }
    return 0;
}

Status StrChange(HString *s,int i,int j,HString *t){
    int k;
    if(i<=0 || i>s->length || j<=0 || j>s->length-i+1)
        return ERROR;
    if(j<t->length){
        if(s->length+t->length-j+1 > s->strsize){
            s->ch = (char *)realloc(s->ch,(s->length+t->length-j+1)*sizeof(char));
            if(!s->ch)
                return ERROR;
            s->strsize = s->length+t->length-j+1;
        }
        for(k=s->length;k>=i+j-1;k--)
            s->ch[k-j+t->length] = s->ch[k];
    }
    else{
        for(k=i-1+j;k<s->length;k++){
            s->ch[k-j+t->length] = s->ch[k];
        }
    }
    s->length = s->length+t->length-j;
    s->ch[s->length] = '\0';
    for(k=0;k<t->length;k++)
        s->ch[k+i-1] = t->ch[k];
    return OK;
}

void PrintResult(HString *s) {
    printf("%s\n", s->ch);
}

void Replace(HString *s, HString *T, HString *V) {
    int i=0;
    while ((i = StrIndex(s,i,T)) != 0) {
        StrChange(s, i, T->length, V);
        i = i+V->length;
    }
}

int main(){
    HString *s = (HString *)malloc(sizeof(HString));
    HString *T = (HString *)malloc(sizeof(HString));
    HString *V = (HString *)malloc(sizeof(HString)); 
    if (!s || !T || !V) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    StrInit(s);
    StrInit(T); 
    StrInit(V); 
    char c;
    while ((c = getchar()) != ' ') {
        StrInsert(s, c);
    }
    while ((c = getchar()) != ' ') {
        StrInsert(T, c); 
    }
    while ((c = getchar()) != '\n') { 
        StrInsert(V, c); 
    }
    Replace(s, T, V); 
    PrintResult(s);
    free(s->ch);
    free(T->ch); 
    free(V->ch); 
    free(s);
    free(T);
    free(V);
    return 0;
}