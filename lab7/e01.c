#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MNAMELEN 20
#define MIDLEN 20


typedef struct product
{
    char* name;
    float price;
    struct product* next;

}product;

typedef struct producer
{
    char* name;
    char* id;
    product* products;
    struct producer* next;
}producer;

FILE* myfopen(char* filename,char* mode)
{
    FILE* temp = fopen(filename,mode);
    if(temp)
        return temp;
    printf("Couldn't open File %s\n",filename);
    exit(1);
}

void* mymalloc(int size)
{
    void* temp = malloc(size);
    if(temp)
        return temp;
    printf("Couldn't allocate memory\n");
    exit(1);

}

producer* mlistinsert(producer* producerslist, char* mname, char* mid)
{
    if(!(producerslist))
    {
        producerslist = mymalloc(sizeof(producer));
        producer* toinin = producerslist;
        toinin->name = mname;
        toinin->id = mid;
        toinin->products = NULL;
        toinin->next = NULL;
        return toinin;
    }
    if(strcmp(mid,producerslist->id)<0)
    {
        producer* new = mymalloc(sizeof(producer));
        new->name = mname;
        new->id = mid;
        new->products = NULL;
        new->next = producerslist;
        return new;
    }
    producerslist->next = mlistinsert(producerslist->next,mname,mid);
    return producerslist;
}

producer* locate_producer(producer* mhead,char* id)
{
    if(!mhead)
        return NULL;
    if(strcmp(mhead->id,id)==0)
        return mhead;
    return locate_producer(mhead->next,id);
}

void plistinsert(producer* producers,char* mid,char* name,float price)
{
    if(!producers)
        exit(1);
    producer* maker = locate_producer(producers,mid);
    product* productsnode=maker->products;
    if(!productsnode)
    {
        maker->products = mymalloc(sizeof(product));
        productsnode = maker->products;
        productsnode->name = name;
        productsnode->price = price;
        productsnode->next=NULL;
        return;
    }

    product* temp = NULL;
    while(productsnode!=NULL && strcmp(name,productsnode->name)>=0)
    {
        temp = productsnode;
        productsnode=productsnode->next;
    }
    product* new = mymalloc(sizeof(product));
    new->name = name;
    new->price = price;
    new->next = productsnode;
    temp->next = new;


}

void printpData(product* productslist)
{
    if(!productslist)
        return;
    printf("\t %s costing %f\n",productslist->name,productslist->price);
    printpData(productslist->next);
}

void printmData(producer* producerslist)
{
    if(!producerslist)
        return;
    printf("The Producer %s (id: %s)has following cars:\n",producerslist->name,producerslist->id);
    printpData(producerslist->products);
    printmData(producerslist->next);
}

int main(int argc, char** argv)
{
    if(argc!=3)
        return 0;

    FILE* producerfile = myfopen(argv[1],"r");
    producer* producers = NULL;

    char mnametemp[MNAMELEN+1];
    char midtemp[MIDLEN+1];

    while(fscanf(producerfile,"%s %s\n",mnametemp,midtemp)!=EOF)
    {
        producers = mlistinsert(producers,strdup(mnametemp),strdup(midtemp));//initialize the products list head
    }

    fclose(producerfile);

    char pnametemp[MNAMELEN+1],pmidtemp[MIDLEN+1];
    float pricetemp;
    FILE* productfile = myfopen(argv[2],"r");

    while(fscanf(productfile,"%s %s %f",pmidtemp,pnametemp,&pricetemp)!=EOF)
    {
        plistinsert(producers,pmidtemp,strdup(pnametemp),pricetemp);
    }

    fclose(productfile);

    printmData(producers);
    while(producers)
    {
        printf("deleting %s\n",producers->name);
        producer* temp = producers->next;
        free(producers->name);
        free(producers->id);
        product* prodlist = producers->products;
        while(prodlist)
        {
            printf("delete status\n");
            printpData(prodlist);
            product* tem = prodlist->next;
            free(prodlist->name);
            free(prodlist);
            prodlist=tem;
        }
        free(producers);
        producers = temp;
    }

    return 0;
}
