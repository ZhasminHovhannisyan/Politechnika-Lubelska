#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <iostream>
#include "semaphore.h"

using namespace std;

class Platform;

  class Train {
  private :
  string m_name;
  Platform &platform;
  Platform &spare_platform;

  public :
  Train(string n, Platform &p1, Platform &p2);
     void operator ()();
  string name();
};

class Platform {
  private :
  string name;
  bool empty;
  mutex mtx;

  public :

  Platform(string n) : name(n), empty( true ) { }

  void arrival(Train& p) {
      lock_guard<mutex> lock(mtx); // 🔒 Protect access
      if (empty) {
          cout << "Train " << p.name() << " enters the platform " << name << "\n";
      } else {
          cout << "Train " << p.name() << " caused a disaster on the platform " << name << "\n";
      }
      empty = false;

  void departure(Train& p) {
      lock_guard<mutex> lock(mtx);
      cout << "Train " << p.name() << " leaves platform " << name << "\n";
      empty = true;

  bool isEmpty() {
      lock_guard<mutex> lock(mtx);
      return empty;
  }
};

  minstd_rand generator;
  uniform_int_distribution< int > range( 0 , 500 );

  Train::Train(string n, Platform &p1, Platform &p2) : m_name(n), platform(p1), spare_platform(p2) { }

  string Train::name() {
    return m_name;
  }

void Train:: operator ()() {
  for ( int i = 0 ; i < 3 ; i++) {
    this_thread::sleep_for(chrono::milliseconds(range(generator)));
    //the train tries to enter the preferred platform
    if (platform.isEmpty()) {
      //the platform is clear, so the train is arriving
      platform.arrival(* this );
      //passengers board/disembark
      this_thread::sleep_for(chrono::milliseconds(range(generator)));
      //the train is leaving
      platform.departure(* this );
    } //if this fails, they enter the alternative platform
    else {
      //the platform is free so they know the train is coming
      spare_platform.arrival(* this );
      //passengers board/disembark
      this_thread::sleep_for(chrono::milliseconds(range(generator)));
      //the train is leaving
      spare_platform.departure(* this );
    }
  }
}

int main( int argc, char * argv[]) {
  //there are 3 platforms at the station
  Platform p1( "p1" ), p2( "p2" ), p3( "p3" );

  Train train1( "train1" , p2, p1);
  Train train2( "train2" , p2, p3);
  Train train3( "train3" , p2, p1);
  Train train4( "train4" , p2, p3);

  thread w1(train1);
  thread w2(train2);
  thread w3(train3);
  thread w4(train4);

  w1.join();
  w2.join();
  w3.join();
  w4.join();

  return ( EXIT_SUCCESS );
}
