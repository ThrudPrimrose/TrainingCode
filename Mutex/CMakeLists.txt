find_package(Threads REQUIRED)

add_library(mutex_cpp Mutex.cpp)
add_library(mutex_c CMutex.c)

add_executable(mutex_example_cpp main.cpp)
add_executable(mutex_example_c main.c)

target_link_libraries(mutex_example_cpp PRIVATE mutex_cpp Threads::Threads)
target_link_libraries(mutex_example_c PRIVATE mutex_c Threads::Threads)