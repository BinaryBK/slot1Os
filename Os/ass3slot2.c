#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Global variables for the matrices and vectors
int Allocation[MAX_PROCESSES][MAX_RESOURCES];
int Max[MAX_PROCESSES][MAX_RESOURCES];
int Need[MAX_PROCESSES][MAX_RESOURCES];
int Available[MAX_RESOURCES];
int Request[MAX_RESOURCES];
int Finish[MAX_PROCESSES];
int Safe[MAX_PROCESSES];
int n, m;  // n = number of processes, m = number of resources

// Function prototypes
void acceptAllocation();
void acceptMax();
void acceptAvailable();
void displayMatrices();
void displayAvailable();
void findNeed();
void acceptRequest();
int resourceRequestAlgorithm(int proc);
void safetyAlgorithm();

// Main function
int main() {
    int option;

    // Get the number of processes and resources
    printf("Enter number of processes and number of resources: ");
    scanf("%d%d", &n, &m);

    while(1) {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Accept Allocation\n");
        printf("2. Accept Max\n");
        printf("3. Accept Available\n");
        printf("4. Display Matrices (Allocation, Max, Need)\n");
        printf("5. Display Available\n");
        printf("6. Accept Request for a Process\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                acceptAllocation();
                break;
            case 2:
                acceptMax();
                break;
            case 3:
                acceptAvailable();
                break;
            case 4:
                displayMatrices();
                break;
            case 5:
                displayAvailable();
                break;
            case 6:
                acceptRequest();
                break;
            case 7:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid option! Please try again.\n");
        }
    }

    return 0;
}

// Function to accept Allocation matrix
void acceptAllocation() {
    printf("\nEnter Allocation Matrix (size %d x %d):\n", n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("Enter Allocation[%d][%d]: ", i, j);
            scanf("%d", &Allocation[i][j]);
        }
    }
    findNeed();  // After allocation, calculate the Need matrix
}

// Function to accept Max matrix
void acceptMax() {
    printf("\nEnter Max Matrix (size %d x %d):\n", n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("Enter Max[%d][%d]: ", i, j);
            scanf("%d", &Max[i][j]);
        }
    }
    findNeed();  // After setting Max, calculate the Need matrix
}

// Function to accept Available vector
void acceptAvailable() {
    printf("\nEnter Available Vector (size %d):\n", m);
    for(int i = 0; i < m; i++) {
        printf("Enter Available[%d]: ", i);
        scanf("%d", &Available[i]);
    }
}

// Function to calculate Need matrix
void findNeed() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    // Debugging: Print the Need matrix to check if it is calculated correctly
    printf("\nNeed Matrix (Max - Allocation):\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
}

// Function to display Allocation, Max, and Need matrices
void displayMatrices() {
    printf("\nAllocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", Allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", Max[i][j]);
        }
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
}

// Function to display Available vector
void displayAvailable() {
    printf("\nAvailable Vector:\n");
    for(int i = 0; i < m; i++) {
        printf("%d ", Available[i]);
    }
    printf("\n");
}

// Function to accept a request from a process
void acceptRequest() {
    int proc;
    printf("\nEnter process number to request resources (0 to %d): ", n - 1);
    scanf("%d", &proc);

    // Check if the process number is valid
    if (proc < 0 || proc >= n) {
        printf("Error: Invalid process number.\n");
        return;
    }

    printf("\nEnter the resource request vector for process P%d (size %d):\n", proc, m);
    for (int i = 0; i < m; i++) {
        printf("Enter Request[%d]: ", i);
        scanf("%d", &Request[i]);
    }

    // Call resource request algorithm
    if (resourceRequestAlgorithm(proc)) {
        // If the request is valid, check the system's safety state
        safetyAlgorithm();
    }
}

// Resource-request algorithm for Process Pi
int resourceRequestAlgorithm(int proc) {
    // Check if Request <= Need
    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[proc][i]) {
            printf("Error: Process P%d exceeds its maximum claim.\n", proc);
            return 0; // Request exceeds maximum claim
        }
    }

    // Check if Request <= Available
    for (int i = 0; i < m; i++) {
        if (Request[i] > Available[i]) {
            printf("Process P%d must wait, resources are not available.\n", proc);
            return 0; // Resources are not available
        }
    }

    // Pretend to allocate the resources temporarily
    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];  // Decrease from Available
        Allocation[proc][i] += Request[i];  // Allocate to process
        Need[proc][i] -= Request[i];  // Update Need
    }

    printf("Resources allocated successfully to Process P%d.\n", proc);
    return 1; // Resources allocated successfully
}

// Safety algorithm to check if the system is in a safe state
void safetyAlgorithm() {
    int work[MAX_RESOURCES], finish[MAX_PROCESSES];
    int safeIndex = 0;
    int i, j, k, flag, pno;

    // Initialize work and finish vectors
    for (i = 0; i < m; i++) {
        work[i] = Available[i];
    }
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    while (1) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                // Check if process i can proceed
                flag = 1;
                for (k = 0; k < m; k++) {
                    if (Need[i][k] > work[k]) {
                        flag = 0;
                        break;
                    }
                }

                // If the process can proceed, simulate its completion
                if (flag) {
                    for (k = 0; k < m; k++) {
                        work[k] += Allocation[i][k];
                    }
                    finish[i] = 1;
                    Safe[safeIndex++] = i; // Add to the safe sequence
                    break;
                }
            }
        }

        // If no process can proceed, the system is unsafe
        if (!flag) {
            printf("System is unsafe!\n");
            return;
        }

        // If all processes are finished, the system is in a safe state
        if (safeIndex == n) {
            printf("System is in a safe state.\nSafe sequence is: ");
            for (i = 0; i < n; i++) {
                printf("P%d ", Safe[i]);
            }
            printf("\n");
            return;
        }
    }
}



// Enter number of processes and number of resources: 3 3

// Menu:
// 1. Accept Allocation
// 2. Accept Max
// 3. Accept Available
// 4. Display Matrices (Allocation, Max, Need)
// 5. Display Available
// 6. Accept Request for a Process
// 7. Exit
// Choose an option: 6

// Enter process number to request resources (0 to 2): 2

// Enter the resource request vector for process P2 (size 3):
// Enter Request[0]: 0
// Enter Request[1]: 0
// Enter Request[2]: 0
// Resources allocated successfully to Process P2.
// System is in a safe state.
// Safe sequence is: P0 P1 P2

// Menu:
// 1. Accept Allocation
// 2. Accept Max
// 3. Accept Available
// 4. Display Matrices (Allocation, Max, Need)
// 5. Display Available
// 6. Accept Request for a Process
// 7. Exit
// Choose an option: 7
// Exiting program...