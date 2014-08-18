#pragma once

/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object
// de-templatization on 2012-05-13
/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/

class CLASS_DECL_BASE sync_object :
   public object
{
public:

#ifdef WINDOWS
   HANDLE      m_object;
#endif
   string      m_strName;


   sync_object(const char * pstrName);
   virtual ~sync_object();

   virtual void * get_os_data() const;

   operator HANDLE() const;

   using object::lock;
   virtual bool lock(const duration & durationTimeout);

   using object::wait;
   virtual wait_result wait(const duration & durationTimeout);

   virtual bool unlock() = 0;
   virtual bool unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

};


