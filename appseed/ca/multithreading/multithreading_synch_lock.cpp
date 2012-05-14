#include "framework.h"


synch_lock::synch_lock(waitable * pobject) :
   single_lock(pobject, true)
{
}


synch_lock::~synch_lock()
{
}
