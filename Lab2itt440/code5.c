#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childTask(int child_num) {
    char name[100];
    printf("[Child %d - PID %d] Enter your name: ", child_num, getpid());
    scanf("%99s", name);
    printf("[Child %d - PID %d] Your name is: %s\n\n", child_num, getpid(), name);
}

int main(void) {
    int total_children = 4;

    for (int i = 1; i <= total_children; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            childTask(i);
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent waits for the child process to finish before spawning next child
            wait(NULL);
        }
    }

    printf("Job is done\n");
    return EXIT_SUCCESS;
}
