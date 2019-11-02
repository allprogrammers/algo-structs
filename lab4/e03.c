#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME "test03.txt"
#define NAMELEN 30

typedef struct cyclist
{
    char* name;
    int identifier;
    int laps;
    float* lapTimes;
}cyclist;

FILE* testfopen(char* name,char* mode)
{
    FILE* ret = fopen(name,mode);
    if (ret) return ret;
    exit(1);
}

float calcavg(cyclist ath)
{
    float sum =0;
    for(int j=0;j<ath.laps;j++)
    {
        sum+=ath.lapTimes[j];
    }
    return sum/ath.laps;
}

void best(cyclist* cyclists,int n)
{
    int min_id=0;
    float minavg=calcavg(cyclists[0]); 
    for(int i=0;i<n;i++)
    {
        float sum =0;
        for(int j=0;j<cyclists[i].laps;j++)
        {
            sum+=cyclists[i].lapTimes[j];
        }
        
        float avg = calcavg(cyclists[i]);
        if(avg<minavg)
        {
            min_id = i;
            minavg=avg;
        }
    }

    printf("Name:%s #Id number:%d Laps:%d Times: ",cyclists[min_id].name,cyclists[min_id].identifier,cyclists[min_id].laps);
    for(int i =0;i<cyclists[i].laps;i++)
        printf("%f ",cyclists[min_id].lapTimes[i]);
    printf("(Average: %f)\n",minavg);
}

void list(cyclist* cyclists,int n)
{
    printf("Number of athletes : %d\n",n);
    for(int i=0;i<n;i++)
    {
        printf("Name: %s #Id:%d #Laps:%d\n",cyclists[i].name,cyclists[i].identifier,cyclists[i].laps);
    }
}

void detail(cyclist* cyclists,int n,char* name)
{
    for(int i=0;i<n;i++)
    {
        if(!strcmp(cyclists[i].name,name))
        {
            printf("#Id:%d #Laps:%d Times: ",cyclists[i].identifier,cyclists[i].laps);
            for(int j=0;j<cyclists[i].laps;j++)
                printf("%f ",cyclists[i].lapTimes[j]);
            printf("\n");
            return;
        }
    }
}

int notStop(cyclist* cyclists,int n)
{
    printf("Command? ");
    char item[7];
    char opname[NAMELEN+1];
    scanf("%s",item);
    if(!strcmp(item,"stop"))
    {
        printf("Program ended\n");
        return 0;
    }
    else if(!strcmp(item,"list"))
        list(cyclists,n);
    else if(!strcmp(item,"best"))
        best(cyclists,n);
    else if(!strcmp(item,"detail"))
    {
        scanf("%s",opname);
        detail(cyclists,n,opname);
    }
    return 1;
}

int main(void)
{
    //file format is 
    /*
    *number of cyclists
    *name(at most 30 chars) identifier(int) N(no of laps)
    *lap times space separated floats
    */

    FILE* list = testfopen(FNAME,"r");

    int no;

    fscanf(list,"%d",&no);

    cyclist* cyclists=malloc(sizeof(cyclist)*no);

    for(int i=0;i<no;i++)
    {
        char* tempname = malloc((NAMELEN+1)*sizeof(char));

        fscanf(list,"%s %d %d",tempname,&cyclists[i].identifier,&cyclists[i].laps);
        cyclists[i].name=strdup(tempname);
        
        free(tempname);

        cyclists[i].lapTimes = malloc(cyclists[i].laps*sizeof(float));

        for(int j=0;j<cyclists[i].laps;j++)
        {
            fscanf(list,"%f",&cyclists[i].lapTimes[j]);
        }

    }

    while(notStop(cyclists,no));

    for(int i=0;i<no;i++)
    {
        free(cyclists[i].name);
        free(cyclists[i].lapTimes);
    }

    free(cyclists);
    fclose(list);

}
