#pragma once

#include <pthread.h>
#include <atomic>

struct Mutex {
    // C equivalent atomic_int or _Atomic int
    std::atomic<int> owner_tracker;
    const static int value_when_unowned = -1;

    Mutex();

    bool acquire();
    bool release();
};