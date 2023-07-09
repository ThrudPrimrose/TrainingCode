#pragma once

#include <pthread.h>
#include <atomic>

class Mutex {
    private:
    // C equivalent atomic_int or _Atomic int
    std::atomic<int> owner_tracker;
    const static int value_when_unowned = -1;

    public:
    Mutex();

    bool acquire();
    bool release();
};