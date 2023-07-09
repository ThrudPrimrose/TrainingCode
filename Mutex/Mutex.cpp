#include "Mutex.h"

Mutex::Mutex(){
    // Negative int indicated no owner
    owner_tracker.store(value_when_unowned);
}

bool Mutex::acquire(){
    int copy_unowned_value = -1;
    int current_id = static_cast<int>(pthread_self());
    return owner_tracker.compare_exchange_strong(copy_unowned_value, current_id);
}

bool Mutex::release(){
    int current_id = static_cast<int>(pthread_self());
    // C equivalent atomic_compare_exchange_strong(&owner_tracker, &current_id, value_when_unowned);
    return owner_tracker.compare_exchange_strong(current_id, value_when_unowned);
}
