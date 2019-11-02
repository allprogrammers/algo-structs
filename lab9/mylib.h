#ifndef _mylib
#define _mylib
FILE* myfopen(char* filename,char* mode);
void* mymalloc(int size);
void freeMat(char** mat,int rows,int cols);
#endif
