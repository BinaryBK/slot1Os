#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Initial CPU burst time
    int priority;   // Priority (lower number means higher priority)
    int remaining;  // Remaining burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
} Process;

void calculateTimes(Process processes[], int n, int total_time) {
    int completed = 0, current_time = 0;
    int i, min_priority_index;
    bool is_completed[MAX_PROCESSES] = {false};

    while (completed < n) {
        min_priority_index = -1;

        // Find the process with the highest priority that has arrived
        for (i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && !is_completed[i]) {
                if (min_priority_index == -1 || processes[i].priority < processes[min_priority_index].priority) {
                    min_priority_index = i;
                }
            }
        }

        if (min_priority_index != -1) {
            // Execute the process for 1 time unit
            processes[min_priority_index].remaining--;
            current_time++;

            // If the process is completed
            if (processes[min_priority_index].remaining == 0) {
                processes[min_priority_index].turnaround = current_time - processes[min_priority_index].arrival;
                processes[min_priority_index].waiting = processes[min_priority_index].turnaround - processes[min_priority_index].burst;
                is_completed[min_priority_index] = true;
                completed++;
            }

            // Generate the next CPU burst randomly (for simplicity, we use a fixed range)
            if (processes[min_priority_index].remaining == 0) {
                processes[min_priority_index].burst = rand() % 5 + 1; // Random burst time between 1 and 5
                processes[min_priority_index].remaining = processes[min_priority_index].burst;
            }
        } else {
            // If no process is ready, increment time
            current_time++;
        }
    }
}

void printGanttChart(Process processes[], int n) {
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].id);
    }
    printf("\n");
}

void printAverageTimes(Process processes[], int n) {
    float total_waiting = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++) {
        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
    int n, i;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, initial CPU burst, and priority for process P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
        processes[i].remaining = processes[i].burst; // Initialize remaining time
    }

    // Simulate Preemptive Priority Scheduling
    calculateTimes(processes, n, 0);

    // Print Gantt Chart
    printGanttChart(processes, n);

    // Print average waiting and turnaround times
    printAverageTimes(processes, n);

    // Print individual process times
    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].waiting, processes[i].turnaround);
    }

    return 0;
}

// PS B:\desktopBackup\Coding\Os> ./a.exe
// Enter number of processes: 3
// Enter arrival time, initial CPU burst, and priority for process P1: 0 5 1
// Enter arrival time, initial CPU burst, and priority for process P2: 1 3 2 
// Enter arrival time, initial CPU burst, and priority for process P3: 2 8 3
// Gantt Chart:
// P1 P2 P3 
// Average Waiting Time: 3.33
// Average Turnaround Time: 8.67

// Process Waiting Time    Turnaround Time
// P1      0               5
// P2      4               7
// P3      6               14