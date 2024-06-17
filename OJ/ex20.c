#include <stdio.h>

int fun(int n){
    int f;
    if(n==0){
        f=n+1;
    }
    else{
        f=n*fun(n/2);
    }
    return f;
}

int main(){
    int n;
    scanf("%d",&n);
    int result;
    result = fun(n);
    printf("%d\n",result);
    return 0;
}
