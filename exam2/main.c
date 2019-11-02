#include <stdio.h>
#include <stdlib.h>//added
#include "mylib.h"
#include <string.h>//added

#define F "file.txt"


typedef struct Mu
{
    char* name;
    int no_slots;
    char** slots;
    int** seats_available_on_at;
    struct Mu *left, *right;
}Mu;

Mu* museums = NULL;

typedef struct book
{
    char* name;//changed from v_name => name
    struct res* rese;//changed reserves* => struct res*
    struct book *left,*right;//changed from "book"=>"stuct book"
}book;

book* visitor_book = NULL;//added
typedef struct res
{
    Mu* mp;//modified to store the museum pointer instead of name to save spaces and for easier code modification in the future
    int people;
    int day;
    int slot_ind;//modified to store the slot index instead of name to save space and for easier future code modification
    struct res* next;
}res;

int slot_lookup(Mu* museum,char* slot)
{
    for(int i=0;i<museum->no_slots;i++)
    {
        if(!strcmp(slot,museum->slots[i]))
            return i;
    }
    return -1;
}//O(1)

Mu* mu_binary_add(Mu* root,Mu* toadd)
{
    if(root == NULL)
    {
        return toadd;
    }
    int ans = strcmp(toadd->name,root->name);
    if(ans<0)
    {
        root->left = mu_binary_add(root->left,toadd);
        return root;
    }else if(ans>0)
    {
        root->right = mu_binary_add(root->right,toadd);
        return root;
    }else
    {
        printf("already exists\n");
        return NULL;
    }
}//O(log(n)) where n is the total number of musuems(assuming the tree is balanced)

Mu* mpointerto(Mu* ms,char* name)
{
    if(ms==NULL)
    {
        return NULL;
    }
    int ans = strcmp(ms->name,name);
    if(ans<0)
    {
        return mpointerto(ms->right,name);
    }else if(ans>0)
    {
        return mpointerto(ms->left,name);
    }
    return ms;
}//O(log(n)) where n is the total number of museums

book* pointerto(book* vb, char* name, int create)
{
    if(vb==NULL)
        return NULL;
    int ans = strcmp(vb->name,name);
    if(ans<0)
    {
        if(vb->right==NULL)
        {
            if(create)
            {
                book* new = mymalloc(sizeof(book));
                new->name = strdup(name);
                new->rese = NULL;
                new->left = NULL;
                new->right = NULL;
                vb->right =  new;
                return new;
            }
        }
        return pointerto(vb->right,name,create);
    }
    if(ans>0)
    {
        if(vb->left==NULL)
        {
            if(create)
            {
                book* new = mymalloc(sizeof(book));
                new->name = strdup(name);
                new->rese = NULL;
                new->left = NULL;
                new->right = NULL;
                vb->left = new;
                return new;
            }
        }
        return pointerto(vb->left,name,create);
    }
    return vb;
}//O(log(v)) where v is the total number of visitors

int museum_decrease(Mu* museum,char* slot,int day,int people)
{
    if(!museum)
        return -1;

    int ind = slot_lookup(museum,slot);

    if(ind ==-1)
        return -2;
    if(museum->seats_available_on_at[ind][day-1]<people)
        return -3;
    else
    {
        museum->seats_available_on_at[ind][day-1]-=people;
    }
    return ind;
}//O(1)

void printall(res* rese)
{
    if (rese==NULL)
        return;
    printf("%s, %d, %s, %d\n",rese->mp->name,rese->people,rese->mp->slots[(rese->slot_ind)],rese->day);//modified to add arguements
    printall(rese->next);
}//O(log(v)+R) where v is the number of visitors and R is the maximum number of reservations made by any visitor

void printres(void)
{
    char name[102];
    printf("Please enter the name of the visitor\n");
    scanf("%s",name);
    book* vb = pointerto(visitor_book,name,0);
    if(vb == NULL)
    {
        printf("Visitor not found\n");
    }else
        printall(vb->rese);
}//O(R) where R is the maximum number of reservations made by any individual visitor

void list_add(book* vref,Mu* mp,int day,int people,int slot_ind)
{
    res* newres = mymalloc(sizeof(res));
    newres->next = vref->rese;
    vref->rese = newres;
    newres->mp = mp;
    newres->day= day;
    newres->people=people;
    newres->slot_ind = slot_ind;
}//O(1)

void addres(book* vb,Mu* mp,int day,int people,char* slot)//return type changed from int to void
{
    //removed becase no longer needed
    /*if (vb==NULL)
    {
        book* node = binary_add(visitor,1);
        vb=node;
    }*/

    int slot_ind = museum_decrease(mp,slot,day,people);//modified from directly putting in the if condition to test for different errors
    //added for error testing
    if(slot_ind==-3)
        printf("Capacity exceeded\n");
    else if(slot_ind==-2)
        printf("Slot not found\n");
    else if(slot_ind==-1)
        printf("Museum not found\n");
    else
        list_add(vb,mp,day,people,slot_ind);
}//O(1)

void reserve(void)
{
    printf("Please enter the details\n");
    char m_name[101];
    int day;
    int people;
    char slot[12];
    char fvisitor[101];
    int ans2 = scanf("%100[^,], %d, %11[^,], %d,%100[^\n]",m_name,&day,slot,&people,fvisitor);
    char* visitor = fvisitor+1;
    if(ans2<5 || visitor[0]=='\0')//changed the order of the if statements to be more logical
    {
        printf("Wrong format\n");
        return;
    }else if(day<1 || day>365)
    {
        printf("Day should be between 1 and 365 included\n");
        return;
    }

    book* vb = NULL;
    //added to create the first node
    if(visitor_book==NULL)
    {
        visitor_book=mymalloc(sizeof(book));
        visitor_book->name = strdup(visitor);
        visitor_book->left = NULL;
        visitor_book->right = NULL;
        visitor_book->rese = NULL;
        vb = visitor_book;
    }
    else
    {
        vb = pointerto(visitor_book,visitor,1);//added another argument
    }
    Mu* mp = mpointerto(museums,m_name);//added
    addres(vb,mp,day,people,slot);//modified m_name=>mp to pass the whole object instead of just the name
 
    return;
}//O(log(v)+log(m)+O(1)) which is O(log(v))


void readfile(char* f)
{
    FILE* fp = safefopen(f,"r");
    char name[102];
    int slots;
    
    while(fscanf(fp,"%s %d\n",name,&slots)==2)//added to check for return value instead of EOF
    {
        Mu* new = mymalloc(sizeof(Mu));
        new->name = strdup(name);
        new->no_slots = slots;
        new->slots = mymalloc(slots*sizeof(char*));
        new->seats_available_on_at = mymalloc(slots*sizeof(int*));//changed int => int*
        new->left = NULL;
        new->right = NULL;
        for(int i=0;i<slots;i++)//O(S) where S is the maximum number of slots among museums
        {
            new->seats_available_on_at[i] = mymalloc(365*sizeof(int));
            char s_name[13];//added
            int seats;//added;
            fscanf(fp,"%s %d\n",s_name,&seats);//modified to store in temporary variables instead of directly putting in the struct
            new->slots[i]=strdup(s_name);//added
            for(int j=0;j<365;j++)
            {
                new->seats_available_on_at[i][j]=seats;
            }
        }
        museums = mu_binary_add(museums,new);//added
    }
    fclose(fp);//added
}//O(M*(S+log(M)) = O(M*S+Mlog(M))=O(Mlog(M)) where M is the number of muesums

void freeMU(Mu* museums)
{
    if(museums==NULL)
        return;
    int tmp = museums->no_slots;
    free(museums->name);
    for(int i=0;i<tmp;i++)
    {
        free(museums->slots[i]);
        free(museums->seats_available_on_at[i]);
    }
    free(museums->slots);
    free(museums->seats_available_on_at);
    freeMU(museums->left);
    freeMU(museums->right);
    free(museums);
}//O(M)
void freeRES(res* rese)
{
    if(!rese)
        return;
    freeRES(rese->next);
    free(rese);
}//O(R)
void freeVB(book* vb)
{
    if(vb==NULL)
        return;
    free(vb->name);
    freeRES(vb->rese);
    freeVB(vb->left);
    freeVB(vb->right);
    free(vb);
}//O(V*R)

int main(void)
{
    readfile(F);//removed "museums=" becauses museums is a global variable
    while(1)//changed true =>1
    {
        printf("1)New \n2)Show \n3)exit\n");//added the exit part
        int resp=0;
        scanf("%d",&resp);
        while(getchar()!='\n');//added
        if(resp==1)
            reserve();//removed the arguments
        else if(resp==2)//added the if clause
            printres();//removed the arguments
        else if(resp==3) break;//added
    }
    freeMU(museums);
    freeVB(visitor_book);
    return 0;
}//O(Mlog(M)+log(V)+R+M+V*R)=O(Mlog(M)+log(V)+V*R)
