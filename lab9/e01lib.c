#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

char** readfile(FILE* fp,int rows,int cols)
{
    char** mat = mymalloc(rows*sizeof(char*));

    for(int i=0;i<rows;i++)
    {
        mat[i] = mymalloc(cols*sizeof(char));
        for(int j=0;j<cols;j++)
        {
            do
            {
                fscanf(fp,"%c",&mat[i][j]);
            }while(mat[i][j]=='\n');
        }
    }

    return mat;
}

int countx(char** mat,int rows,int cols)
{
    int count =0;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(mat[i][j]=='x')
                count++;
        }
    }
    return count;
}
void printMat(char** mat,int rows,int cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }
}
char** matcopy(char** mat,int rows,int cols)
{
    char** matcpy = mymalloc(rows*sizeof(char*));
    for(int i=0;i<rows;i++)
    {
        matcpy[i]=mymalloc(cols*sizeof(char));
        for(int j=0;j<cols;j++)
            matcpy[i][j]=mat[i][j];
    }
    return matcpy;
}
char** onesolve(char** mat,int rows,int cols,int startx,int starty)
{
    int stepsx[4]={0,0,-1,1};
    int stepsy[4]={1,-1,0,0};
    for(int i=0;i<4;i++)
    {
        int newx=startx+stepsx[i];
        int newy=starty+stepsy[i];
        if(newx>=cols || newy>=rows || newx<0 || newy<0)
            continue;
        if(mat[newy][newx]=='#')
        {
            return mat;
        }else if(mat[newy][newx]==' ')
        {
            mat[newy][newx]='x';
            char** ans = onesolve(mat,rows,cols,newx,newy);
            if(ans)
                return ans;
            mat[newy][newx]=' ';
            continue;
        }   
    }
    return NULL;
}

char** allsolve(char** mat,int rows,int cols,int startx,int starty)
{
    int stepsx[4]={0,0,-1,1};
    int stepsy[4]={1,-1,0,0};
    for(int i=0;i<4;i++)
    {
        int newx=startx+stepsx[i];
        int newy=starty+stepsy[i];
        if(newx>=cols || newy>=rows || newx<0 || newy<0)
            continue;
        if(mat[newy][newx]=='#')
        {
            printMat(mat,rows,cols);
        }else if(mat[newy][newx]==' ')
        {
            mat[newy][newx]='x';
            allsolve(mat,rows,cols,newx,newy);
            mat[newy][newx]=' ';
            continue;
        }   
    }
    return NULL;
}

char** shortsolve(char** omat,int rows,int cols,int startx,int starty)
{
    int stepsx[4]={0,0,-1,1};
    int stepsy[4]={1,-1,0,0};
    int min = rows*cols;
    char** minmat = NULL;
    char** mat = matcopy(omat,rows,cols);

    for(int i=0;i<4;i++)
    {
        int newx = startx+stepsx[i];
        int newy = starty+stepsy[i];
        if(newx>=cols || newy>=rows || newx<0 || newy<0)
            continue;
        if(mat[newy][newx]=='#')
        {
            return mat;
        }else if(mat[newy][newx] ==' ')
        {
            mat[newy][newx]='x';
            char** ans = shortsolve(mat,rows,cols,newx,newy);
            if(ans)
            {
                int count = countx(ans,rows,cols);
                if(count<min)
                {
                    if(minmat)
                        freeMat(minmat,rows,cols);
                    min = count;
                    minmat = ans;
                }else
                {
                    freeMat(ans,rows,cols);
                }
            }
            mat[newy][newx]=' ';
        }
    }
    freeMat(mat,rows,cols);
    return minmat;
}

void solve(char** mat,int rows,int cols)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(mat[i][j]=='@')
            {
                char** ans;

                char** onecopy = matcopy(mat,rows,cols);
                ans = onesolve(onecopy,rows,cols,j,i);
                printMat(ans,rows,cols);
                freeMat(onecopy,rows,cols);
                printf("\n");

                char** allcopy = matcopy(mat,rows,cols);
                allsolve(allcopy,rows,cols,j,i);
                freeMat(allcopy,rows,cols);

                ans = shortsolve(mat,rows,cols,j,i);
                printMat(ans,rows,cols);
                freeMat(ans,rows,cols);
                break;
            }
        }
    }
}


