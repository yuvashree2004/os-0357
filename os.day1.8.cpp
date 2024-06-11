#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int remaining_time;  // Remaining Time
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
};

void findWaitingAndTurnaroundTimes(struct Process proc[], int n, int quantum) {
    int current_time = 0;
    int completed_processes = 0;
    int i = 0;

    while (completed_processes < n) {
        // If the process has remaining burst time
        if (proc[i].remaining_time > 0) {
            // If the remaining burst time is greater than or equal to the quantum
            if (proc[i].remaining_time > quantum) {
                current_time += quantum;
                proc[i].remaining_time -= quantum;
            } else {
                // Process will finish in this time slice
                current_time += proc[i].remaining_time;
                proc[i].waiting_time = current_time - proc[i].burst_time;
                proc[i].remaining_time = 0;
                completed_processes++;
            }
        }
        i = (i + 1) % n;
    }

    for (int j = 0; j < n; j++) {
        proc[j].turnaround_time = proc[j].waiting_time + proc[j].burst_time;
    }
}

void findAverageTimes(struct Process proc[], int n, int quantum) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    findWaitingAndTurnaroundTimes(proc, n, quantum);

    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("Average waiting time = %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time = %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    findAverageTimes(proc, n, quantum);

    return 0;
}

