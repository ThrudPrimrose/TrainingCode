#include "CMutex.h"

#include <stdio.h>
#include <assert.h>

static const int limit = 100000;

struct argument_struct
{
    int *increment;
    int *acquisitons;
    struct CMutex *mutex;
};

void *work(void *ptr)
{
    pthread_detach(pthread_self());

    struct argument_struct *arg_struct = (struct argument_struct *)(ptr);
    while (*(arg_struct->increment) < limit)
    {
        bool acquired = acquire(arg_struct->mutex);
        if (*(arg_struct->increment) < limit)
        {
            (*(arg_struct->increment))++;
            (*(arg_struct->acquisitons))++;
        }
        bool released = release(arg_struct->mutex);
        assert(!acquired || (acquired && released));
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2;
    struct CMutex *cmutex = Init_CMutex();
    int increment = 0;
    int acquisitions_by_thread1 = 0;
    int acquisitions_by_thread2 = 0;
    int iret1 = 0;
    int iret2 = 0;
    struct argument_struct arg_struct1 = {&increment, &acquisitions_by_thread1, cmutex};
    struct argument_struct arg_struct2 = {&increment, &acquisitions_by_thread2, cmutex};

    iret1 = pthread_create(&thread1, NULL, work, (void *)(&arg_struct1));
    iret2 = pthread_create(&thread2, NULL, work, (void *)(&arg_struct2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if (acquisitions_by_thread1 > acquisitions_by_thread2)
    {
        printf("C style, reached %d: Thread 1 wins with %d to %d.\n", increment, acquisitions_by_thread1, acquisitions_by_thread2);
    }
    else if (acquisitions_by_thread1 < acquisitions_by_thread2)
    {
        printf("C style, reached %d: Thread 2 wins with %d to %d.\n", increment, acquisitions_by_thread1, acquisitions_by_thread2);
    }
    else
    {
        printf("C style, reached %d: It is a stalemate\n", increment);
    }

    return 0;
}