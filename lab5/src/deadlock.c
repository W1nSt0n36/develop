#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* operation1(void* arg) {
    pthread_mutex_lock(&mutex1);    // Блокируем mutex1
    printf("Выполняется операция 1\n");
    pthread_mutex_lock(&mutex2);    // Пытаемся заблокировать mutex2
    printf("Операция 1 завершена\n");
    pthread_mutex_unlock(&mutex2);    // Разблокируем mutex2
    pthread_mutex_unlock(&mutex1);    // Разблокируем mutex1
    return NULL;
}

void* operation2(void* arg) {
    pthread_mutex_lock(&mutex2);    // Блокируем mutex2
    printf("Выполняется операция 2\n");
    pthread_mutex_lock(&mutex1);    // Пытаемся заблокировать mutex1
    printf("Операция 2 завершена\n");
    pthread_mutex_unlock(&mutex1);    // Разблокируем mutex1
    pthread_mutex_unlock(&mutex2); // Разблокируем mutex2
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex1, NULL);    // Инициализируем мьютексы
    pthread_mutex_init(&mutex2, NULL);
    pthread_t thread1, thread2;    // Создаем потоки
    pthread_create(&thread1, NULL, operation1, NULL);
    pthread_create(&thread2, NULL, operation2, NULL);
    pthread_join(thread1, NULL);    // Ожидаем завершения потоков
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex1);    // Уничтожаем мьютексы
    pthread_mutex_destroy(&mutex2);
    
    return 0;
}