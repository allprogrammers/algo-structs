#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 100

typedef struct string
{
    char* str;
}string;

FILE* testfopen(char* filename,char* mode)
{
    FILE* ret = fopen(filename,mode);
    if (ret)
        return ret;
    exit(1);
}

int counter =0;

void sort(string* strings,int len,int key)
{
    if(len==0 || len==1)
    {
        return;
    }
    int sp=0;
    int last=0;
    for(int i = 0;i<26;i++)
    {
        for(int j=0;j<len;j++)
        {
            printf("%d\n",counter++);
            if(strings[j].str[key]=='a'+i)
            {
                string temp = strings[sp];
                strings[sp]=strings[j];
                strings[j]=temp;
                sp++;
            }
        }
        sort(strings+last,sp-last,key+1);
        last = sp;
    }
}

void store(string* strings,int n,FILE* outfile)
{
    for(int i=0;i<n;i++)
    {
        fprintf(outfile,"%s\n",strings[i].str);
    }
}

char tollower(char c)
{
    if (c>='A' && c<='Z')
        return c+'a'-'A';
    else if(c=='\n')
        return '\0';
    return c;
}

int strrdup(char** newstr, char* buff)
{
    int i=0;
    int sl = strlen(buff);
    *newstr = malloc(sl*sizeof(char));
    while(buff[i]!='\n')
    {
        (*newstr)[i]=tollower(buff[i]);
        i++;
    }
    
    return i;
}

int main(int argc, char** argv)
{
    if (argc!=3)
        return 1;
    FILE* inpfile = testfopen(argv[1],"r");
    FILE* outfile = testfopen(argv[2],"w");

    int n;
    fscanf(inpfile,"%d\n",&n);

    string* strings = malloc(n*sizeof(string));

    char buff[STRLEN+1+1];
    int maxStrLen=0;

    for(int i=0;i<n;i++)
    {
        fgets(buff,STRLEN,inpfile);
        int tempstrlen= strrdup(&(strings[i].str),buff);
        if(tempstrlen>maxStrLen)
            maxStrLen=tempstrlen;
    }

    sort(strings,n,0);

    store(strings,n,outfile);

    for(int i=0;i<n;i++)
        free(strings[i].str);

    free(strings);

    fclose(outfile);
    fclose(inpfile);
    return 0;
}
