#include <pthread.h>
#include <stdio.h>

#define N 5

int forks[N] = {0};

pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void getForkId(int person_id, int *left, int *right)
{
    *left = person_id;
    *right = (person_id + 1) % N;
}

void printForkStatus()
{
    for (int i = 0; i < N; ++i)
        printf("%d ", forks[i]);
    printf("\n");
}

void *Tp(void *arg)
{
    int id = (int)arg;
    int left, right;
    getForkId(id, &left, &right);
    while (1)
    {
        pthread_mutex_lock(&lk);
        while (!(!forks[left] && !forks[right]))
        {
            pthread_cond_wait(&cv, &lk);
        }
        forks[left] = forks[right] = 1; // begin to eat
        // fork status
        printForkStatus();
        pthread_mutex_unlock(&lk);
        // usleep(10000); // eat time

        pthread_mutex_lock(&lk);
        forks[left] = forks[right] = 0; // end to eat
        pthread_mutex_unlock(&lk);

        pthread_cond_broadcast(&cv);
    }
}

int main()
{
    pthread_t tid;
    for (int i = 0; i < N; ++i)
    {
        pthread_create(&tid, NULL, Tp, (void *)i);
    }

    while (1)
        ;
}