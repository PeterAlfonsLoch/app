#include "StdAfx.h"


synch_lock::synch_lock(sync_object_base * pobject) :
   single_lock(pobject, true)
{
}


synch_lock::~synch_lock()
{
}
