#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void prompt() {
    printf("Please Input something> ");
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[2];

    while (1) {
        prompt();
        if (!fgets(input, MAX_INPUT_LENGTH, stdin)) {
            break;
        }
        input[strlen(input) - 1] = '\0';
        args[0] = input;
        args[1] = NULL;

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
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid failed");
                exit(1);
            }
        }
    }

    printf("\n");
    return 0;
}
