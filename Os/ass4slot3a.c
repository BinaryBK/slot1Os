#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 16

// Function to simulate MRU Page Replacement Algorithm
void MRU(int page_ref[], int num_pages, int n) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  // Memory frames
    int last_used[MAX_FRAMES] = {0}; // To track the last used page index
    int page_faults = 0;
    int i, j;

    printf("\nMRU Page Replacement Algorithm:\n");

    for (i = 0; i < num_pages; i++) {
        int page = page_ref[i];
        int found = 0;

        // Check if the page is already in memory (no page fault)
        for (j = 0; j < n; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {  // Page Fault
            int most_recent = -1;
            int replace_index = -1;

            // Find the page that was accessed most recently
            for (j = 0; j < n; j++) {
                if (last_used[j] > most_recent) {
                    most_recent = last_used[j];
                    replace_index = j;
                }
            }

            // Replace the selected page with the new page
            frames[replace_index] = page;
            page_faults++;

            // Update the last used timestamp for the replaced page
            last_used[replace_index] = i;

            printf("Accessing page %d: Page Fault!\n", page);
            printf("Memory Frames: ");
            for (j = 0; j < n; j++) {
                if (frames[j] != -1) {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }
    printf("Total Page Faults (MRU): %d\n", page_faults);
}

// Function to simulate Second Chance Page Replacement Algorithm
void SecondChance(int page_ref[], int num_pages, int n) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  // Memory frames
    int reference_bit[MAX_FRAMES] = {0};    // Reference bits for each page
    int page_faults = 0;
    int i, j;
    int pointer = 0;  // Pointer to track the page in a circular manner

    printf("\nSecond Chance Page Replacement Algorithm:\n");

    for (i = 0; i < num_pages; i++) {
        int page = page_ref[i];
        int found = 0;

        // Check if the page is already in memory (no page fault)
        for (j = 0; j < n; j++) {
            if (frames[j] == page) {
                found = 1;
                reference_bit[j] = 1;  // Set reference bit to 1
                break;
            }
        }

        if (!found) {  // Page Fault
            // Find an empty slot in memory or use second chance replacement
            while (1) {
                if (frames[pointer] == -1) {  // Find an empty slot
                    frames[pointer] = page;
                    reference_bit[pointer] = 1;
                    break;
                } else if (reference_bit[pointer] == 0) {  // Replace if reference bit is 0
                    frames[pointer] = page;
                    reference_bit[pointer] = 1;
                    break;
                } else {  // Give second chance and reset reference bit
                    reference_bit[pointer] = 0;
                }
                pointer = (pointer + 1) % n;  // Move pointer in a circular manner
            }
            page_faults++;
            printf("Accessing page %d: Page Fault!\n", page);
            printf("Memory Frames: ");
            for (j = 0; j < n; j++) {
                if (frames[j] != -1) {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }
    printf("Total Page Faults (Second Chance): %d\n", page_faults);
}

int main() {
    int page_ref[MAX_PAGES] = {2, 5, 2, 8, 5, 4, 1, 2, 3, 2, 6, 1, 2, 5, 9, 8};
    int num_pages = 16; // Number of pages in reference string
    int n;

    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    // Call the algorithms
    MRU(page_ref, num_pages, n);
    SecondChance(page_ref, num_pages, n);

    return 0;
}




// Enter the number of memory frames: 3

// MRU Page Replacement Algorithm:
// Accessing page 2: Page Fault!
// Memory Frames: 2 
// Accessing page 5: Page Fault!
// Memory Frames: 5 
// Accessing page 2: Page Fault!
// Memory Frames: 2 
// Accessing page 8: Page Fault!
// Memory Frames: 8
// Accessing page 5: Page Fault!
// Memory Frames: 5
// Accessing page 4: Page Fault!
// Memory Frames: 4
// Accessing page 1: Page Fault!
// Memory Frames: 1
// Accessing page 2: Page Fault!
// Memory Frames: 2
// Accessing page 3: Page Fault!
// Memory Frames: 3
// Accessing page 2: Page Fault!
// Memory Frames: 2
// Accessing page 6: Page Fault!
// Memory Frames: 6
// Accessing page 1: Page Fault!
// Memory Frames: 1
// Accessing page 2: Page Fault!
// Memory Frames: 2
// Accessing page 5: Page Fault!
// Memory Frames: 5
// Accessing page 9: Page Fault!
// Memory Frames: 9
// Accessing page 8: Page Fault!
// Memory Frames: 8
// Total Page Faults (MRU): 16

// Second Chance Page Replacement Algorithm:
// Accessing page 2: Page Fault!
// Memory Frames: 2
// Accessing page 5: Page Fault!
// Memory Frames: 2 5
// Accessing page 8: Page Fault!
// Memory Frames: 2 5 8
// Accessing page 4: Page Fault!
// Memory Frames: 2 5 4
// Accessing page 1: Page Fault!
// Memory Frames: 1 5 4
// Accessing page 2: Page Fault!
// Memory Frames: 1 2 4
// Accessing page 3: Page Fault!
// Memory Frames: 1 2 3 
// Accessing page 6: Page Fault!
// Memory Frames: 6 2 3
// Accessing page 1: Page Fault!
// Memory Frames: 6 2 1
// Accessing page 5: Page Fault!
// Memory Frames: 5 2 1
// Accessing page 9: Page Fault!
// Memory Frames: 5 2 9
// Accessing page 8: Page Fault!
// Memory Frames: 8 2 9
// Total Page Faults (Second Chance): 12