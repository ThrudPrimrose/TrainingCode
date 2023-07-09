#include "CMutex.h"
#include <stdlib.h>

struct CMutex* Init_CMutex(){
    struct CMutex* cmutex =  (struct CMutex*)malloc(sizeof(struct CMutex)); 
    // Negative int indicated no owner
    atomic_init(&(cmutex->owner_tracker), value_when_unowned);
}

bool acquire(struct CMutex* cmutex){
    int copy_unowned_value = -1;
    int current_id = (int)(pthread_self());
    return atomic_compare_exchange_strong(&cmutex->owner_tracker, &copy_unowned_value, current_id);
}

bool release(struct CMutex* cmutex){
    int current_id = (int)(pthread_self());
    return atomic_compare_exchange_strong(&cmutex->owner_tracker, &current_id, value_when_unowned);
}
