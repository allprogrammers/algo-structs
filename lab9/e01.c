#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "e01lib.h"

int main(int argc,char** argv)
{
    if(argc!=2)
        return 1;

    int rows,cols;

    FILE* fp = myfopen(argv[1],"r");

    fscanf(fp,"%d %d\n",&rows,&cols);

    char** mat = readfile(fp,rows,cols);
    printMat(mat,rows,cols);

    fclose(fp);

    solve(mat,rows,cols);
    freeMat(mat,rows,cols);
    return 0;
}
