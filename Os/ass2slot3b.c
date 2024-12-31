#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Initial CPU burst time
    int remaining;  // Remaining burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
} Process;

void calculateTimes(Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int gantt[MAX_PROCESSES * 10]; // Gantt chart array
    int gantt_index = 0;
    bool is_completed[MAX_PROCESSES] = {false};

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
    }

    while (1) {
        bool all_completed = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && !is_completed[i]) {
                all_completed = false; // At least one process is not completed
                if (processes[i].remaining > 0) {
                    // Determine the time to execute
                    int time_to_execute = (processes[i].remaining < time_quantum) ? processes[i].remaining : time_quantum;

                    // Execute the process for the determined time
                    processes[i].remaining -= time_to_execute;
                    current_time += time_to_execute;

                    // Store the process ID in Gantt chart
                    for (int j = 0; j < time_to_execute; j++) {
                        gantt[gantt_index++] = processes[i].id;
                    }

                    // If the process is completed
                    if (processes[i].remaining == 0) {
                        processes[i].turnaround = current_time - processes[i].arrival;
                        processes[i].waiting = processes[i].turnaround - processes[i].burst;
                        is_completed[i] = true;
                    }
                }
            }
        }
        if (all_completed) break; // Exit if all processes are completed
    }

    // Print Gantt Chart
    printf("Gantt Chart:\n");
    for (int i = 0; i < gantt_index; i++) {
        printf("P%d ", gantt[i]);
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
    int n, time_quantum, i;
    Process processes[MAX_PROCESSES];

    // Set a fixed seed for random number generation
    srand(42); // Fixed seed for reproducibility

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and initial CPU burst for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst; // Initialize remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    // Simulate Round Robin Scheduling
    calculateTimes(processes, n, time_quantum);

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
// Enter arrival time and initial CPU burst for process P1: 0 5
// Enter arrival time and initial CPU burst for process P2: 1 3
// Enter arrival time and initial CPU burst for process P3: 2 8
// Enter time quantum: 2
// Gantt Chart:
// P1 P1 P2 P2 P3 P3 P1 P1 P2 P3 P3 P1 P3 P3 P3 P3 
// Average Waiting Time: 6.00
// Average Turnaround Time: 11.33

// Process Waiting Time    Turnaround Time
// P1      7               12
// P2      5               8
// P3      6               14