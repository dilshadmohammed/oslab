#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].pid = i + 1;
    }

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                // Swap processes
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    int total_waiting_time = 0, total_turnaround_time = 0;
    int currentTime = proc[0].arrival_time; // Start time

    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrival_time) {
            currentTime = proc[i].arrival_time; // Move current time forward if there is no arrived processes
        }
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        total_turnaround_time += proc[i].turnaround_time;
        total_waiting_time += proc[i].waiting_time;
        currentTime += proc[i].burst_time;
    }

    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);

    return 0;
}
