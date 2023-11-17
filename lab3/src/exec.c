#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        execlp("./sequential_min_max", "./sequential_min_max",  "1", "100", NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
        printf("Дочерний процесс: ", getpid());
        sleep(5);
        printf("Дочерний процесс завершен");
    } 
    else if (child_pid>0){
        printf("Родительский процесс: ", getpid());
        sleep(2);
        printf("Родительский процесс завершен");
        wait(NULL); // Ожидание завершения дочернего процесса
        printf("Дочерний процесс завершен");
    }

    return 0;
}