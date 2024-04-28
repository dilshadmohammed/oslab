#include <stdio.h>

struct Process{
    int pid,at,bt,rm,ct,tt,wt,isComplete,inQueue;
};
typedef struct Process Process;

struct Queue {
    int q[100];
    int r,f;
};
typedef struct Queue Queue;

int currentTime = 0;
int programsExecuted = 0;

void sort_at(Process processes[],int n){
        int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if ( processes[j].at > processes[j+1].at) {
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void sort_pid(Process processes[],int n){
        int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if ( processes[j].pid > processes[j+1].pid) {
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void checkForNewArrivals(Process processes[], int n, Queue *readyQueue) {
    for (int i = 0; i < n; i++) {
        Process p = processes[i];

        if (p.at <= currentTime && !p.inQueue && !p.isComplete) {
            processes[i].inQueue = 1;
            readyQueue->q[++readyQueue->r] = i;
        }
    }
}


void updateQueue(Process processes[], int n, int tq, Queue *readyQueue) {
    int i = readyQueue->q[readyQueue->f++];

    if (processes[i].bt <= tq) {
        processes[i].isComplete = 1;
        currentTime += processes[i].rm;
        processes[i].ct = currentTime;
        processes[i].wt = currentTime - processes[i].at - processes[i].bt + tq;
        processes[i].tt = processes[i].wt + processes[i].bt;
        programsExecuted++;

        if (programsExecuted != n)
            checkForNewArrivals(processes, n, readyQueue);
    } else {
        processes[i].rm -= tq;
        currentTime += tq;

        if (programsExecuted != n)
            checkForNewArrivals(processes, n, readyQueue);
        readyQueue->q[(readyQueue->r + 1) % 100] = i; // Circular queue enqueue
        readyQueue->r = (readyQueue->r + 1) % 100; // Update rear index
    }
}

void roundRobin(Process processes[], int n, int tq) {
    Queue readyQueue;
    readyQueue.r = -1;
    readyQueue.f = 0;
    readyQueue.q[++readyQueue.r] = 0;
    processes[0].inQueue = 1;
    currentTime = 0;
    while (readyQueue.r >= readyQueue.f) {
        updateQueue(processes, n, tq, &readyQueue);
    }
}


int main(){
    int n,tq;

    printf("Enter the number of process: ");
    scanf("%d",&n);

    printf("Enter the time quantum: ");
    scanf("%d",&tq);

    Process processes[n+1];

    printf("Enter arrival time and burst time of each process:\n");
    for(int i = 0;i<n;i++){
        printf("P%d : ",i+1);
        scanf("%d%d",&processes[i].at,&processes[i].bt);
        processes[i].rm = processes[i].bt;
        processes[i].pid = i+1;
    }


    sort_at(processes,n);
    roundRobin(processes,n,tq);
    sort_pid(processes,n);

    int total_tt=0,total_wt=0;
    printf("\n");
    for(int i = 0;i<n;i++){
        printf("P%d wt=%2d tt=%2d\n",processes[i].pid,processes[i].wt,processes[i].tt);
        total_tt += processes[i].tt;
        total_wt += processes[i].wt;
    }

    printf("\nTotal TT=%3d     Total WT=%3d      Avg TT=%.2f   Avg WT=%.2f\n",total_tt,total_wt,((float)total_tt/n),((float)total_wt/n));

    return 0;
}