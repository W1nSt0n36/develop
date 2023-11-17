#include <getopt.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char flags[7] = "\0"; // массив флагов
  int index_end_flags = 1;
  flags_parser(flags, argc, argv, &index_end_flags);
  return 0;
}

void flags_parser(char *flags, int argc, char **argv, int *index) {
  // пройдемся по всем аргументам, кроме 1
  for (int i = 1; i < argc; i++) {
    
    // если аргумент начинается не на '-' 
    // или является строкой "-" или "--" ("--" сигнал что опции кончились)
    // считаем что флаги опций кончились, и начались имена файлов
    if (argv[i][0] != '-' || strcmp(argv[i], "--") == 0 ||
      strcmp(argv[i], "-") == 0 ) {
      break;                                                                                  
    } else {
      *index = i;
      // флаги могут быть написаны слитно, например: -bE
      // поэтому проходимся по каждому символу аргумента кроме 1
      for (size_t j = 1; j < strlen(argv[i]); j++) {
        append_flags(flags, argv[i][j]);
      }
    }  
  }
}

struct s_avi_flags {
  char flag;              // флаг
  char *equivalent_flags; // эквивалентные простые флаги
};

void append_flags(char *flags, char flag) {
  // доступные флаги
  int err_code = 1;
  struct s_avi_flags avi_flags[8] = {{'b', "b"}, {'E', "E"}, {'e', "Ev"},
                                     {'n', "n"}, {'s', "s"}, {'T', "T"},
                                     {'t', "Tv"}, {'v', "v"}};

  for (int i = 0; i < 8; i++) {
    if (avi_flags[i].flag == flag) {
      for (size_t j = 0; j < strlen(avi_flags[i].equivalent_flags); j++) {
        append_flag(flags, avi_flags[i].equivalent_flags[j]);
      }
      err_code = 0;
      break;
    }
  }
}

// добавить 1 флаг в массив флагов
void append_flag(char *flags, char flag) {

  if (strchr(flags, flag) == NULL) { // если такого флага нет
    char temp[2] = "-";   // создаем временную строку
    temp[0] = flag;       // например ['v', '\0']
    strcat(flags, temp);  // объеденяем её со строкой флагов
  }
}

