#include <thread>
#include <mutex>
#include <random>
#include <iostream>
#include <vector>
#include "semaphore.h"

using namespace std;

// Eating time in ms
const int MAX_DELAY = 1000;

random_device rd;
minstd_rand generator(rd());
uniform_int_distribution<int> distribution(0, MAX_DELAY);

const int NUMBER_OF_PHILOSOPHERS = 5;
const int NUMBER_OF_MEALS = 3;

// Create a binary semaphore for each fork
Semaphore* forks[NUMBER_OF_PHILOSOPHERS];

// Create a multi-state semaphore to limit the number of eating philosophers
Semaphore diningRoom(NUMBER_OF_PHILOSOPHERS - 1);

// Mutex for display protection
mutex displayMutex;

class Philosopher {
private:
    int number;
    int leftFork;
    int rightFork;
    int eatenMeals;

public:
    Philosopher(int n) : number(n), eatenMeals(0) {
        // Left fork is the philosopher's own number
        leftFork = number;
        // Right fork is the next philosopher's fork
        rightFork = (number + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS;
    }

    void operator()() {
        while (eatenMeals < NUMBER_OF_MEALS) {
            // Operations to wait for the dining room semaphore
            diningRoom.wait();

            // Wait for the left fork
            forks[leftFork]->wait();
            // Wait for the right fork
            forks[rightFork]->wait();

            // Simulate eating
            int mealtime = distribution(generator);
            {
                lock_guard<mutex> lock(displayMutex);
                cout << "Philosopher " << number << " is eating meal " << eatenMeals + 1
                     << " for " << mealtime << "ms." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(mealtime));

            {
                lock_guard<mutex> lock(displayMutex);
                cout << "Philosopher " << number << " has finished meal " << eatenMeals + 1 << "." << endl;
            }
            ++eatenMeals;

            // Signal the release of the right fork
            forks[rightFork]->signal();
            // Signal the release of the left fork
            forks[leftFork]->signal();

            // Release the dining room semaphore
            diningRoom.signal();
        }

        {
            lock_guard<mutex> lock(displayMutex);
            cout << "Philosopher " << number << " has eaten all meals." << endl;
        }
    }
};

int main(int argc, char **argv) {
    // Create fork semaphores (arrays)
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
        forks[i] = new Semaphore(1); // Each fork can be used by one philosopher at a time
    }

    // Create philosophers
    vector<thread> philosophers;
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(Philosopher(i));
    }

    // Wait for completion
    for (thread &f : philosophers) {
        f.join();
    }

    return EXIT_SUCCESS;
}
