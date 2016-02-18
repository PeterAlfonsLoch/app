#pragma once

/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object
// de-templatization on 2012-05-13
/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/

class CLASS_DECL_AURA sync_object :
   virtual public object
{
public:

#ifdef WINDOWS
   HANDLE      m_object;
#endif
   const char *      m_pszName;
   bool                    m_bOwner;


   sync_object(const char * pstrName);
   virtual ~sync_object();

   virtual void * get_os_data() const;

   operator HANDLE() const;

   virtual void lock();
   virtual bool lock(const duration & durationTimeout);

   virtual void wait();
   virtual wait_result wait(const duration & durationTimeout);

   virtual bool is_locked() const;

   virtual bool unlock();
   virtual bool unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

};


