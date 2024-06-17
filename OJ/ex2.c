#include <stdio.h>
void fib(int k,int m);
int main(){
    int k,m;
    scanf("%d %d",&k,&m);
    fib(k,m);
    return 0;
}
void fib(int k,int m){
    int f[10000];
    int i,j;
    for(i=0;i<k-1;i++){
        f[i]=0;
    }
    f[k-1]=1;
    for(i=k;i<10000;i++){
        for(j=1;j<k+1;j++){
            f[i]+=f[i-j];
        }
    }
    printf("%d\n",f[m]);
}