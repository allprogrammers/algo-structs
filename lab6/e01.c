#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 50

typedef struct node
{
    char* word;
    int freq;
    struct node* next;
}node;

FILE* testfopen(char* filename,char* mode)
{
    FILE* temp = fopen(filename,mode);
    if (temp)
        return temp;
    exit(1);
}

char* tolowers(char* str)
{
    for(int i=0;str[i]!='\0';i++)
    {
        str[i]=tolower(str[i]);
    }
    return strdup(str);
}

node* list_found(node* head,char* word)
{
    if(!head)
    {
        return NULL;
    }
    if(!strcmp(head->word,word))
    {
        return head;
    }
    return list_found(head->next,word);
}

void node_update_freq(node* cursor,int quantity)
{
    cursor->freq +=quantity;
}

node* node_add(node* head,char* word)
{
    node* newhead = malloc(sizeof(node));
    newhead->word = word;
    newhead->freq = 1;
    newhead->next = head;
    return newhead;
}

int main(int argc,char** argv)
{
    if(argc!=3)
        return 1;
    FILE* ftr = testfopen(argv[1],"r");
    
    node* head = NULL;

    char buff[MAXLEN+1];

    while(fscanf(ftr,"%s",buff)!=EOF)
    {
        char* lowered = tolowers(buff);
        node* found = list_found(head,lowered);
        if(found)
        {
            node_update_freq(found,1);
            free(lowered);
        }else
        {
            head = node_add(head,lowered);
        }
    }
    fclose(ftr);

    FILE* ftwt = testfopen(argv[2],"w");

    node* cursor = head;

    while(cursor)
    {
        fprintf(ftwt,"%s %d\n",cursor->word,cursor->freq);
        node* temp = cursor->next;
        free(cursor->word);
        free(cursor);
        cursor = temp;
    }
    fclose(ftwt);

    return 0;
}
