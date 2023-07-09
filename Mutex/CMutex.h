#pragma once

#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

const static int value_when_unowned = -1;

struct CMutex {
    _Atomic(int) owner_tracker;
};

struct CMutex* Init_CMutex();

bool acquire(struct CMutex* cmutex);

bool release(struct CMutex* cmutex);