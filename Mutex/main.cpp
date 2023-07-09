#include "Mutex.h"

#include <iostream>
#include <cassert>

constexpr int limit = 100000;

struct argument_struct {
    int* increment;
    int* acquisitons;
    Mutex* mutex;
};

void *work(void* ptr){
    pthread_detach(pthread_self());

    argument_struct* arg_struct = static_cast<argument_struct*>(ptr);
    while (*(arg_struct->increment) < limit) {
        bool acquired = arg_struct->mutex->acquire();
        if (*(arg_struct->increment) < limit) {
            (*(arg_struct->increment))++;
            (*(arg_struct->acquisitons))++;
        }
        bool released = arg_struct->mutex->release();
        assert(!acquired || (acquired && released));
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t thread1, thread2;
    Mutex mutex;
    int increment = 0;
    int acquisitions_by_thread1 = 0;
    int acquisitions_by_thread2 = 0;
    int iret1 = 0;
    int iret2 = 0;
    argument_struct arg_struct1  = { &increment, &acquisitions_by_thread1, &mutex };
    argument_struct arg_struct2  = { &increment, &acquisitions_by_thread2, &mutex };

    iret1 = pthread_create( &thread1, NULL, work, static_cast<void*>(&arg_struct1));
    iret2 = pthread_create( &thread2, NULL, work, static_cast<void*>(&arg_struct2));

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); 

    if (acquisitions_by_thread1 > acquisitions_by_thread2) {
        std::cout << "C++ style: Thread 1 wins with ";
    } else if (acquisitions_by_thread1 < acquisitions_by_thread2) {
        std::cout << "C++ style: Thread 2 wins with ";
    } else {
        std::cout << "C++ style: It is a stalement with ";
    }
    std::cout << acquisitions_by_thread1 << " to " << acquisitions_by_thread2 << std::endl;

    return 0;
}