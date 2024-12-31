#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10

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

// FCFS Scheduling function
void FCFS(struct Process processes[], int n) {
    int currentTime = 0;

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

    // Calculate completion time, waiting time, and turnaround time for each process
    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;  // Wait for the next process to arrive
        }
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        currentTime = processes[i].completionTime;
    }

    // Output Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].processID);
    }
    printf("\n");

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

        // We do not randomly generate the burst time anymore
    }

    // Run FCFS scheduling
    FCFS(processes, n);

    return 0;
}
