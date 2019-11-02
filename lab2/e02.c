#include <stdio.h>

#define SIZE 5
#define MAX 100

int srcmp(char buff[],int start,char ch)
{
    for(int i=start;i<start+SIZE;i++)
    {
        if(buff[i]!=ch)
        {
            return i+1;
        }
    }
    return -1;
}

int lookh(char buff[])
{
    int count = 0;
    int i=0;
    while(buff[i]!='\0')
    {
        int ans = srcmp(buff,i,'h');
        if(ans<0)
        {
            count +=1;
            i++;
        }
        else
            i=ans;
    }
    return count;
}

int lookv(char buff[],int vcount[])
{
    int i = 0;
    int count = 0;
    

    while(buff[i]!='\0')
    {
        if(buff[i]=='v')
            vcount[i]++;
        else
            vcount[i]=0;
        i++;
    }
    
    i=0;
    while(i<MAX)
    {
        if(vcount[i]>=SIZE)
            count++;
        i++;
    }
    return count;
}

int main(void)
{
    FILE *p = fopen("test02.txt","r");
    if(p == NULL)
        return 1;

    int h=0;
    int v=0;
    char buff[MAX+1+1];
    int vcount[MAX]={0};//keeps track of number of contiguous vs encountered during the last few lines
    
    while(fgets(buff,100,p))
    {
        printf("%s",buff);
        h += lookh(buff);
        v += lookv(buff,vcount);
    }
    printf("the verticals %d \nthe horizontals %d\n",v,h);

    fclose(p);
    return 0;
}
