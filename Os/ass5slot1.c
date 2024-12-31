#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Include this header for malloc and free

#define MAX_FILES 100

// Structure to store the directory information for each file
struct DirectoryEntry {
    char filename[20];
    int start_block;
    int num_blocks;
};

// Global variables for bit vector and directory
int *bit_vector; // 0 for free, 1 for allocated
struct DirectoryEntry directory[MAX_FILES];
int num_blocks, num_files = 0;

// Function to show the bit vector
void show_bit_vector() {
    printf("Bit Vector (0=Free, 1=Allocated):\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%d ", bit_vector[i]);
    }
    printf("\n");
}

// Function to create a new file
void create_new_file() {
    char filename[20];
    int num_blocks_to_allocate;

    printf("Enter file name: ");
    scanf("%s", filename);
    printf("Enter number of blocks to allocate: ");
    scanf("%d", &num_blocks_to_allocate);

    // Check if there are enough free blocks for allocation
    int start_block = -1;
    for (int i = 0; i <= num_blocks - num_blocks_to_allocate; i++) {
        int found = 1;
        for (int j = 0; j < num_blocks_to_allocate; j++) {
            if (bit_vector[i + j] == 1) {
                found = 0;
                break;
            }
        }
        if (found) {
            start_block = i;
            break;
        }
    }

    if (start_block == -1) {
        printf("Error: Not enough contiguous free blocks available.\n");
        return;
    }

    // Allocate blocks
    for (int i = 0; i < num_blocks_to_allocate; i++) {
        bit_vector[start_block + i] = 1;
    }

    // Add to directory
    strcpy(directory[num_files].filename, filename);
    directory[num_files].start_block = start_block;
    directory[num_files].num_blocks = num_blocks_to_allocate;
    num_files++;

    printf("File '%s' created at block %d with %d blocks.\n", filename, start_block, num_blocks_to_allocate);
}

// Function to show the directory
void show_directory() {
    if (num_files == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Directory Entries:\n");
    for (int i = 0; i < num_files; i++) {
        printf("Filename: %s, Start Block: %d, Number of Blocks: %d\n", 
                directory[i].filename, directory[i].start_block, directory[i].num_blocks);
    }
}

// Function to delete a file
void delete_file() {
    char filename[20];
    printf("Enter the file name to delete: ");
    scanf("%s", filename);

    // Search for the file in the directory
    int file_index = -1;
    for (int i = 0; i < num_files; i++) {
        if (strcmp(directory[i].filename, filename) == 0) {
            file_index = i;
            break;
        }
    }

    if (file_index == -1) {
        printf("File not found.\n");
        return;
    }

    // Free the allocated blocks for this file
    for (int i = 0; i < directory[file_index].num_blocks; i++) {
        bit_vector[directory[file_index].start_block + i] = 0;
    }

    // Remove the file from the directory
    for (int i = file_index; i < num_files - 1; i++) {
        directory[i] = directory[i + 1];
    }
    num_files--;

    printf("File '%s' deleted successfully.\n", filename);
}

int main() {
    int option;

    // Input the number of blocks on the disk
    printf("Enter the number of blocks on the disk: ");
    scanf("%d", &num_blocks);

    // Allocate memory for the bit vector
    bit_vector = (int *)malloc(num_blocks * sizeof(int));

    // Initialize all blocks as free (0)
    for (int i = 0; i < num_blocks; i++) {
        bit_vector[i] = 0;
    }

    do {
        // Display the menu
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                show_bit_vector();
                break;
            case 2:
                create_new_file();
                break;
            case 3:
                show_directory();
                break;
            case 4:
                delete_file();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 5);

    // Free allocated memory
    free(bit_vector);
    return 0;
}




// Enter the number of blocks on the disk: 10

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 1
// Bit Vector (0=Free, 1=Allocated):
// 0 0 0 0 0 0 0 0 0 0

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 2
// Enter file name: file1
// Enter number of blocks to allocate: 3
// File 'file1' created at block 0 with 3 blocks.

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 1
// Bit Vector (0=Free, 1=Allocated):
// 1 1 1 0 0 0 0 0 0 0

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 3
// Directory Entries:
// Filename: file1, Start Block: 0, Number of Blocks: 3

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 4
// Enter the file name to delete: file1
// File 'file1' deleted successfully.

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 5
// Exiting...