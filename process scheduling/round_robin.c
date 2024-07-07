#include <stdio.h>

struct Process
{
    int at, bt, temp, ct, tt, wt,pid;
};
typedef struct Process Process;

struct Gant
{
    int pid, stime;
};

typedef struct Gant Gant;
Gant gantChart[100];


void main()
{
    Process processes[10];
    int i, n, currentTime = 0, count = 0, remainingProcesses, tq, total_wt = 0, total_tt = 0;
    float avg_total_wt, avg_total_tt;
    printf(" Total number of processes: ");
    scanf("%d", &n);
    remainingProcesses = n;
    printf("Enter the Time time quantum for the process: \t");
    scanf("%d", &tq);

    printf("Enter arrival time for processes: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i].at);

    printf("Enter burst time for processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &processes[i].bt);
        processes[i].temp = processes[i].bt;
        processes[i].pid = i+1;
    }

    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].at > processes[j + 1].at)
            {
                Process temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
    int gi=0;
    gantChart[gi].stime = 0;
    gantChart[gi++].pid = -1;

    currentTime = processes[0].at;

    for (i = 0; remainingProcesses != 0;)
    {
        if (processes[i].temp <= tq && processes[i].temp > 0)
        {   gantChart[gi].pid = processes[i].pid;
            gantChart[gi++].stime = currentTime;
            currentTime = currentTime + processes[i].temp;
            processes[i].temp = 0;
            count = 1;
        }
        else if (processes[i].temp > 0)
        {
            gantChart[gi].pid = processes[i].pid;
            gantChart[gi++].stime = currentTime;
            processes[i].temp = processes[i].temp - tq;
            currentTime = currentTime + tq;
        }
        if (processes[i].temp == 0 && count == 1)
        {
            remainingProcesses--;
            processes[i].ct = currentTime;
            processes[i].wt = currentTime - processes[i].at - processes[i].bt;
            processes[i].tt = currentTime - processes[i].at;     
            total_wt = total_wt + processes[i].wt;
            total_tt = total_tt + processes[i].tt;
            count = 0;
        }
        if (i == n - 1)
        {
            i = 0;
        }
        else if (processes[i + 1].at <= currentTime)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    for(int i = 0;i<gi;i++)
        printf("--------");
    printf("\n");
    for(int i = 0;i<gi;i++)
       {if(gantChart[i].pid == -1)
       {
        printf("|      ");
        continue;
       } 
        printf("|  P%d  ",gantChart[i].pid);
        }
    printf("|\n");
    for(int i = 0;i<gi;i++)
        printf("--------");
    printf("\n");
    for(int i = 0;i<gi;i++)
        printf("%d      ",gantChart[i].stime);
    printf("%d   \n",currentTime);
    

    printf("\n Process No \t\t Burst Time \t\t total_tt \t\t Waiting Time ");
    for (int i = 0; i < n; i++)
    {
        printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", processes[i].pid, processes[i].bt, processes[i].tt, processes[i].wt);

    }
    
    avg_total_wt = total_wt * 1.0 / n;
    avg_total_tt = total_tt * 1.0 / n;
    printf("\n Average Turn Around Time: \t%f", avg_total_wt);
    printf("\n Average Waiting Time: \t%f", avg_total_tt);
}