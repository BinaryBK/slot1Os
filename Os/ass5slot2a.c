#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define MAX_BLOCKS 1000

// Structure to store the directory information for each file
struct DirectoryEntry {
    char filename[20];
    int start_block;
    int end_block;
};

// Linked List Node for the file allocation
struct BlockNode {
    int block_number;
    struct BlockNode* next;
};

// Global variables
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
    int prev_block = -1;
    struct BlockNode* file_head = NULL;
    struct BlockNode* current_node = NULL;

    for (int i = 0; i < num_blocks; i++) {
        if (bit_vector[i] == 0) { // Block is free
            if (start_block == -1) {
                start_block = i; // First free block
            }
            bit_vector[i] = 1;

            // Allocate the block in the linked list
            struct BlockNode* new_node = (struct BlockNode*)malloc(sizeof(struct BlockNode));
            new_node->block_number = i;
            new_node->next = NULL;

            if (current_node == NULL) {
                file_head = new_node;
                current_node = file_head;
            } else {
                current_node->next = new_node;
                current_node = new_node;
            }

            num_blocks_to_allocate--;
        }

        if (num_blocks_to_allocate == 0) {
            break;
        }
    }

    if (num_blocks_to_allocate > 0) {
        printf("Error: Not enough free blocks available.\n");
        return;
    }

    // Add to directory
    directory[num_files].start_block = start_block;
    directory[num_files].end_block = current_node->block_number;
    strcpy(directory[num_files].filename, filename);
    num_files++;

    printf("File '%s' created successfully with blocks linked from block %d to block %d.\n", filename, start_block, current_node->block_number);
}

// Function to show the directory
void show_directory() {
    if (num_files == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Directory Entries:\n");
    for (int i = 0; i < num_files; i++) {
        printf("Filename: %s, Start Block: %d, End Block: %d\n", 
                directory[i].filename, directory[i].start_block, directory[i].end_block);
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
    struct BlockNode* current_node = NULL;
    for (int i = directory[file_index].start_block; i <= directory[file_index].end_block; i++) {
        bit_vector[i] = 0;  // Mark the block as free
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
// Enter number of blocks to allocate: 4
// File 'file1' created successfully with blocks linked from block 0 to block 3.

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 1
// Bit Vector (0=Free, 1=Allocated):
// 1 1 1 1 0 0 0 0 0 0

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 3
// Directory Entries:
// Filename: file1, Start Block: 0, End Block: 3

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