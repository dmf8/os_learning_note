#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
int N, count = 0;

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
        while (N == count) // when awaked, check condition again
        {
            pthread_cond_wait(&cv, &lk);
        }
        count++;
        printf("(");
        pthread_mutex_unlock(&lk);
        pthread_cond_broadcast(&cv); // notice all threads
    }
}
void Tc()
{
    while (1)
    {
        pthread_mutex_lock(&lk);
        while (0 == count)
        {
            pthread_cond_wait(&cv, &lk);
        }
        count--;
        printf(")");
        pthread_mutex_unlock(&lk);
        pthread_cond_broadcast(&cv);
    }
}

int main(int argc, char **argv)
{
    assert(2 == argc);
    N = atoi(argv[1]);

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