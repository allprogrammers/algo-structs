#include <stdio.h>
#include <stdlib.h>


FILE* testfopen(char* filename,char* mode)
{
    FILE* ret = fopen(filename,mode);
    if(ret)
        return ret;
    exit(1);
}

int testmagic(int* matrix,int n)
{
    int sum =0;
    for(int i=0;i<n;i++)
    {
        sum+=matrix[i];
    }
    int tsum =0;
    for(int row=0;row<n;row++)
    {
        for(int col=0;col<n;col++)
        {
            tsum+=matrix[row*n+col];
        }
        if(tsum!=sum)
            return 0;
        tsum=0;
    }
    for(int row=0;row<n;row++)
    {
        for(int col=0;col<n;col++)
        {
            tsum+=matrix[col*n+row];
        }
        if(tsum!=sum)
            return 0;
        tsum=0;
    }
    for(int row=0;row<n;row++)
    {
        tsum+=matrix[row*n+row];
    }
    if(tsum!=sum)
        return 0;
    tsum=0;
    for(int row=0;row<n;row++)
    {
        for(int col=n-1;col>=0;col--)
        {
            tsum+=matrix[row*n+col];
        }
        if(tsum!=sum)
            return 0;
        tsum=0;
    }
    return 1;
}
int fillup(int* matrix,int n,int* numbers,int ind)
{
    if(ind==n*n)
    {
        return testmagic(matrix,n);
    }
    int square = n*n;
    for(int i=0;i<square;i++)
    {
        if(numbers[i]!=-1)
        {
            matrix[ind]=numbers[i];
            numbers[i]=-1;
            if(fillup(matrix,n,numbers,ind+1))
            {
                return 1;
            }
            numbers[i]=i+1;
        }
    }
    return 0;
}

void magic(int* matrix,int n)
{
    int* numbers = malloc(n*n*sizeof(int));
    for(int j=0;j<n*n;j++)
    {
        numbers[j]=j+1;
        matrix[j]=-1;
    }

    if(fillup(matrix,n,numbers,0))
        return;
    else
        exit(1);

}



void store(char* filename,int* matrix,int n)
{
    FILE* tos = testfopen(filename,"w");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            fprintf(tos,"%d ",matrix[i*n+j]);
        }
        fprintf(tos,"\n");
    }
    fclose(tos);
}

int main(int argc, char** argv)
{
    if (argc!=3)
        return 1;
    
    int n = atoi(argv[1]);

    int* matrix = malloc(n*n*sizeof(int*));
    
    magic(matrix,n);

    store(argv[2],matrix,n);

    return 0;
}
