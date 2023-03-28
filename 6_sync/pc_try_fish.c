#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
int count = 0;
int head_dir;
enum HeadDirection
{
    HeadLeft,
    HeadRight,
};

void CountChange()
{
    count = ++count % 4;
}

void t_create(void (*f)(void))
{
    pthread_t tid;
    pthread_create(&tid, NULL, (void *(*)(void *))f, NULL);
}

void Tp()
{
    while (1)
    {
        pthread_mutex_lock(&lk);
        while (!(0 == count))
        {
            pthread_cond_wait(&cv, &lk);
        }
        head_dir = rand() % 2;
        CountChange();
        switch (head_dir)
        {
        case HeadLeft:
            printf("<");
            break;
        default:
            printf(">");
            break;
        }
        pthread_mutex_unlock(&lk);
        pthread_cond_broadcast(&cv);
    }
}
void Tc()
{
    while (1)
    {
        pthread_mutex_lock(&lk);
        while (!(0 != count))
        {
            pthread_cond_wait(&cv, &lk);
        }
        switch (head_dir)
        {
        case HeadLeft:
            printf("><_");
            break;
        default:
            printf("<>_");
            break;
        }
        CountChange();
        CountChange();
        CountChange();
        pthread_mutex_unlock(&lk);
        pthread_cond_broadcast(&cv);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    setbuf(stdout, NULL);

    for (int i = 0; i < 8; ++i)
    {
        t_create(Tp);
        t_create(Tc);
    }

    while (1)
    {
        /* code */
    }
}