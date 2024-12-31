#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function to find the next occurrence of a page in the reference string after a given index
int find_next(int page_ref[], int current_pos, int num_pages, int page) {
    for (int i = current_pos + 1; i < num_pages; i++) {
        if (page_ref[i] == page) {
            return i;
        }
    }
    return -1;  // -1 indicates that the page doesn't appear again
}

// OPT (Optimal) Page Replacement Algorithm
void OPT(int page_ref[], int num_pages, int n) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  // Memory frames
    int page_faults = 0;
    int i, j;

    printf("\nOPT Page Replacement Algorithm:\n");

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
            // Find a free slot in memory
            int free_slot = -1;
            for (j = 0; j < n; j++) {
                if (frames[j] == -1) {
                    free_slot = j;
                    break;
                }
            }

            if (free_slot == -1) {  // No free slot, need to replace a page
                int farthest = -1;
                int replace_index = -1;

                // Find the page to replace (page that is used farthest in the future)
                for (j = 0; j < n; j++) {
                    int next_use = find_next(page_ref, i, num_pages, frames[j]);
                    if (next_use == -1) {
                        replace_index = j;
                        break;
                    } else {
                        if (next_use > farthest) {
                            farthest = next_use;
                            replace_index = j;
                        }
                    }
                }

                // Replace the selected page
                frames[replace_index] = page;
            } else {
                // Insert the page into the free slot
                frames[free_slot] = page;
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
    printf("Total Page Faults (OPT): %d\n", page_faults);
}


// MFU (Most Frequently Used) Page Replacement Algorithm
void MFU(int page_ref[], int num_pages, int n) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  // Memory frames
    int frequency[MAX_FRAMES] = {0};         // Frequency count for pages in memory
    int page_faults = 0;
    int i, j;

    printf("\nMFU Page Replacement Algorithm:\n");

    for (i = 0; i < num_pages; i++) {
        int page = page_ref[i];
        int found = 0;

        // Check if the page is already in memory (no page fault)
        for (j = 0; j < n; j++) {
            if (frames[j] == page) {
                found = 1;
                frequency[j]++;
                break;
            }
        }

        if (!found) {  // Page Fault
            // Find a free slot in memory
            int free_slot = -1;
            for (j = 0; j < n; j++) {
                if (frames[j] == -1) {
                    free_slot = j;
                    break;
                }
            }

            if (free_slot == -1) {  // No free slot, need to replace a page
                int max_freq = -1;
                int replace_index = -1;

                // Find the page with the highest frequency to replace
                for (j = 0; j < n; j++) {
                    if (frequency[j] > max_freq) {
                        max_freq = frequency[j];
                        replace_index = j;
                    }
                }

                // Replace the selected page
                frames[replace_index] = page;
                frequency[replace_index] = 1;
            } else {
                // Insert the page into the free slot
                frames[free_slot] = page;
                frequency[free_slot] = 1;
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
    printf("Total Page Faults (MFU): %d\n", page_faults);
}

// LFU (Least Frequently Used) Page Replacement Algorithm
void LFU(int page_ref[], int num_pages, int n) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  // Memory frames
    int frequency[MAX_FRAMES] = {0};         // Frequency count for pages in memory
    int page_faults = 0;
    int i, j;

    printf("\nLFU Page Replacement Algorithm:\n");

    for (i = 0; i < num_pages; i++) {
        int page = page_ref[i];
        int found = 0;

        // Check if the page is already in memory (no page fault)
        for (j = 0; j < n; j++) {
            if (frames[j] == page) {
                found = 1;
                frequency[j]++;
                break;
            }
        }

        if (!found) {  // Page Fault
            // Find a free slot in memory
            int free_slot = -1;
            for (j = 0; j < n; j++) {
                if (frames[j] == -1) {
                    free_slot = j;
                    break;
                }
            }

            if (free_slot == -1) {  // No free slot, need to replace a page
                int min_freq = 9999;
                int replace_index = -1;

                // Find the page with the lowest frequency to replace
                for (j = 0; j < n; j++) {
                    if (frequency[j] < min_freq) {
                        min_freq = frequency[j];
                        replace_index = j;
                    }
                }

                // Replace the selected page
                frames[replace_index] = page;
                frequency[replace_index] = 1;
            } else {
                // Insert the page into the free slot
                frames[free_slot] = page;
                frequency[free_slot] = 1;
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
    printf("Total Page Faults (LFU): %d\n", page_faults);
}

int main() {
    int page_ref[MAX_PAGES] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int num_pages = 16; // Number of pages in reference string
    int n;

    printf("Enter the number of memory frames: ");
    scanf("%d", &n);

    // Call the algorithms
    OPT(page_ref, num_pages, n);
    MFU(page_ref, num_pages, n);
    LFU(page_ref, num_pages, n);

    return 0;
}


// Enter the number of memory frames: 3

// OPT Page Replacement Algorithm:
// Accessing page 12: Page Fault!
// Memory Frames: 12 
// Accessing page 15: Page Fault!
// Memory Frames: 12 15 
// Accessing page 18: Page Fault!
// Memory Frames: 12 15 18 
// Accessing page 6: Page Fault!
// Memory Frames: 12 15 6
// Accessing page 8: Page Fault!
// Memory Frames: 12 8 6
// Accessing page 11: Page Fault!
// Memory Frames: 12 11 6
// Accessing page 19: Page Fault!
// Memory Frames: 12 19 6
// Accessing page 8: Page Fault!
// Memory Frames: 12 19 8
// Accessing page 15: Page Fault!
// Memory Frames: 15 19 8
// Total Page Faults (OPT): 9

// MFU Page Replacement Algorithm:
// Accessing page 12: Page Fault!
// Memory Frames: 12
// Accessing page 15: Page Fault!
// Memory Frames: 12 15
// Accessing page 18: Page Fault!
// Memory Frames: 12 15 18
// Accessing page 6: Page Fault!
// Memory Frames: 6 15 18 
// Accessing page 8: Page Fault!
// Memory Frames: 8 15 18
// Accessing page 11: Page Fault!
// Memory Frames: 11 15 18
// Accessing page 12: Page Fault!
// Memory Frames: 12 15 18
// Accessing page 19: Page Fault!
// Memory Frames: 19 15 18
// Accessing page 12: Page Fault!
// Memory Frames: 12 15 18
// Accessing page 6: Page Fault!
// Memory Frames: 6 15 18
// Accessing page 8: Page Fault!
// Memory Frames: 8 15 18
// Accessing page 12: Page Fault!
// Memory Frames: 12 15 18
// Accessing page 19: Page Fault!
// Memory Frames: 12 19 18
// Accessing page 8: Page Fault!
// Memory Frames: 8 19 18
// Total Page Faults (MFU): 14

// LFU Page Replacement Algorithm:
// Accessing page 12: Page Fault!
// Memory Frames: 12
// Accessing page 15: Page Fault!
// Memory Frames: 12 15
// Accessing page 18: Page Fault!
// Memory Frames: 12 15 18 
// Accessing page 6: Page Fault!
// Memory Frames: 12 6 18
// Accessing page 8: Page Fault!
// Memory Frames: 12 8 18
// Accessing page 11: Page Fault!
// Memory Frames: 12 11 18
// Accessing page 19: Page Fault!
// Memory Frames: 12 19 18
// Accessing page 6: Page Fault!
// Memory Frames: 12 6 18
// Accessing page 8: Page Fault!
// Memory Frames: 12 8 18
// Accessing page 15: Page Fault!
// Memory Frames: 12 15 18
// Accessing page 19: Page Fault!
// Memory Frames: 12 19 18
// Accessing page 8: Page Fault!
// Memory Frames: 12 8 18
// Total Page Faults (LFU): 12