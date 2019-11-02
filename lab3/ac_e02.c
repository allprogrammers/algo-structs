#include <stdio.h>

#define STR_LEN 4

// The maximum size of the problem is 26^4 assuming the name composes only english alphabets

typedef struct point
{
    float x,y;
} point;

typedef struct rect
{
    char name[STR_LEN+1];
    point defi[2];
    float area;
    float peri;
} rect;

FILE* testfopen(char *filename, char *mode)
{
    FILE* res = fopen(filename,mode);
    if(res)
        return res;
    exit(0);
}

int indexof(rect* rects,char* name,int len)
{
    //linear search because the names are not generally sorted inside the file
    for(int i=0;i<len;i++)
    {
        if(!strcmp(name,rects[i].name))
            return i;
    }
    return freeind+1;
}

void addData(rect* rects,char* name,float x, float y, int freeind)
{
    int i = indexof(rects,name,freeind-1);

    if(i<0)
    {
        i=freeind;
        rects[i].name = strdup(name);
        rects[i].defi[0].x=x;
        rects[i],defi[0].y=y;
    }else
    {
        //already existing so only one point and then peri and area
        rects[i].defi[1].x=x;
        rects[i].defi[1].y=y;

        float l1 = rects[i].defi[0].x-rects[i].defi[1].x;
        float l2 = rects[i].defi[0].y-rects[i].defi[1].y;
        
        if(l1<0)
            l1 *=-1;
        if(l2<0)
            l2 *=-1;

        rects[i].peri = 2*l1+2*l2;
        rects[i].area = l1*l2;
    }

}

void sortRects(rect* rects,int len,int offset,int sortedindex)
{
    float min,max;
}

void store(rect* rects,int len,int offset,FILE* out)
{
    int* sortedindex = malloc(len*sizeof(int));
    sortRects(rects,len,offset,sortedindex);
    for(int i=0;i<len;i++)
    {
        fprintf(out,"%s\n",rects[sortedindex[i]]);
    }
    free(sortedindex);
}

int main(int argc, char **argv)
{
    if(argc!=4)
        return 1;

    FILE* datafile = testfopen(argv[1],"r");

    int no_rect;
    fscanf(datafile,"%d\n",&no_rect);
    no_rect /=2;

    rect* rects = malloc(no_rect*sizeof(rect));

    char buff[STR_LEN+1];
    float x,y;

    int i =0;
    while(fscanf(datafile,"%s %f %f",buff,&x,&y))
    {
        addData(rects,buff,x,y,i);
    }
    fclose(datafile);

    FILE* areafile = testfopen(argv[2],"w");
    store(rects,no_rect,offsetof(rect,area),areafile);
    fclose(areafile);

    FILE* perifile = testfopen(argv[3],"w");
    store(rects,no_rect,offsetof(rect,peri),perifile);
    fclose(perifile);

    free(rects);


    return 0;
}
