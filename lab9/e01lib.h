#ifndef _e01lib
#define _e01lib
char** readfile(FILE* fp,int rows,int cols);
int countx(char** mat,int rows,int cols);
void printMat(char** mat,int rows,int cols);
char** matcopy(char** mat,int rows,int cols);
char** onesolve(char** mat,int rows,int cols,int startx,int starty);
char** allsolve(char** mat,int rows,int cols,int startx,int starty);
char** shortsolve(char** omat,int rows,int cols,int startx,int starty);
void solve(char** mat,int rows,int cols);
#endif
