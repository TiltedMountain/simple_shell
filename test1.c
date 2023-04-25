#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

void prompt() {
    printf("input> ");
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    int status;

    while (1) {
        prompt();
        if (!fgets(input, MAX_INPUT_LENGTH, stdin)) {
            break;
        }
        input[strlen(input) - 1] = '\0';

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] != NULL) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(1);
            } else if (pid == 0) {
                if (execvp(args[0], args) == -1) {
                    perror("execvp failed");
                    exit(1);
                }
            } else {
                if (waitpid(pid, &status, 0) == -1) {
                    perror("waitpid failed");
                    exit(1);
                }
            }
        }
    }

    printf("\n");
    return 0;
}
