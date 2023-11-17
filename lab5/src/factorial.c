#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

struct Fac {
    int* value;
    int start;
    int end;
};

void* factorial(void *args){
    pthread_mutex_lock( &mutex1 );
    struct Fac *arg = (struct Fac *) args;
    for (int i =arg->start+1;i<=arg->end;i++){
        *(arg->value)=*(arg->value)*i;
    }
    pthread_mutex_unlock( &mutex1 );
}

void *Threadfac(void *args) {
    struct Fac *sum_args = (struct Fac *) args;
    factorial(sum_args);
}

int main(int argc, char **argv) {
    int k = -1;
    int pnum = -1;
    int mod = -1;

    while (true) {
        int current_optind = optind ? optind : 1;

        static struct option options[] = {{"k", required_argument, 0, 0},
                                          {"pnum", required_argument, 0, 0},
                                          {"mod", required_argument, 0, 0},
                                          {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "f", options, &option_index);

        if (c == -1) break;

        switch (c) {
            case 0:
                switch (option_index) {
                    case 0:
                        k = atoi(optarg);
                        if(k<=0)
                        {
                            printf("k must be positive\n");
                            return 1;
                        }

                        break;
                    case 1:
                        pnum = atoi(optarg);
                        if (pnum<=0)
                        {
                            printf("pnum must be positive\n");
                            return 1;
                        }
                        break;
                    case 2:
                        mod = atoi(optarg);
                        if(mod<=0)
                        {
                            printf("mod must be positive\n");
                            return 1;
                        }
                        break;
                    defalut:
                        printf("Index %d is out of options\n", option_index);
                }
                break;
            case '?':
                break;

            default:
                printf("getopt returned character code 0%o?\n", c);
        }
    }

    if (optind < argc) {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (k == -1 || pnum == -1 || mod == -1) {
        printf("Usage: %s --seed \"num\" --array_size \"num\" --threads_num \"num\" \n",
               argv[0]);
        return 1;
    }

 pthread_t threads[pnum];
 struct Fac arg[pnum];
 unsigned int step = k/pnum;
 int z = ((k%pnum)==0)?0:(k%pnum);
 int r = 1;
  for (int i = 0; i < pnum; i++) {
    arg[i].value=&r;
    arg[i].start = step*i;
    arg[i].end=arg[i].start+step;
    if (i == pnum - 1) {
            arg[i].end += z;
            }
        if (pthread_create(&threads[i], NULL, factorial, (void *)(arg+i))) {
            printf("Error: pthread_create failed!\n");
            return 1;
        }
  }
  for (int i = 0; i < pnum; i++) {
    pthread_join(threads[i], NULL);
  }

printf("%d",r);

  return 0;
}