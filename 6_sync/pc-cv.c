#include "../thread_common/thread.h"
#include "../thread_common/thread-sync.h"

int n, count = 0;
mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT();

void Tproduce()
{
    while (1)
    {
        mutex_lock(&lk);
        if (count == n)
        {
            cond_wait(&cv, &lk); // pthread_cond_wait, thread lib function
        }
        if (!(count == n))
        {
            printf("(");
            count++;
            cond_signal(&cv); // pthread_cond_signal
        }
        mutex_unlock(&lk);
    }
}

void Tconsume()
{
    while (1)
    {
        mutex_lock(&lk);
        if (count == 0)
        {
            pthread_cond_wait(&cv, &lk);
        }
        if (!(count == 0))
        {
            printf(")");
            count--;
            cond_signal(&cv);
        }
        mutex_unlock(&lk);
    }
}

int main(int argc, char *argv[])
{
    assert(argc == 2);
    n = atoi(argv[1]);
    setbuf(stdout, NULL);
    for (int i = 0; i < 1; i++)
    {
        create(Tproduce);
        create(Tconsume);
    }
}
