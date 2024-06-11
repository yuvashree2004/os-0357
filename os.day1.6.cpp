#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;             // Process ID
    int burst_time;      // Burst Time
    int remaining_time;  // Remaining Time
    int priority;        // Priority
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
    int arrival_time;    // Arrival Time
    bool completed;      // Completion Status
};

void findWaitingAndTurnaroundTimes(struct Process proc[], int n, int total_time) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void preemptivePriorityScheduling(struct Process proc[], int n) {
    int total_time = 0;
    int completed_processes = 0;
    int min_priority_index;
    int shortest_remaining_time;
    bool process_selected;

    while (completed_processes < n) {
        min_priority_index = -1;
        shortest_remaining_time = -1;
        process_selected = false;

        // Select the process with the highest priority that is ready to execute
        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && proc[i].arrival_time <= total_time) {
                if (min_priority_index == -1 || proc[i].priority < proc[min_priority_index].priority) {
                    min_priority_index = i;
                    process_selected = true;
                } else if (proc[i].priority == proc[min_priority_index].priority && proc[i].remaining_time < proc[min_priority_index].remaining_time) {
                    min_priority_index = i;
                    process_selected = true;
                }
            }
        }

        if (process_selected) {
            proc[min_priority_index].remaining_time--;
            total_time++;

            // If a process gets completed
            if (proc[min_priority_index].remaining_time == 0) {
                proc[min_priority_index].completed = true;
                completed_processes++;
                proc[min_priority_index].waiting_time = total_time - proc[min_priority_index].arrival_time - proc[min_priority_index].burst_time;
            }
        } else {
            total_time++;
        }
    }

    findWaitingAndTurnaroundTimes(proc, n, total_time);
}

void findAverageTimes(struct Process proc[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    preemptivePriorityScheduling(proc, n);

    printf("Process ID\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].priority, proc[i].arrival_time, proc[i].waiting_time, proc[i].turnaround_time);
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
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &proc[i].priority);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].completed = false;
    }

    findAverageTimes(proc, n);

    return 0;
}

