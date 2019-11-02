#include <stdio.h>
#include <stdlib.h>

typedef struct point
{
    float x,y;
}point;

typedef struct rect
{
    char* name;
    point points[2];
    float area,perimeter;
}rect;

FILE* testfopen(char* filename,char* mode)
{
    FILE* temp = fopen(filename,mode);
    if(temp)
        return temp;
    exit(1);
}

int main(int argc, char** argv)
{
    if(argc!=4)
        return 1;

    FILE* datafile = testfopen(argv[1],"r");

    int no_rect;
    fscanf(datafile,"%d",&no_rect);
    no_rect = no_rect / 2;

    rect* rects = malloc(no_rect*sizeof(rect));

    char temp[5];
    float x,y;
    while(fscanf(datafile,"%s %f %f",temp,&x,&y))
    {
        addData(rects,temp,x,y);
    }
    fclose(datafile);


    return 0;
}
