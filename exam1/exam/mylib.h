#include <stdio.h>
#include <stdlib.h>

FILE* safefopen(char* fname,char* mode)
{
    FILE* tmp = fopen(fname,mode);
    if(tmp)
        return tmp;
    printf("couldn't open file\n");
    exit(1);
}

void* mymalloc(int size)
{
    void* tmp = malloc(size);
    if(tmp)
        return tmp;
    printf("couldn't allocate memory\n");
    exit(1);
}
