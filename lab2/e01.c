#include <stdio.h>

#define DIM_MAX 100

typedef float matrix[DIM_MAX][DIM_MAX];

void readDim(int *row, int *col)
{
    scanf("%d %d",row,col);
}

int checkDim(int r1,int c1,int r2,int c2)
{
    if(r1>=DIM_MAX || r2>=DIM_MAX || c1>=DIM_MAX || c2>=DIM_MAX || r2!=c1)
        return 1;
    return 0;
}

void readMatrix(float m[][DIM_MAX],int row,int col)
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            scanf("%f",&m[i][j]); 
        }
    }
}

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

void computeProduct(float m1[][DIM_MAX],int r1,int c1,float m2[][DIM_MAX],int r2,int c2,float m3[][DIM_MAX],int r3,int c3)
{
    for(int i=0;i<r3;i++)
    {
        for(int j=0;j<c3;j++)
        {
            m3[i][j]=dot(m1,m2,r2,i,j);//dot product of ith row of m1 with jth column of m2
        }
    }
}

void writeMatrix(float m1[][DIM_MAX],int r1,int c1,float m2[][DIM_MAX],int r2,int c2,float m3[][DIM_MAX],int r3,int c3)
{
    for(int i=0;i<r1;i++) 
    {
        for(int j=0;j<c1;j++)
        {
            printf("%.2f\t",m1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    for(int i=0;i<r2;i++) 
    {
        for(int j=0;j<c2;j++)
        {
            printf("%.2f\t",m2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i=0;i<r3;i++) 
    {
        for(int j=0;j<c3;j++)
        {
            printf("%.2f\t",m3[i][j]);
        }
        printf("\n");
    }
}



int main(void)
{
    int r[3],c[3];
    readDim(&r[0],&c[0]);
    readDim(&r[1],&c[1]);

    if (checkDim(r[0],c[0],r[1],c[1]))
        return 1;

    r[2]=r[0];
    c[2]=c[1];
    
    matrix m[3];
    readMatrix(m[0],r[0],c[0]);
    readMatrix(m[1],r[1],c[1]);

    computeProduct(m[0],r[0],c[0],m[1],r[1],c[2],m[2],r[2],c[2]);

    writeMatrix(m[0],r[0],c[0],m[1],r[1],c[2],m[2],r[2],c[2]);

    return 0;

}
