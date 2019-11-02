#include <stdio.h>

void quicksort(int arr[],int start,int end)
{
    printf("%d %d\n",start,end);
    for(int i=0;i<=end;i++)
        printf("%d ",arr[i]);
    printf("\n");
    if(end-start==1)
    {
        if(arr[end]<arr[start])
        {
            int temp = arr[start];
            arr[start]=arr[end];
            arr[end]=temp;
        }
        return;
    }

    if(end<=start)
        return;

    int pivot=arr[start];

    int l = 1;
    int r=end;

    while(1)
    {
        while(arr[l]<=pivot)
        {
            l++;
        }
        while(arr[r]>=pivot)
        {
            r--;
        }
        if(r<l)
        {
            break;
        }else
        {
            int temp = arr[l];
            arr[l]=arr[r];
            arr[r]=temp;
        }
    }

    arr[start]=arr[r];
    arr[r]=pivot;
    r--;

    for(int i=start;i<=end;i++)
        printf("%d ",arr[i]);
    printf("\n");
    quicksort(arr,start,r);
    quicksort(arr,l,end);
}

int main(void)
{
    int arr[10]={5,1,3,6,2,8,9,3,8,5};

    for(int i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    quicksort(arr,0,9);

    printf("sorted\n");
    for(int i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");

    return 0;
}
