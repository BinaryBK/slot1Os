#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Global variables for the matrices and vectors
int Allocation[MAX_PROCESSES][MAX_RESOURCES];
int Max[MAX_PROCESSES][MAX_RESOURCES];
int Need[MAX_PROCESSES][MAX_RESOURCES];
int Available[MAX_RESOURCES];
int n, m;  // n = number of processes, m = number of resources

// Function prototypes
void acceptAllocation();
void acceptMax();
void displayMatrices();
void findNeed();

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
        printf("3. Display Matrices\n");
        printf("4. Exit\n");
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
                displayMatrices();
                break;
            case 4:
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

// Function to calculate Need matrix
void findNeed() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
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


// PS B:\desktopBackup\Coding\Os> ./a.exe
// Enter number of processes and number of resources: 3 3

// Menu:
// 1. Accept Allocation
// 2. Accept Max
// 3. Display Matrices
// 4. Exit
// Choose an option: 1

// Enter Allocation Matrix (size 3 x 3):
// Enter Allocation[0][0]: 0
// Enter Allocation[0][1]: 1
// Enter Allocation[0][2]: 2
// Enter Allocation[1][0]: 3
// Enter Allocation[1][1]: 2
// Enter Allocation[1][2]: 1
// Enter Allocation[2][0]: 2
// Enter Allocation[2][1]: 1
// Enter Allocation[2][2]: 3

// Menu:
// 1. Accept Allocation
// 2. Accept Max
// 3. Display Matrices
// 4. Exit
// Choose an option: 2

// Enter Max Matrix (size 3 x 3):
// Enter Max[0][0]: 7
// Enter Max[0][1]: 5
// Enter Max[0][2]: 3
// Enter Max[1][0]: 3
// Enter Max[1][1]: 2
// Enter Max[1][2]: 2
// Enter Max[2][0]: 9
// Enter Max[2][1]: 0
// Enter Max[2][2]: 2

// Menu:
// 1. Accept Allocation
// 2. Accept Max
// 3. Display Matrices
// 4. Exit
// Choose an option: 3

// Allocation Matrix:
// 0 1 2
// 3 2 1
// 2 1 3

// Max Matrix:
// 7 5 3
// 3 2 2
// 9 0 2

// Need Matrix:
// 7 4 1
// 0 0 1
// 7 -1 -1

// Menu:
// 1. Accept Allocation
// 2. Accept Max
// 3. Display Matrices
// 4. Exit
// Choose an option:       4
// Exiting program...