#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
  pid_t chld_pid;
  chld_pid = fork();
  if (chld_pid > 0) //родитель
  {
    printf("Родитель\n");
    sleep(10);
    printf("Родительская программа завершена\n");
  }
  else //потомок
  {
    printf("Дочерняя программа завершена\n");
    exit(0);
  }
  return 0;
}