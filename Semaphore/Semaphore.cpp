#include "Semaphore.h"

#include <cassert>

Semaphore::Semaphore(unsigned int max_available, unsigned int initial) : counter(initial), max_available(max_available), initial(initial) {}

bool Semaphore::increment()
{
    int oldValue = counter.load();
    if (oldValue < max_available && counter.compare_exchange_strong(oldValue, oldValue + 1))
    {
        return true;
    }

    return false;
}

bool Semaphore::decrement()
{
    int oldValue = counter.load();
    if (oldValue > 0 && counter.compare_exchange_strong(oldValue, oldValue - 1))
    {
        return true;
    }

    return false;
}

int Semaphore::load()
{
    return counter.load();
}
