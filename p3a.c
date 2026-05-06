#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void inputProcesses(Process p[], int *n) {
    printf("Enter number of processes: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);

        p[i].pid = i + 1;

        scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);

        p[i].remaining_time = p[i].burst_time;
    }
}

void sjfPreemptive(Process p[], int n) {
    int time = 0, completed = 0, min_index;
    int shortest;
    int is_completed[MAX_PROCESSES] = {0};

    printf("\n--- Shortest Job First (Preemptive) ---\n");

    while (completed != n) {
        shortest = 1000000000;
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time &&
                !is_completed[i] &&
                p[i].remaining_time < shortest &&
                p[i].remaining_time > 0) {

                shortest = p[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
        } else {
            p[min_index].remaining_time--;
            time++;

            if (p[min_index].remaining_time == 0) {
                p[min_index].completion_time = time;

                p[min_index].turnaround_time =
                    p[min_index].completion_time - p[min_index].arrival_time;

                p[min_index].waiting_time =
                    p[min_index].turnaround_time - p[min_index].burst_time;

                is_completed[min_index] = 1;
                completed++;
            }
        }
    }

    float total_tat = 0, total_wt = 0;

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);

        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
    }

    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time = %.2f\n", total_wt / n);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n;

    inputProcesses(processes, &n);
    sjfPreemptive(processes, n);

    return 0;
}
