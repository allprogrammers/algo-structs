#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 20

typedef char* string;

FILE* testfopen(char*, char*);

string** makemat(int, int, int);

void readfile(FILE*, string**, int, int);
string* sortmat(string**,int,int);
void printmat(string**, int, int);
void freemat(string**, int, int, int);

int strrcmp(string, string);

int main(void)
{
    FILE* input = testfopen("texte2.txt","r");

    int rows,cols;

    fscanf(input,"%d %d\n",&rows,&cols);

    //creating the matrix
    string** strmat = makemat(rows,cols,1);

    readfile(input,strmat,rows,cols);
    printmat(strmat,rows,cols);
    printf("\n");

    //sorting the matrix
    strmat[0] = sortmat(strmat,rows,cols);
    //freemat(strmat,rows,cols,0);

    
    //printing
    printmat(strmat,1,rows*cols);

    //freeing
    //freemat(strmat,rows,cols,1);
    free(strmat[0]);
    free(strmat);
    free(input);

    return 0;
}

FILE* testfopen(char* inp,char* mode)
{
    FILE* out=fopen(inp,mode);
    if(out)
        return out;
    exit(0);
}

string** makemat(int rows,int cols,int alloc)
{
    string** strmat = malloc(rows*sizeof(string*));
    for(int i=0;i<rows;i++)
    {
        strmat[i]=malloc(cols*sizeof(string));
        if(alloc)
        {
            for(int j=0;j<cols;j++)
            {
                strmat[i][j] = malloc((MAX_LEN+1)*sizeof(char));
            }
        }
    }

    return strmat;
}

void readfile(FILE* inputfile,string** strmat,int rows,int cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            fscanf(inputfile,"%s",strmat[i][j]);
        }
    }
}

string* merge(string* arr1,int len1,string* arr2,int len2)
{
    int i1 = 0;
    int i2 = 0;

    string* merged = malloc((len1+len2)*sizeof(string));
    int ind = 0;

    while(i1<len1 && i2<len2)
    {
        if(strrcmp(arr1[i1],arr2[i2])<=0)
        {
            merged[ind++]=arr1[i1++];
        }else
        {
            merged[ind++]=arr2[i2++];
        }
    }
    while(i1<len1)
    {
        merged[ind++]=arr1[i1++];
    }
    while(i2<len2)
    {
        merged[ind++]=arr2[i2++];
    }

    free(arr1);
    free(arr2);

    return merged;
}

string* mergemat(string** strmat,int rstart,int rend,int cols)
{
    if(rend-rstart==1)
    {
        return merge(strmat[rstart],cols,strmat[rend],cols);
    }
    if(rend==rstart)
    {
        return strmat[rstart];
    }

    int mid = (rstart+rend)/2;
    int sizea = (mid-rstart+1)*cols;
    int sizeb = (rend-mid)*cols;


    return merge(mergemat(strmat,rstart,mid,cols),sizea,mergemat(strmat,mid+1,rend,cols),sizeb);
    
}

string* sortmat(string** strmat,int rows,int cols)
{
    return mergemat(strmat,0,rows-1,cols);
}

void printmat(string** strmat,int rows,int cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            printf("strmat at i = %d j=%d is %s\n",i,j,strmat[i][j]);
        }
    }

}

void freemat(string** strmat,int rows,int cols,int rmstr)
{
    for(int i=0;i<rows;i++)
    {
        if(rmstr)
        {
            for(int j=0;j<cols;j++)
            {
                free(strmat[i][j]);
            }
        }
        free(strmat[i]);
    }
    free(strmat);
}

int strrcmp(string str1,string str2)
{
    if(!str1)
        return -1;
    if(!str2)
        return 1;
    if(str1[0]<str2[0])
    {
        return -1;
    }else if(str1[0]>str2[0])
    {
        return 1;
    }else
    {
        return strrcmp(str1+1,str2+1);
    }
}

