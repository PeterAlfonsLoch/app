#pragma once


#include "ca/gen/gen_object.h"
#include "ca/datetime/datetime_duration.h"


/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object

/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/

class CLASS_DECL_ca sync_object_base :
   virtual public ::gen::object
{
public:

   sync_object_base();
   sync_object_base(const sync_object_base & objectSrc);
   virtual ~sync_object_base();


   virtual void * get_os_data() const;

   virtual bool lock(const duration & durationTimeout = duration::infinite());
   virtual bool unlock();
   virtual bool unlock(LONG lCount, LPLONG lpPrevCount = NULL);


};


