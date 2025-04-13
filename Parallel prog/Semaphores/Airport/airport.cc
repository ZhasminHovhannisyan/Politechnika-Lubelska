#include <thread>
#include <mutex>
#include <random>
#include <iostream>
#include <set>
#include <vector>
#include <thread>
// #include "semaphore.h"

using namespace std;

const int HANGAR_CAPACITY=5;
const int NUMBER_OF_PLANES = 10;

random_device rd;
minstd_rand generator(rd());
uniform_int_distribution<int> range(1, 5);

class Hangar;
class Airplane;

class Airport {
public:

     Airport(Hangar &h) : runwayFree(true), hangar(h) {
     }
     void land(Airplane &s);
     void goToHangar(Airplane &s);
     void leaveHangar(Airplane &s);
     void takeoff(Airplane &s);
private:
     bool runwayFree;
     Hangar &hangar;
};

class Airplane {
public:

     Airplane(string n, Airport &l) : name(n), airport(l) {
     }
     string name;

     void operator()() {
         this_thread::sleep_for(chrono::seconds(range(generator))*10);
         airport.land(*this);
         // stop at the arrivals hall
         this_thread::sleep_for(chrono::seconds(range(generator)));
         airport.goToHangar(*this);
         // stop in the hangar
         this_thread::sleep_for(chrono::seconds(range(generator))*5);
         airport.leaveHangar(*this);
         // stop at the departures hall
         this_thread::sleep_for(chrono::seconds(range(generator)));
         airport.takeoff(*this);
     }

private:
     Airport &airport;
};

class Hangar {
public:

     Hangar(int n) : hangarsize(n) {
     }

     void park(Airplane &s) {
         if (planes.size() < hangarsize) {
             planes.insert(s.name);
         } else {
             cout << "Hangar full\n";
         }
     }

     void leave(Airplane &s) {
         if (planes.count(s.name) == 1) {
             planes.erase(s.name);
         } else {
             cout << "This plane is not in the hangar\n";
         }
     }

private:
     unsigned hangarsize;
     set<string> planes;
};

void Airport::land(Airplane &s) {
     if (runwayFree) {
         runwayFree = false;
         string info = "Airplane " + s.name + " landing\n";
         cout << info;
         this_thread::sleep_for(chrono::seconds(range(generator)));
         info = "The plane " + s.name + " landed\n";
         runwayFree = true;
     } else {
         cout << "Collision on the runway\n";
     }
}

void Airport::goToHangar(Airplane &s) {
     hangar.park(s);
}

void Airport::leaveHangar(Airplane &s) {
     hangar.leave(s);
}

void Airport::takeoff(Airplane &s) {
     if (runwayFree) {
         runwayFree = false;
         string info = "Airplane " + s.name + " taking off\n";
         cout << info;
         this_thread::sleep_for(chrono::seconds(range(generator)));
         info = "The plane " + s.name + " took off\n";
         runwayFree = true;
     } else {
         cout << "Collision on the runway\n";
     }
}

int main(int argc, char** argv) {
     Hangar hangar(HANGAR_CAPACITY);
     Airport airport(hangar);

     vector<thread> threads;

     for (int i = 0; i < NUMBER_OF_PLANES; ++i) {
         string string = "Parallel Airlines "+to_string(i);
         threads.emplace_back(Airplane(string, airport));
     }

     for (thread &w: threads) w.join();

     return EXIT_SUCCESS;
}
