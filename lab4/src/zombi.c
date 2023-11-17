#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        printf("Дочерний процесс");
        sleep(5);
        printf("\nДочерний процесс завершен!");
    } 
    else if (child_pid>0){
        printf("\nРодительский процесс");
        sleep(5);
        printf("\nРодительский процесс завершен");
        wait(NULL); // Ожидание завершения дочернего процесса
        printf("Дочерний процесс завершен");
    }

    return 0;
}