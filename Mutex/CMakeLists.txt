find_package(Threads REQUIRED)

add_executable(mutex_cpp main.cpp Mutex.cpp)
add_executable(mutex_c main.c CMutex.c)

target_link_libraries(mutex_cpp PRIVATE Threads::Threads)

target_link_libraries(mutex_c PRIVATE Threads::Threads)