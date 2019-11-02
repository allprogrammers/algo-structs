#include <stdio.h>

#define MAX_DIM 100

typedef float matrix[MAX_DIM][MAX_DIM];

float dot(matrix m1,matrix m2,int size,int row, int col)
{
    float prod = 0;
    for(int i=0;i<size;i++)
    {
        prod += m1[row][i]*m2[i][col];
        printf("prod %.2f\n",prod);
    }
    printf("prod at %d %d is %.2f\n",row,col,prod);
    return prod;
}

int main(void)
{
    int r[3],c[3];
    scanf("%d %d %d %d",&r[0],&c[0],&r[1],&c[1]);
    r[2]=r[0];
    c[2]=c[1];
  
    if(r[0]>=MAX_DIM || r[1]>=MAX_DIM || c[1]>=MAX_DIM || c[1]>=MAX_DIM || r[1]!=c[0])
    {
        return 1;
    }
    
    matrix m[3];

    for(int times=0;times<2;times++)
    {
        for(int i=0;i<r[times];i++)
        {
            for(int j=0;j<c[times];j++)
            {
                scanf("%f",&m[times][i][j]); 
            }
        }
    }

    for(int i=0;i<r[2];i++)
    {
        for(int j=0;j<c[2];j++)
        {
            m[2][i][j]=dot(m[0],m[1],r[1],i,j);//dot product of ith row of m1 with jth column of m2
        }
    }

    for(int i=0;i<r[2];i++) 
    {
        for(int j=0;j<c[2];j++)
        {
            printf("%.2f\t",m[2][i][j]);
        }
        printf("\n");
    }

    return 0;

}
