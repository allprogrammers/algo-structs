#include <stdio.h>

int more_zeros(char** puzzle,int n)
{
    int mat_size = 2*n-1;
    for(int i=0;i<mat_size;i+=2)
    {
        for(int j=0;j<mat_size;j+=2)
        {
            if(puzzle[i][j]=='0')
            {
                return 1;
            }
        }
    }
    return 0;
}

int test(char** puzzle,int n)
{
    int mat_size = 2*n-1;
    
    //rows check
    //cols check
    //inequality check
}

int solvefrom(char** puzzle,int row,int n)
{
    int mat_size = 2*n-1;

    int* possibilities = mymalloc(n*sizeof(int));
    for(int i=0;i<n;i++)
        possibilities[i]=0;
    for(int i=0;i<mat_size;i+=2)
    {
        if(puzzle[row][i]>'0' && puzzle[row][i]<=
    }

    //make list of the numbers to add in a row by considering the row and col
    //don't consider inequalities you do that in the test


}

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        fprintf(stderr,"Usage: %s <filename>",argv[0]);
        exit(1);
    }

    int mat_rows = 2*argv[2]-1;
    int** mat=mymalloc(mat_rows*sizeof(int*));
    for(int i=0;i<mat_rows;i++)
    {
        mat[i]=mymalloc(mat_rows*sizeof(int));
    }
    int tmp;
    int i=0;
    int j=0;
    int char_trig = 0;

    FILE* readfile = myfopen(argv[1],"r");
    while(1)
    {
        if(char_trig)
        {
            char tmp;
            fscanf(readfile,"%c",tmp);
            if(tmp==LT)
        }
    }
    fclose(readfile);

    if(more_zeros(mat,argv[2]))
    {
        solve(mat,argv[2]);
    }
    if(test(mat,argv[2]))
    {
        printf("Correct");
    }else
    {
        printf("Wrong");
    }
    free(mat);
    return 0;
}
