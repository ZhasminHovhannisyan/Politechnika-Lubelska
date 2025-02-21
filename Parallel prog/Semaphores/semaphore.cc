#include "semaphore.h"

Semaphore::Semaphore( int _count)
: resourcecounter(_count) { }

int Semaphore::value() const
{
   return resourcecounter ;
}

void Semaphore::signal()
{
  //exclusive counter
  unique_lock<mutex> counterLock(mutexCounter);
  //increment the counter
  ++resourcecounter;
  //notify one waiting thread that the counter is gone
  //has been incremented
  conditionCounterDifferentFromZero.notify_one();
}

void Semaphore::wait()
{
  //exclusive counter
  unique_lock<mutex> counterLock(mutexCounter);
  //if the counter is equal to 0, we cannot do it
  //decrease, wait until it is incremented by
  //another thread
  while (resourcecounter == 0 )
    conditionCounterDifferentFromZero.wait(counterLock);
  //decrease the counter
  --resourcecounter;
}

bool Semaphore::try_to_wait()
{
  //exclusive counter
  unique_lock<mutex> counterLock(mutexCounter);
  //if the counter is greater than 0, we decrement it
  if (resourcecounter != 0 ) {
    --resourcecounter;
    return true ;
  } //otherwise we report that it failed
  else
    return false ;
}
