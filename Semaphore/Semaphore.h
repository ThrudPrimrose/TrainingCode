#pragma once

#include <atomic>

class Semaphore {
    private:
    std::atomic<int> counter;
    int max_available;
    int initial;

    public:
    Semaphore(unsigned int max_available, unsigned int initial);

    bool increment();
    bool decrement();

    int load();
};