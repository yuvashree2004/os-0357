#include <stdio.h>

struct Process {
    int pid;            // Process ID
    int burst_time;     // Burst Time
    int waiting_time;   // Waiting Time
    int turnaround_time; // Turnaround Time
};

void findWaitingTime(struct Process proc[], int n) {
    // Waiting time for the first process is 0
    proc[0].waiting_time = 0;

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void findTurnaroundTime(struct Process proc[], int n) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void findAverageTimes(struct Process proc[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    findWaitingTime(proc, n);
    findTurnaroundTime(proc, n);

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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    findAverageTimes(proc, n);

    return 0;
}

