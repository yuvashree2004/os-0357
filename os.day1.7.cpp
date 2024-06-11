#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;            // Process ID
    int burst_time;     // Burst Time
    int waiting_time;   // Waiting Time
    int turnaround_time; // Turnaround Time
    bool completed;     // Completion status
};

void findWaitingAndTurnaroundTimes(struct Process proc[], int n) {
    int completed_processes = 0;
    int current_time = 0;
    int min_burst_index;

    while (completed_processes < n) {
        // Find the process with the smallest burst time that has not yet completed
        min_burst_index = -1;
        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && (min_burst_index == -1 || proc[i].burst_time < proc[min_burst_index].burst_time)) {
                min_burst_index = i;
            }
        }

        // Execute the selected process
        current_time += proc[min_burst_index].burst_time;
        proc[min_burst_index].turnaround_time = current_time;
        proc[min_burst_index].waiting_time = proc[min_burst_index].turnaround_time - proc[min_burst_index].burst_time;
        proc[min_burst_index].completed = true;

        completed_processes++;
    }
}

void findAverageTimes(struct Process proc[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    findWaitingAndTurnaroundTimes(proc, n);

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
        proc[i].completed = false;
    }

    findAverageTimes(proc, n);

    return 0;
}

