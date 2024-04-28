#include <stdio.h>


struct Process {
    int pid; 
    int arrival_time; 
    int burst_time; 
    int waiting_time; 
    int turnaround_time;
    int completed; 
};


void sjf(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int completed = 0, current_time = 0, shortest;

    while (completed != n) {
        shortest = -1;
        // Find the shortest job among the arrived processes
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && !proc[i].completed) {
                if (shortest == -1 || proc[i].burst_time < proc[shortest].burst_time) {
                    shortest = i;
                }
            }
        }

        // If no process is found, move to next time unit
        if (shortest == -1) {
            current_time++;
            continue;
        }

        // Execute the shortest job
        proc[shortest].waiting_time = current_time - proc[shortest].arrival_time;
        proc[shortest].turnaround_time = proc[shortest].waiting_time + proc[shortest].burst_time;
        total_waiting_time += proc[shortest].waiting_time;
        total_turnaround_time += proc[shortest].turnaround_time;
        proc[shortest].completed = 1;
        completed++;
        current_time += proc[shortest].burst_time;
    }

    // Print the results
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);
}

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
        proc[i].completed = 0;
    }

    // Perform SJF scheduling
    sjf(proc, n);

    return 0;
}
