#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10
#define IO_WAIT_TIME 2  // Fixed I/O waiting time for all processes

// Structure to hold process information
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

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

// Function to calculate turnaround time and waiting time
void calculateTurnaroundAndWaitingTime(int n, struct Process processes[]) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
}

// SJF Scheduling function
void SJF(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    // Sorting processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Array to track remaining burst times
    int remainingBurstTimes[n];
    for (int i = 0; i < n; i++) {
        remainingBurstTimes[i] = processes[i].burstTime;
    }

    // Gantt chart simulation
    printf("\nGantt Chart:\n");
    while (completed < n) {
        // Find processes that have arrived and are not completed
        int minBurstIndex = -1;
        int minBurstTime = 99999;  // A large number to ensure we select the shortest burst time
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && remainingBurstTimes[i] > 0) {
                if (remainingBurstTimes[i] < minBurstTime) {
                    minBurstTime = remainingBurstTimes[i];
                    minBurstIndex = i;
                }
            }
        }

        if (minBurstIndex != -1) {
            // Execute the selected process
            printf("P%d ", processes[minBurstIndex].processID);
            currentTime += remainingBurstTimes[minBurstIndex];
            processes[minBurstIndex].completionTime = currentTime;
            remainingBurstTimes[minBurstIndex] = 0;  // Mark process as completed
            completed++;
            
            // Add I/O wait time after each process (except for the last process)
            if (completed < n) {
                currentTime += IO_WAIT_TIME;
            }
        } else {
            // If no process is ready to execute, increment the time
            currentTime++;
        }
    }

    // Calculate turnaround time and waiting time for each process
    calculateTurnaroundAndWaitingTime(n, processes);

    // Output process details
    printf("\nProcessID  ArrivalTime  BurstTime  CompletionTime  WaitingTime  TurnaroundTime\n");
    for (int i = 0; i < n; i++) {
        printf("P%d         %d           %d          %d              %d             %d\n", 
               processes[i].processID, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate averages
    calculateAverages(n, processes);
}

int main() {
    srand(time(0));  // Seed the random number generator

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input arrival times and CPU burst times for each process
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].processID = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("First CPU Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    // Run SJF scheduling
    SJF(processes, n);

    return 0;
}


// Enter the number of processes: 3 

// Enter details for Process 1:
// Arrival Time: 0
// First CPU Burst Time: 4

// Enter details for Process 2:
// Arrival Time: 1
// First CPU Burst Time: 5

// Enter details for Process 3:
// Arrival Time: 2
// First CPU Burst Time: 3

// Gantt Chart:
// P1 P3 P2
// ProcessID  ArrivalTime  BurstTime  CompletionTime  WaitingTime  TurnaroundTime
// P1         0           4          4              0             4
// P2         1           5          16              10             15
// P3         2           3          9              4             7

// Average Waiting Time: 4.67
// Average Turnaround Time: 8.67