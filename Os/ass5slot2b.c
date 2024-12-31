#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define MAX_BLOCKS 1000

// Structure to store the directory information for each file
struct DirectoryEntry {
    char filename[20];
    int index_block;
    int num_blocks;
};

// Global variables
int *bit_vector;  // 0 for free, 1 for allocated
int *index_block; // Index block for storing block numbers
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
    if (num_blocks_to_allocate > num_blocks) {
        printf("Error: Not enough blocks available for allocation.\n");
        return;
    }

    // Allocate index block
    int index_block_num = -1;
    for (int i = 0; i < num_blocks; i++) {
        if (bit_vector[i] == 0) { // Block is free
            index_block_num = i;
            bit_vector[i] = 1;
            break;
        }
    }

    if (index_block_num == -1) {
        printf("Error: Unable to allocate index block.\n");
        return;
    }

    // Allocate data blocks and update index block
    index_block[index_block_num] = -1; // Mark the index block as free
    int *allocated_blocks = (int *)malloc(num_blocks_to_allocate * sizeof(int));
    int num_allocated = 0;
    for (int i = 0; i < num_blocks; i++) {
        if (bit_vector[i] == 0) {
            bit_vector[i] = 1;
            allocated_blocks[num_allocated++] = i;
            if (num_allocated == num_blocks_to_allocate) break;
        }
    }

    // Add to directory
    strcpy(directory[num_files].filename, filename);
    directory[num_files].index_block = index_block_num;
    directory[num_files].num_blocks = num_blocks_to_allocate;

    for (int i = 0; i < num_blocks_to_allocate; i++) {
        index_block[index_block_num] = allocated_blocks[i];
    }

    num_files++;

    printf("File '%s' created successfully with index block %d and %d data blocks.\n", filename, index_block_num, num_blocks_to_allocate);
    free(allocated_blocks);  // Free memory
}

// Function to show the directory
void show_directory() {
    if (num_files == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Directory Entries:\n");
    for (int i = 0; i < num_files; i++) {
        printf("Filename: %s, Index Block: %d, Number of Data Blocks: %d\n", 
                directory[i].filename, directory[i].index_block, directory[i].num_blocks);
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
    int index_block_num = directory[file_index].index_block;
    for (int i = 0; i < directory[file_index].num_blocks; i++) {
        int block_num = index_block[index_block_num];
        bit_vector[block_num] = 0;
        index_block[index_block_num] = -1; // Mark block as free
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

    // Allocate memory for the bit vector and index block array
    bit_vector = (int *)malloc(num_blocks * sizeof(int));
    index_block = (int *)malloc(num_blocks * sizeof(int));

    // Initialize all blocks as free (0)
    for (int i = 0; i < num_blocks; i++) {
        bit_vector[i] = 0;
        index_block[i] = -1;
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
    free(index_block);
    return 0;
}


// Enter the number of blocks on the disk: 12

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 1
// Bit Vector (0=Free, 1=Allocated):
// 0 0 0 0 0 0 0 0 0 0 0 0

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 2
// Enter file name: file2
// Enter number of blocks to allocate: 5
// File 'file2' created successfully with index block 0 and 5 data blocks.

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 1
// Bit Vector (0=Free, 1=Allocated):
// 1 1 1 1 1 1 0 0 0 0 0 0

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 3
// Directory Entries:
// Filename: file2, Index Block: 0, Number of Data Blocks: 5

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 4
// Enter the file name to delete: file2
// File 'file2' deleted successfully.

// Menu:
// 1. Show Bit Vector
// 2. Create New File
// 3. Show Directory
// 4. Delete File
// 5. Exit
// Enter your choice: 5
// Exiting...