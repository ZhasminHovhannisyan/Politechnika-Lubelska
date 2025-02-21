#include <iostream>
#include <thread>
//#include <mutex>
#include <random>
//#include <vector>
#include "semaphore.h"

 using namespace std;

// Global Semaphore
Semaphore semaphore(1); // Start with 1 resource available (mutex-like behavior)

// Function executed by each thread
void threadFunction(int threadID, int count) {
    for (int i = 0; i < count; ++i) {
        // Wait to acquire access to the resource
        semaphore.wait();

        // Critical Section
        cout << "Thread " << threadID << " prints " << i << endl;

        // Simulate some work
        this_thread::sleep_for(chrono::milliseconds(100));

        // Signal to release the resource
        semaphore.signal();
    }
}

int main() {
    const int THREAD_COUNT = 4;  // Number of threads
    const int PRINT_COUNT = 10;  // Number of times each thread prints
    vector<thread> threads;

    // Create threads
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads.emplace_back(threadFunction, i, PRINT_COUNT);
    }

    // Join threads
    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
