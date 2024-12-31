#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

// Function to check if a page is in the memory
int is_page_in_memory(int page, int frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return 1; // Page is in memory
        }
    }
    return 0; // Page is not in memory
}

// FIFO Page Replacement Algorithm
void fifo_page_replacement(int reference_string[], int num_references, int num_frames) {
    int frames[num_frames];
    int page_faults = 0;
    int next_frame = 0;

    // Initialize all frames with -1 to represent empty frames
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("\nFIFO Page Replacement Algorithm:\n");
    for (int i = 0; i < num_references; i++) {
        int page = reference_string[i];
        printf("Accessing page %d: ", page);
        
        // If page is not in memory, replace the oldest page
        if (!is_page_in_memory(page, frames, num_frames)) {
            frames[next_frame] = page;
            next_frame = (next_frame + 1) % num_frames;
            page_faults++;
            printf("Page Fault!\n");
        } else {
            printf("No Page Fault.\n");
        }

        // Print the current state of memory frames
        printf("Memory Frames: ");
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", page_faults);
}

// LRU Page Replacement Algorithm
void lru_page_replacement(int reference_string[], int num_references, int num_frames) {
    int frames[num_frames];
    int page_faults = 0;
    int last_used[num_frames]; // Array to store last used time for LRU
    int current_time = 0;      // To simulate time

    // Initialize all frames with -1 to represent empty frames
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1; // Initially, all frames have not been used
    }

    printf("\nLRU Page Replacement Algorithm:\n");
    for (int i = 0; i < num_references; i++) {
        int page = reference_string[i];
        printf("Accessing page %d: ", page);

        // If page is not in memory, replace the least recently used page
        if (!is_page_in_memory(page, frames, num_frames)) {
            // Find the least recently used page
            int lru_page = -1, lru_time = current_time;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1 || last_used[j] < lru_time) {
                    lru_page = j;
                    lru_time = last_used[j];
                }
            }
            frames[lru_page] = page;
            page_faults++;
            printf("Page Fault!\n");
        } else {
            printf("No Page Fault.\n");
        }

        // Update the last used time for the current page
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                last_used[j] = current_time;
                break;
            }
        }

        // Increment the time (simulate time passing)
        current_time++;

        // Print the current state of memory frames
        printf("Memory Frames: ");
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", page_faults);
}

int main() {
    // Given reference string
    int reference_string[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int num_references = sizeof(reference_string) / sizeof(reference_string[0]);

    int num_frames;
    printf("Enter the number of memory frames: ");
    scanf("%d", &num_frames);

    // Run FIFO page replacement
    fifo_page_replacement(reference_string, num_references, num_frames);

    // Run LRU page replacement
    lru_page_replacement(reference_string, num_references, num_frames);

    return 0;
}



// PS B:\desktopBackup\Coding\Os> gcc ass4slot1.c
// PS B:\desktopBackup\Coding\Os> ./a.exe
// Enter the number of memory frames: 3

// FIFO Page Replacement Algorithm:
// Accessing page 12: Page Fault!
// Memory Frames: 12 
// Accessing page 15: Page Fault!
// Memory Frames: 12 15 
// Accessing page 12: No Page Fault.
// Memory Frames: 12 15 
// Accessing page 18: Page Fault!
// Memory Frames: 12 15 18
// Accessing page 6: Page Fault!
// Memory Frames: 6 15 18
// Accessing page 8: Page Fault!
// Memory Frames: 6 8 18
// Accessing page 11: Page Fault!
// Memory Frames: 6 8 11
// Accessing page 12: Page Fault!
// Memory Frames: 12 8 11
// Accessing page 19: Page Fault!
// Memory Frames: 12 19 11
// Accessing page 12: No Page Fault.
// Memory Frames: 12 19 11
// Accessing page 6: Page Fault!
// Memory Frames: 12 19 6
// Accessing page 8: Page Fault!
// Memory Frames: 8 19 6
// Accessing page 12: Page Fault!
// Memory Frames: 8 12 6
// Accessing page 15: Page Fault!
// Memory Frames: 8 12 15
// Accessing page 19: Page Fault!
// Memory Frames: 19 12 15
// Accessing page 8: Page Fault!
// Memory Frames: 19 8 15
// Total Page Faults (FIFO): 14

// LRU Page Replacement Algorithm:
// Accessing page 12: Page Fault!
// Memory Frames: 12
// Accessing page 15: Page Fault!
// Memory Frames: 15 12
// Accessing page 12: No Page Fault.
// Memory Frames: 15 12
// Accessing page 18: Page Fault!
// Memory Frames: 18 15 12 
// Accessing page 6: Page Fault!
// Memory Frames: 18 6 12
// Accessing page 8: Page Fault!
// Memory Frames: 18 6 8
// Accessing page 11: Page Fault!
// Memory Frames: 11 6 8
// Accessing page 12: Page Fault!
// Memory Frames: 11 12 8
// Accessing page 19: Page Fault!
// Memory Frames: 11 12 19
// Accessing page 12: No Page Fault.
// Memory Frames: 11 12 19
// Accessing page 6: Page Fault!
// Memory Frames: 6 12 19
// Accessing page 8: Page Fault!
// Memory Frames: 6 12 8
// Accessing page 12: No Page Fault.
// Memory Frames: 6 12 8 
// Accessing page 15: Page Fault!
// Memory Frames: 15 12 8
// Accessing page 19: Page Fault!
// Memory Frames: 15 12 19
// Accessing page 8: Page Fault!
// Memory Frames: 15 8 19
// Total Page Faults (LRU): 13
// PS B:\desktopBackup\Coding\Os>