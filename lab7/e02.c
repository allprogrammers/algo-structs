#include <stdio.h>

int mult(int x,int y)
{
    if(y==1)
        return x;
    return mult(x,y-1)+x;
}

void d2b(int d, int* b, int n)
{
    printf("%d\n",d);
    *(b+n-1) = d%2;
    if(d/2==0)
    {
        return;
    }
    d2b(d/2,b,n-1);
}

void triangle(int n,int i)
{
    if(n==1)
    {
        printf("1");
        return;
    }
    if(i==0)
    {
        triangle(n-1,0);
        printf("\n%d ",n);
        triangle(n,1);
        return;
    }
    if(n!=i)
    {
        printf("%d ",n);
        triangle(n,i+1);
    }
    
}

int catalan(int n)
{
    if(n==0)
    {
        return 1;
    }
    int catalann = 0;
    for(int i=0;i<n;i++)
    {
        catalann += catalan(i)*catalan(n-i-1);
    }
    return catalann;
}

int main (void)
{
    printf("%d\n",catalan(6));
    return 0;
}
