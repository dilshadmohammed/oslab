#include <stdio.h>

struct process
{
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int completed;
};

struct gantchart{
    int id;
    int st;
    int ct;
}gt[20];

void main(){
    int n;
    printf("Enter the no of process : ");
    scanf("%d",&n);
    struct process p[n];
    printf("Enter the at and bt");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&p[i].at);
        scanf("%d",&p[i].bt);
        p[i].completed=0;
        p[i].pid=i+1;
    }
    struct process temp;
    float avtat=0,avwt=0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(p[j].at>p[j+1].at){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
        
    }
    
    int t=0,count=0,num=0,idle=0;
    while(count != n)
    {
        int min=-1;
        for (int j = 0; j < n; j++)
        {
            if(p[j].at<=t && p[j].completed==0){
                if(min==-1 || p[j].bt<p[min].bt){
                    min=j;
                }
            }
        }
        if(min==-1){
            if(idle==0){
                gt[num].id=-1;
                gt[num].st=t;
                idle=1;
            }
            t++;
            continue;
        }
        if(idle==1){
                gt[num].ct=t;
                num++;
                idle=0;
        }
        gt[num].id=p[min].pid;
        gt[num].st=t;
        t+=p[min].bt;
        gt[num].ct=t;
        num++;
        p[min].tat=t-p[min].at;
        p[min].wt=p[min].tat-p[min].bt;
        p[min].completed=1;
        avtat+=p[min].tat;
        avwt+=p[min].wt;
        count++;  
    }
    printf("Average tat : %2f\n",avtat/n);
    
    printf("Average wt : %2f\n",avwt/n);

    printf("-----------------------------------------------\n|");
    for (int i = 0; i < num; i++)
    {
        if (gt[i].id==-1)
        {
            printf("  idle   |");
        }
        else
        {printf("    P%d    |",gt[i].id);}
    }
    printf("\n-----------------------------------------------\n");
    for (int i = 0; i < num; i++)
    {
        printf("%d         ",gt[i].st);
    }
    printf("%d\n\n",gt[num-1].ct);
    
}