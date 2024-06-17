#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_WIDTH 20
#define MAX_HEIGHT 20

typedef struct{
    int color;
    int state;
}Node;

typedef struct{
    Node lab[MAX_HEIGHT][MAX_WIDTH];
    int height;
    int width;
}Image;

int direction[4][2] = {
    {1,0},{-1,0},{0,-1},{0,1}
};

void PrintImage(Image *L){
    for(int i=0;i<L->height;i++){
        for(int j=0;j<L->width;j++){
            printf("%d",L->lab[i][j].color);
        }
        printf("\n");
    }
}

void ChangeColor(Image *L,int row,int col){
    int eld_col;
    if(row>=0 && row<L->height && col>=0 && col<L->width && L->lab[row][col].state==0){
        eld_col = L->lab[row][col].color;
        L->lab[row][col].color = 2;
        L->lab[row][col].state = 1;
        for(int i=0;i<4;i++){
            if(row+direction[i][0]>=0 && row+direction[i][0]<L->height
               && col+direction[i][1]>=0 && col+direction[i][1]<L->width
               && eld_col==L->lab[row+direction[i][0]][col+direction[i][1]].color 
               && L->lab[row+direction[i][0]][col+direction[i][1]].state==0){
                ChangeColor(L,row+direction[i][0],col+direction[i][1]);
               }
        }
    }
}

int main(){
    int row,col,dir;
    Image *L = (Image *)malloc(sizeof(Image));
    scanf("%d %d %d %d %d",&L->height,&L->width,&row,&col,&dir);
    for(int i=0;i<L->height;i++){
        for (int j=0;j<L->width;j++){
            scanf("%d",&L->lab[i][j].color);
            L->lab[i][j].state = 0;
        }
    }
    ChangeColor(L,row,col);
    PrintImage(L);
    return 0;
}
