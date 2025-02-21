#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

// allow waiting for a specific condition to be met
#include <condition_variable>
//random number generator
#include <random>

using namespace std;

//time during which the producer will generate characters
const int WORK_TIME = 5 ;

//Monitor - a container that stores and provides data
//thread synchronization
template <typename DataType>
class Monitor {
   private :
      DataType data;
      bool DataReady; //is the data up to date?

      mutex mutexData;
      //allows you to wait for new data
      condition_variable conditionSaNewDane;
      //allows you to empty the container
      condition_variable conditionDataTaken;
   public :
      Monitor()
      {
         DataReady= false ; //initially the container is empty
      }
      void save(DataType newData)
      {
         //lock prevents simultaneous reading of data
         //we have to use unique_lock<> because the condition variable
         //will have to remove the lock - lock_guard<> is not suitable
         unique_lock<mutex> lock(mutexData);
         //if the container is full, wait for the data to be collected
         //(data lock is temporarily removed)
         while (DataReady) conditionDataTaken.wait(lock);
         //the container is empty, the lock is active again
         DataReady= true ;
         data=newData;
         //if another thread is waiting for data, we notify it
         conditionSaNewDane.notify_one();
         //here the lock ceases to exist
      }
      DataType read()
      {
         //lock prevents simultaneous data writing
         unique_lock<mutex> lock(mutexData);
         //if there is no data, we have to wait until some data is saved
         //(data lock is temporarily removed)
         while (!DataReady) conditionSaNewDane.wait(lock);
         DataReady= false ;
         //if any thread is waiting for the container to be empty
         //then we notify him
         conditionDataTaken.notify_one();
         return data;
         //here the lock ceases to exist
      }
};

class Producer {
   private :
      //time the producer worked
      int time;
      //reference to a common data container
      Monitor< char >& container;
      //current character
      char currentChar;

      //random number generator
      minstd_rand generator; //pseudo-random number generator algorithm
      uniform_int_distribution< char > distribution; //distribution of pseudo-random numbers
   public :
      //creating a producer that generates the characters [a,z]
      Producer(Monitor < char >& _container):

      time(0), container(_container), currentChar('a'), generator(random_device()()), distribution('a', 'z') {}

      //code executed in the thread
      void operator ()()
      {
         while (time<WORK_TIME)
         {
            //first we generate subsequent characters
            //(to check synchronization)
            container.save(currentChar);
            //next character from 'a' to 'z'
            currentChar=(currentChar+ 1 - 97 )% 25 + 97 ;

           //then for variety
           //you can write random characters instead of consecutive ones
           //container.save(decomposition(generator));

           //break at work
           this_thread::sleep_for(chrono::seconds( 1 ));
           ++time;
         }
         //the "end of file" character terminates the consumer
         container.save( EOF );
      }
};

class Consumer {
   private :
      //reference to the common container
      Monitor< char >& container;
   public :
      //create a consumer
      Consumer(Monitor< char >& _container): container(_container) {}

      //code executed in the thread
      void operator ()()
      {
         char character = container.read();
         while (character != EOF )
         {
            cout<<character<<endl;
            character=container.read();
         }
      }
};

int main( int argc, char ** argv) {
   random_device r;
   minstd_rand generator(r()) ;
   //creating a common container for the consumer and the producer
   Monitor< char > container;
   //creating a producer and a consumer
   Consumer consumer(container);
   Producer producer(container);
   //create threads
   thread wk(consumer);
   thread wp(producer);
   //wait for threads to end
   wp.join();
   wk.join();
   return ( EXIT_SUCCESS );
}
