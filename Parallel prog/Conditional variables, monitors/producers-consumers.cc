#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

// allow waiting for a specific condition to be met
#include <condition_variable>
//random number generator
#include <random>

using namespace std;

//time during which the producer will generate characters
const int WORK_TIME = 5 ;

//Monitor - a container that stores and provides data
//thread synchronization

mutex screenMutex;

template <typename DataType>
class Monitor {
   private :
      DataType data;
      bool DataReady; //is the data up to date?

      mutex mutexData;
      //allows you to wait for new data
      condition_variable conditionNewDataExists;
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
         conditionNewDataExists.notify_one();
         //here the lock ceases to exist
      }
      DataType read()
      {
         //lock prevents simultaneous data writing
         unique_lock<mutex> lock(mutexData);
         //if there is no data, we have to wait until some data is saved
         //(data lock is temporarily removed)
         while (!DataReady) conditionNewDataExists.wait(lock);
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
      void operator ()(int number)
      {
         while (time<WORK_TIME)
         {
			//first character is initialized by the constructor
            container.save(currentChar);
		    {
		      lock_guard<mutex> consoleLock(screenMutex);
		         cout<<"Producer: "<< number << " produced: " << currentChar << endl;
		    }
            //generate character from 'b' to 'z'
            currentChar=(currentChar + 1 - 97 ) % 25 + 97 ;

           //then for variety
           //you can write random characters instead of consecutive ones
           //container.save(decomposition(generator));

           //break at work
           this_thread::sleep_for(chrono::seconds( 1 ));
           ++time;
         }
         //the "end of file" character terminates the consumer
         container.save(EOF);
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
      void operator ()(int number)
      {
         char character = container.read();
         while (character != EOF )
		 {
		    screenMutex.lock();
			   cout<<"Consumer: "<< number << " reads: " << character << endl;
		    screenMutex.unlock();
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
   //create consumer threads
	vector<thread> consumers;
	for (int i=0; i<4; i++)
		consumers.emplace_back(thread(Consumer(container), i));
		//consumers.push_back(thread(Consumer(container), i));
   //create producer threads
	vector<thread> producers;
	for (int i=0; i<4; i++)
		producers.emplace_back(thread(Producer(container), i));
		//producers.push_back(thread(Producer(container), i));
   //wait for threads to end
	for (thread& con:consumers) con.join();
	for (thread& prod:producers) prod.join();

   return ( EXIT_SUCCESS );
}



char strings[3][80] = { "Ha! Ha! Ha! It's only a superficial signal!\n",
 "Only process %d can ignore signal %d \n",
 "Ouch - that hurt!\n" };
int string_no = 0;
void sig_int_handling(int sig)
{
    printf(strings[string_no], getpid(), sig);
    string_no = ((string_no + 1) % 3);
}
int main(int argc, char** argv)
{
    signal(SIGINT, sig_int_handling);

    while (true)
    {
        printf("Hello it is process: %d\n", getpid());
        sleep(1);
    }

    return 0;
}