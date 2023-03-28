#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem;

void *Ta(void *arg)
{
    sleep(2);
    printf("ta finishes\n");
    sem_post(&sem);
}
void *Tb(void *arg)
{
    sem_wait(&sem);
    printf("tb starts\n");
}

int main()
{
    sem_init(&sem, 0, 0);

    pthread_t tid;
    pthread_create(&tid, NULL, Ta, NULL);
    pthread_create(&tid, NULL, Tb, NULL);

    while (1)
        ;
}