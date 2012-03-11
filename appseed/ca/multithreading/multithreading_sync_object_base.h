#pragma once


#include "ca/primitive/datetime/datetime_duration.h"
#include "ex1/ex1_request_interface.h"




/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object

/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/

class CLASS_DECL_ca sync_object_base :
   virtual public ::ex1::request_interface
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


