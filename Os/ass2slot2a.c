#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10
#define IO_WAIT_TIME 2  // Fixed I/O waiting time

// Structure to hold process information
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingBurstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;  // Flag to check if the process is completed
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

// Function to generate a random CPU burst (for simplicity, between 1 and 10)
int generateRandomBurstTime() {
    return rand() % 10 + 1;
}

// Preemptive SJF Scheduling function
void PreemptiveSJF(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int ganttIndex = 0;
    int ganttChart[100];  // To store the Gantt chart for display

    // Initialize remaining burst times and set isCompleted flag to 0
    for (int i = 0; i < n; i++) {
        processes[i].remainingBurstTime = processes[i].burstTime;
        processes[i].isCompleted = 0;
    }

    // Gantt chart simulation
    printf("\nGantt Chart:\n");

    // Run the scheduling simulation until all processes are completed
    while (completed < n) {
        int minBurstTime = 99999;
        int processIndex = -1;

        // Find the process with the minimum remaining burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0 && processes[i].remainingBurstTime < minBurstTime) {
                minBurstTime = processes[i].remainingBurstTime;
                processIndex = i;
            }
        }

        // If we have a process to execute
        if (processIndex != -1) {
            ganttChart[ganttIndex++] = processes[processIndex].processID;
            currentTime++;
            processes[processIndex].remainingBurstTime--;

            // If process has finished execution
            if (processes[processIndex].remainingBurstTime == 0 && processes[processIndex].isCompleted == 0) {
                processes[processIndex].completionTime = currentTime;
                processes[processIndex].turnaroundTime = processes[processIndex].completionTime - processes[processIndex].arrivalTime;
                processes[processIndex].waitingTime = processes[processIndex].turnaroundTime - processes[processIndex].burstTime;
                processes[processIndex].isCompleted = 1;
                completed++;
                
                // Add fixed I/O wait time after each process (except for the last process)
                if (completed < n) {
                    currentTime += IO_WAIT_TIME;
                }
            }
        } else {
            // If no process is ready to execute, increment the time
            currentTime++;
        }
    }

    // Output the Gantt chart
    for (int i = 0; i < ganttIndex; i++) {
        printf("P%d ", ganttChart[i]);
    }

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

        // Generate a random burst time for subsequent bursts
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    // Run Preemptive SJF scheduling
    PreemptiveSJF(processes, n);

    return 0;
}

// PS B:\desktopBackup\Coding\Os> ./a.exe
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
// P1 P1 P1 P1 P3 P3 P3 P2 P2 P2 P2 P2
// ProcessID  ArrivalTime  BurstTime  CompletionTime  WaitingTime  TurnaroundTime
// P1         0           4          4              0             4
// P2         1           5          16              10             15
// P3         2           3          9              4             7

// Average Waiting Time: 4.67
// Average Turnaround Time: 8.67