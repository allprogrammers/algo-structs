#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

FILE* myfopen(char* filename,char* mode)
{
    FILE* temp = fopen(filename,mode);
    if(temp)
        return temp;
    exit(1);
}

void* mymalloc(int size)
{
    void* temp = malloc(size);
    if(temp)
        return temp;
    exit(1);
}

void freeMat(char** mat,int rows,int cols)
{
    for(int i=0;i<rows;i++)
        free(mat[i]);
    free(mat);
}
