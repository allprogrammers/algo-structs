#include <stdio.h>
#include <stdlib.h>

int twopower(int n)
{
    int rows = 1;
    for(int i=0;i<n;i++)
    {
        rows = rows*2;
    }
    return rows;
}

void generate(int** mat,int rows,int cols,int bits)
{
    if(bits==1)
    {
        mat[0][cols-1]=0;
        mat[1][cols-1]=1;
        return;
    }
    generate(mat,rows,cols,bits-1);
    int rowsfilled = twopower(bits-1);
    int currentending = 2*rowsfilled;
    for(int i=0;i<rowsfilled;i++)
    {
        for(int j=cols-1;j>=cols-bits;j--)
        {
            mat[currentending-i-1][j]=mat[i][j];
        }
        mat[i][cols-bits]=0;
        mat[currentending-1-i][cols-bits]=1;
    }

}

int main(int argc,char** argv)
{
    if(argc!=2)
        return 1;
    int n = atoi(argv[1]);
    int rows = twopower(n);

    int** mat = malloc(rows*sizeof(int*));
    for(int i=0;i<rows;i++)
    {
        mat[i]=calloc(n,sizeof(int));
    }

    generate(mat,rows,n,n);

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d",mat[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<rows;i++)
        free(mat[i]);
    free(mat);
    return 0;
}
