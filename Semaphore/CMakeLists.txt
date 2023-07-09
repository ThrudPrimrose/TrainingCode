find_package(Threads REQUIRED)

add_library(semaphore_cpp Semaphore.cpp)
add_executable(semaphore_example_cpp main.cpp)

target_link_libraries(semaphore_example_cpp PRIVATE semaphore_cpp Threads::Threads)