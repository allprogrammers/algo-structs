#include <stdio.h>
#include <stdlib.h>

#define MAX 99
#define W_MAX 19

int strrlen(char* word)
{
    int i;
    for(i=0;word[i]!='\0';i++){}
    return i;
}
int issalpha(char chr)
{
    return (chr>='a' && chr<='z') || (chr>='A' && chr<='Z');
}

int isupperalpha(char chr)
{
    return chr>='A' && chr<='Z';
}

char* tolowerr(char* str)
{
    for(int i=0;str[i]!='\0';i++)
    {
        if(isupperalpha(str[i]))
        {
            str[i]+='a'-'A';
        }
    }
    return str;
}

FILE* testfopen(char* filename,char* mode)
{
    FILE *res = fopen(filename,mode);
    if(res)
        return res;
    exit(0);
}

int strrcmp(char* word,char* buff,int start)
{
    for(int i=start;word[i-start]!='\0';i++)
    {
        if(word[i-start]!=buff[i])
        {
            return 0;
        }
    }
    return 1;
}

void count(char** words,char buff[],int wordscount[],int wordcount)
{
    for(int i=0;i<wordcount;i++)
    {
        printf("looking for %s\n",words[i]);
        char* word=tolowerr(words[i]);
        int wordlen = strrlen(word);
        int flag = 0;
        for(int j=0;buff[j]!='\0';j++)
        {
            if(buff[j]!=word[0] || issalpha(buff[j+wordlen]))
            {
                continue;
            }
            if(strrcmp(word,buff,j))
            {
                printf("found\n");
                wordscount[i]++;
            }
        }
    }
}

int main(int argc,char **argv)
{
    if(argc!=3)
        return 0;

    FILE *wordfile = testfopen(argv[1],"r");
    FILE *textfile = testfopen(argv[2],"r");

    int wordcount;
    fscanf(wordfile,"%d\n",&wordcount);

    // an array of strings of length wordcount 
    char** words = calloc(wordcount,sizeof(char*));
    for(int i=0;i<wordcount;i++)
    {
        words[i]=calloc(W_MAX+1,sizeof(char));
        fscanf(wordfile,"%s\n",words[i]);
    }

    char buff[MAX+1+1];
    int *wordscount = calloc(wordcount,sizeof(int));
    while(fgets(buff,MAX,textfile))
    {
        printf("%s",tolowerr(buff));
        count(words,tolowerr(buff),wordscount,wordcount);
    }

    for(int i=0;i<wordcount;i++)
    {
        printf("count of %s is %d\n",words[i],wordscount[i]);
    }
    free(wordscount);
    for(int i=0;i<wordcount;i++)
        free(words[i]);
    free(words);

    fclose(wordfile);
    fclose(textfile);
    return 0;
}
