#include <stdio.h>

typedef struct {
    int pid, at, bt, remaining_time, wt, tt, ct, status;
} Process;

typedef struct {
    int pid, st, ct;
} GantChart;

int q[100], front = -1, rear = -1;

void enqueue(int item) {
    if (front == -1 && rear == -1)
        front++;
    rear++;
    q[rear] = item;
}

int dequeue() {
    int item = q[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front++;
    }
    return item;
}

int main() {
    int n, idle = 0, remainingProcesses, gc_index = 0, tq;
    float avtt = 0, avwt = 0;

    printf("Enter time quanta: ");
    scanf("%d", &tq);
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    GantChart gc[100];
    remainingProcesses = n;

    printf("Enter the (at bt):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].remaining_time = p[i].bt;
        p[i].pid = i + 1;
        p[i].status = 0;
    }

    // Sort processes by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    for (int time = 0; remainingProcesses > 0;) {
        // Enqueue processes that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].status == 0) {
                enqueue(i);
                p[i].status = 1;
            }
        }

        if (idle == 0 && front == -1) {
            // Handle idle time
            gc[gc_index].pid = -1;
            gc[gc_index].st = time;
            idle = 1;
            time++;
        } else if (front != -1) {
            if (idle) {
                gc[gc_index++].ct = time;
                idle = 0;
            }

            int k = dequeue();
            gc[gc_index].st = time;
            gc[gc_index].pid = p[k].pid;

            if (p[k].remaining_time <= tq) {
                time += p[k].remaining_time;
                p[k].ct = time;
                p[k].wt = time - p[k].at - p[k].bt;
                p[k].tt = p[k].wt + p[k].bt;
                p[k].remaining_time = 0;

                gc[gc_index].ct = time;
                remainingProcesses--;  // Decrement remaining processes count
                p[k].status = 2;

                avwt += p[k].wt;
                avtt += p[k].tt;
            } else {
                time += tq;
                gc[gc_index].ct = time;
                p[k].remaining_time -= tq;

                // Enqueue newly arrived processes during the time quantum
                for (int i = 0; i < n; i++) {
                    if (p[i].at <= time && p[i].status == 0) {
                        enqueue(i);
                        p[i].status = 1;
                    }
                }
                enqueue(k);  // Re-enqueue the current process
            }
            gc_index++;
        } else {
            time++;
        }
    }

    printf("\nAVERAGE WAITING TIME : %.2f", (avwt / n));
    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", (avtt / n));

    // Display Gantt chart
    printf("\n\nGANTT CHART\n");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < gc_index; i++) {
        if (gc[i].pid == -1) {
            printf("| Idle ");
        } else {
            printf("| P%d ", gc[i].pid);
        }
    }
    printf("|\n");
    printf("--------------------------------------------------------------\n");
    printf("%d", gc[0].st);
    for (int i = 0; i < gc_index; i++) {
        printf("\t%d", gc[i].ct);
    }
    printf("\n");

    return 0;
}
