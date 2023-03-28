#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5

sem_t forks[N];
sem_t table;
pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;

void getForkId(int person_id, int *left, int *right)
{
    *left = person_id;
    *right = (person_id + 1) % N;
}

void printForkStatus()
{
    pthread_mutex_lock(&lk);
    for (int i = 0; i < N; ++i)
    {
        int val;
        sem_getvalue(&forks[i], &val);
        printf("%d ", 1 - val);
    }
    printf("\n");
    pthread_mutex_unlock(&lk);
}

void *Tp(void *arg)
{
    int id = (int)arg;
    int left, right;
    getForkId(id, &left, &right);
    while (1)
    {
        sem_wait(&table);
        sem_wait(&forks[left]);
        printForkStatus();
        sem_wait(&forks[right]);
        printForkStatus();

        // printf("%d eating\n", id);

        sem_post(&forks[left]);
        sem_post(&forks[right]);
        sem_post(&table);
    }
}

int main()
{
    pthread_t tid;
    for (int i = 0; i < N; ++i)
    {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&table, 0, N - 1);

    for (int i = 0; i < N; ++i)
    {
        pthread_create(&tid, NULL, Tp, (void *)i);
    }

    while (1)
        ;
}