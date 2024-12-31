#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to count lines, words, or characters in a file
void count_file(const char *file, const char *option) {
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    int lines = 0, words = 0, chars = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') {
            lines++;
        }
        if (ch == ' ' || ch == '\n') {
            words++;
        }
    }

    if (strcmp(option, "l") == 0) {
        printf("Lines: %d\n", lines);
    } else if (strcmp(option, "w") == 0) {
        printf("Words: %d\n", words);
    } else if (strcmp(option, "c") == 0) {
        printf("Characters: %d\n", chars);
    }

    fclose(fp);
}

// Function to execute the command
void execute_command(char *command) {
    char *args[10];
    char *token = strtok(command, " ");
    int i = 0;

    // Tokenize the command
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    // Handle the 'count' command
    if (strcmp(args[0], "count") == 0) {
        if (i < 3) {
            printf("Usage: count <option> <filename>\n");
            return;
        }
        count_file(args[2], args[1]);
    } else {
        // Create child process to execute external commands
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);  // If execvp fails
        } else if (pid > 0) {
            // Parent process waits for child to finish
            waitpid(pid, NULL, 0);
        } else {
            perror("Fork failed");
        }
    }
}

int main() {
    char command[100];

    while (1) {
        // Display the shell prompt
        printf("myshell$ ");
        fflush(stdout);

        // Read the command input
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        // Remove newline character from input
        command[strcspn(command, "\n")] = 0;

        // Exit the shell if the command is "q"
        if (strcmp(command, "q") == 0) {
            break;
        }

        // Execute the command
        execute_command(command);
    }

    return 0;
}
