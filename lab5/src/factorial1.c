#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/time.h>

#include <pthread.h>

struct FactArgs{
    int begin;
    int end;
    int mod;
};
long long result = 1;

// статически созданный мьютекс
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int Factorial(const struct FactArgs *args)
{
    int fact = 1;
    int i;
    for(i = args->begin; i <= args->end; i++){
        fact *= i;
        fact %= args->mod;
    }

    // блокировка мьютекса
    pthread_mutex_lock(&mutex);
    // подсчет и запись результата (критическая секция)
    result *= fact;
    result %= args->mod;
    // освобождение мьютекса
    pthread_mutex_unlock(&mutex);
    
    return fact;
}

void *ThreadFact(void *args) {
  struct FactArgs *fact_args = (struct FactArgs*)args;
  return (void *)(size_t)Factorial(fact_args);
}

int main(int argc, char **argv) {
    int threads_num = -1;
    int mod = -1;
    int k = -1;
    int current_optind = optind ? optind : 1;
    while(true){
        static struct option options[] = {{"pnum", required_argument, 0, 0},
                                        {"mod", required_argument, 0, 0},
                                        {0, 0, 0, 0}};
                                        
        int option_index = 0;
        int c = getopt_long(argc, argv, "k:", options, &option_index);
    if (c == -1) break;
        switch (c) {
        case 0:
            switch (option_index) {
            case 0:
                threads_num = atoi(optarg);
                break;
            case 1:
                mod = atoi(optarg);
                break;
            default:
                printf("Index %d is out of options\n", option_index);
            }
            break;
        case 'k':
            k = atoi(optarg);
            if(k < 0){
                printf("k must be positive \n");
                return 1;
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

    if (mod == -1 || k == -1 || threads_num == -1) {
        printf("Usage: %s -k \"num\" --pnum \"num\" --mod \"num\" \n",
            argv[0]);
        return 1;
    }

    // массив c несколькими элементами-идентификаторами потоков
    pthread_t threads[threads_num];

    struct FactArgs args[threads_num];
    double block = (double) k / threads_num;

    int i;
    for (i = 0;i < threads_num;i++)
    {
        int begin = (int)(block * i)+1;
        int end = (int)(block * (i + 1));
        args[i].begin = begin;
        args[i].end = end;
        args[i].mod = mod;
    }
    for (i = 0; i < threads_num; i++) {
        if (pthread_create(&threads[i], NULL, ThreadFact, (void *)&args[i])) {
            printf("Error: pthread_create failed!\n");
            return 1;
        }
    }

    for ( i = 0; i < threads_num; i++) {
        int fact = 1;
        pthread_join(threads[i], (void **)&fact);
    }

printf("Rezult= %lld\n", result);
    return 0;

}