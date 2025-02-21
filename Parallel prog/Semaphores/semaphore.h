#include <mutex>
#include <condition_variable>

using namespace std;

//is used to manage access to limited resources

class Semaphore
{
  public :
  Semaphore( int _count=1 );

  //frees resource
  void signal();

  //occupies the resource (if there are no free resources
  //this waits for the resource to be released)
  void wait();

  //trying to occupy a resource, returns true if
  //successful, false if all
  //resources are busy
  bool try_to_wait();

  //returns the current counter value
  int value() const ;

  private :
    //counter of available resources
    int resourcecounter;

    //thread synchronization
    mutex mutexCounter;
    condition_variable conditionCounterDifferentFromZero;
};