#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10
#define IO_WAIT_TIME 2  // Fixed I/O wait time

// Structure to hold process information
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingBurstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

// Function to generate random burst time for the next burst
int generateRandomBurstTime() {
    return rand() % 10 + 1;  // Random burst time between 1 and 10
}

// Function to calculate average waiting time and turnaround time
void calculateAverages(int n, struct Process processes[]) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

// Non-preemptive Priority Scheduling function
void PriorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int ganttIndex = 0;
    int ganttChart[100];

    // Initialize remaining burst time and completed flag
    for (int i = 0; i < n; i++) {
        processes[i].remainingBurstTime = processes[i].burstTime;
        processes[i].isCompleted = 0;
    }

    // Process scheduling loop
    while (completed < n) {
        int minPriority = 99999;
        int processIndex = -1;

        // Find the process with the smallest priority (highest priority)
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0 && processes[i].priority < minPriority && processes[i].isCompleted == 0) {
                minPriority = processes[i].priority;
                processIndex = i;
            }
        }

        // If a process is found, execute it
        if (processIndex != -1) {
            // Execute the process
            ganttChart[ganttIndex++] = processes[processIndex].processID;
            currentTime += processes[processIndex].remainingBurstTime;
            processes[processIndex].completionTime = currentTime;
            processes[processIndex].turnaroundTime = processes[processIndex].completionTime - processes[processIndex].arrivalTime;
            processes[processIndex].waitingTime = processes[processIndex].turnaroundTime - processes[processIndex].burstTime;
            processes[processIndex].remainingBurstTime = 0;  // Mark the process as completed
            processes[processIndex].isCompleted = 1;  // Set the process as completed
            completed++;

            // Simulate fixed I/O wait time (for all processes after they finish)
            if (completed < n) {
                currentTime += IO_WAIT_TIME;
            }

            // Generate new random burst time for the next CPU burst if applicable
            if (completed < n) {
                processes[processIndex].burstTime = generateRandomBurstTime();
                processes[processIndex].remainingBurstTime = processes[processIndex].burstTime;
            }
        } else {
            // If no process is ready to execute, increment currentTime
            currentTime++;
        }
    }

    // Output Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttIndex; i++) {
        printf("P%d ", ganttChart[i]);
    }
    printf("\n");

    // Output process details
    printf("\nProcessID  ArrivalTime  BurstTime  Priority  CompletionTime  WaitingTime  TurnaroundTime\n");
    for (int i = 0; i < n; i++) {
        printf("P%d         %d           %d          %d        %d              %d             %d\n", 
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].priority, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate averages
    calculateAverages(n, processes);
}

int main() {
    srand(time(0));  // Seed random number generator

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input details for each process
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].processID = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("First CPU Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);

        // Initialize the remaining burst time
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    // Run Priority Scheduling
    PriorityScheduling(processes, n);

    return 0;
}


// Enter the number of processes: 3

// Enter details for Process 1:
// Arrival Time: 0
// First CPU Burst Time: 4
// Priority: 2

// Enter details for Process 2:
// Arrival Time: 1
// First CPU Burst Time: 5
// Priority: 1

// Enter details for Process 3:
// Arrival Time: 2
// First CPU Burst Time: 3
// Priority: 3

// Gantt Chart:
// P1 P2 P3

// ProcessID  ArrivalTime  BurstTime  Priority  CompletionTime  WaitingTime  TurnaroundTime
// P1         0           8          2        4              0             4
// P2         1           10          1        11              5             10
// P3         2           3          3        16              11             14

// Average Waiting Time: 5.33
// Average Turnaround Time: 9.33