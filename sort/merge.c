#include <stdio.h>

void mergesort(int arr[],int aux[],int start,int end)
{
    if (start>=end)
        return;

    int mid = (start+end)/2;
    
    mergesort(arr,aux,start,mid);
    mergesort(arr,aux,mid+1,end);

    int c[2] = {start,mid+1};
    int count = 0;
    while(c[0]<=mid && c[1]<=end)
    {
        if(arr[c[0]]<=arr[c[1]])
        {
            aux[start+count]=arr[c[0]];
            c[0]++;
        }else
        {
            aux[start+count]=arr[c[1]];
            c[1]++;
        }
        count++;
    }

    while(c[0]<=mid)
    {
        aux[start+count]=arr[c[0]];
        c[0]++;
        count++;
    }
    
    while(c[1]<=end)
    {
        aux[start+count]=arr[c[1]];
        c[1]++;
        count++;
    }

    for(int i = start; i<=end;i++)
    {
        arr[i]=aux[i];
    }
}

int main(void)
{
    int arr[10]={5,1,3,6,2,8,9,3,8,5};

    int aux[10];
    mergesort(arr,aux,0,9);

    for(int i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }

    return 0;
}
