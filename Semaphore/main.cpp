#include "Semaphore.h"

#include <thread>
#include <random>
#include <chrono>
#include <iostream>

void produce(Semaphore& semaphore) 
{
    // 1 Worker thread, do not need to think a lot about the problems
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(10, 20);
    static int produced = 0;
    while (produced < 1000) {
        if(semaphore.increment()){
            int sleep_duration = dist(mt); 
            produced++;
            std::cout << "Produced, available: " + std::to_string(semaphore.load()) + ", produced: " + std::to_string(produced) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
        }

    }
}

void consume(Semaphore& semaphore)
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(60, 100);
    static std::atomic<int> consumed{0};
    int current_val = consumed.load();
    while (current_val < 1000){
        if(semaphore.decrement()){
            int sleep_duration = dist(mt);
            int value_to_write = current_val + 1;
            consumed++;
            std::cout << "Consumed, available: " + std::to_string(semaphore.load()) + ", consumed: " + std::to_string(value_to_write) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
            current_val = consumed.load();
        }

    }
}

int main() 
{
  Semaphore semaphore(10, 0);
  std::thread producer_thread(produce, std::ref(semaphore));
  std::thread worker_threads[4];
  for (int i = 0; i < 4; i++){
    worker_threads[i] = std::thread(consume, std::ref(semaphore));
  }

  producer_thread.join();
  for (int i = 0; i < 4; i++){
    worker_threads[i].join();
  }
}