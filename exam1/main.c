#include <stdio.h>
#include <string.h>
#include <stdlib.h> //added

typedef struct node node;
typedef struct al adj_list;
struct node
{
    char* name;
    int color;
    adj_list* to;
    struct node* next;
};

struct al
{
    node* pointer;
    struct al* next;
};

void free_adj(adj_list* N)
{
    if(!N)
        return;
    free_adj(N->next);
    free(N);
}

void freeG(node* root)
{
    if (!root)
        return;
    free(root->name);
    free_adj(root->to);//modified from root->adj_list to root->to
    freeG(root->next);
    free(root);
}

int printG(node* G)
{
    int max=0;
    while(G)//removed not
    {
        printf("V %s colored %d\n",G->name,G->color);//added newline
        if(G->color>max)
            max = G->color;
        G=G->next;
    }
    return max;
}

FILE* myfopen(char* fname, char* m)
{
    FILE* tmp = fopen(fname,m);
    if(tmp)
        return tmp;
    exit(1);
}

void* mymalloc(int size)
{
    void* tmp = malloc(size);
    if(tmp)
        return tmp;
    exit(1);
}

void color_func(node* root)//changed name because of name conflict
{
    if(root==NULL) return;
    
    if(root->color!=-1) return;

    //if(root->color!=-1)
    //{
    //    color_func(root->next);
    //    return;
    //}//removed to avoid excessive recursion calls

    int color=0;
    adj_list* temp = root->to;
    while(temp)//removed the not
    {
        if(temp->pointer->color==color)
        {
            color++;
            temp = root->to;
        }else
            temp = temp->next;
    }

    root->color=color;
    adj_list* tmp = root->to;
    while(tmp)//removed the not
    {
        color_func(tmp->pointer);//tmp->pointer instead of tmp
        tmp = tmp->next;
    }
    //color_func(root->next);//removed to avoid excessive recursion calls
}

void insert_adj(node* f,node* s)
{
    //to add s to f's adjlist
    adj_list* tmp = f->to;
    adj_list* new = mymalloc(sizeof(adj_list));//mymalloc instead of malloc
    new->pointer = s;
    new->next = tmp;
    f->to=new;
    //to add f to s's adjlist
    tmp = s->to;
    new = mymalloc(sizeof(adj_list));//mymalloc instead of malloc
    new->pointer = f;
    new->next = tmp;
    s->to = new;
}

node* pointerto(char* name, node* graph)
{
    if(graph==NULL)//special case for the sentinel
    {
        node* new = mymalloc(sizeof(node));
        new->name = strdup(name);
        new->next = NULL;
        new->to=NULL;//added
        new->color=-1;
        return new;
    }
    node* temp = graph;
    while(temp!=NULL)
    {
        if(strcmp(temp->name,name)==0)
            return temp;
        temp=temp->next;//added
    }

    node* new = mymalloc(sizeof(node));
    new->name = strdup(name);
    node* tp = graph->next;
    graph->next= new;
    new->next = tp;
    new->to = NULL;//added
    new->color=-1;
    return new;
}

void readGraph(FILE* fp,node* graph)
{
    char n1[101],n2[101];
    while(fscanf(fp,"%s %s \n",n1,n2)!=EOF)//added EOF
    {
        node* nf = pointerto(n1,graph);
        node* ns = pointerto(n2,graph);//added the second argument
        insert_adj(nf,ns);
    }
}


int main(void)
{
    char fname[100];
    scanf("%s",fname);
    FILE* fp = myfopen(fname,"r");
    node* graph = pointerto("sentinel",NULL);//changed from graph = NULL
    readGraph(fp,graph);//
    fclose(fp);//added
    //to check how the graph was read
    /*node* testtmp = graph->next;
    while(testtmp)
    {
        //print name of the current node and it's adj list and move next
        printf("%s\n",testtmp->name);
        adj_list* tmpadj = testtmp->to;
        while(tmpadj)
        {
            printf("is adj to %s\n",tmpadj->pointer->name);
            tmpadj=tmpadj->next;
        }
        testtmp = testtmp->next;
    }*/
    //end test
    node* nodetocolor = graph->next;//added to start after the sentinel
    /*
     *while loop added to make sure all nodes are colored.. 
     *in the exam it was done by recursion 
     *but the loop is not required if the graph is colored
     */
    while(nodetocolor)
    {
        color_func(nodetocolor);
        nodetocolor=nodetocolor->next;
    }
    int min_color=printG(graph->next);//changed graph to graph->next to avoid sentinel
    printf("\nmin color required are %d\n",min_color+1);//added plus 1 to account for color zero
    freeG(graph);
    return 0;
}
