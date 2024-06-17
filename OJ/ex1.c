#include <stdio.h>
int main(){
  int x,y,z;
  scanf("%d %d %d",&x,&y,&z);
  if(x>y){
    if(y>z){
      printf("%d %d %d\n",x,y,z);
      }
    else if(y<=z && x>z){
      printf("%d %d %d\n",x,z,y);
      }
    else if(y<=z && x<=z){
      printf("%d %d %d",z,x,y);
      }
  }
  else if(x<=y){
    if(x>z){
      printf("%d %d %d\n",y,x,z);
      }
    else if(x<=z && y>z){
      printf("%d %d %d\n",y,z,x);
      }
    else if(y<=z && x<=z){
      printf("%d %d %d\n",z,y,x);
      }
  }
  return 0;
}