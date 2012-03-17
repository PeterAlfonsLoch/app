#pragma once

/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object

/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/

template < typename THANDLE >
class sync_object :
   public ::radix::object
{
public:


   THANDLE     m_hObject;
   string      m_strName;


   explicit sync_object(LPCTSTR pstrName);
   virtual ~sync_object();


   virtual void * get_os_data() const;

   operator THANDLE() const;

   virtual bool lock(const duration & durationTimeout = duration::infinite());
   virtual bool unlock() = 0;
   virtual bool unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

};


template < typename THANDLE >
bool sync_object<THANDLE>::unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */)
{
   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object
template < typename THANDLE >
sync_object < THANDLE >::sync_object(const char * pstrName)
{
   UNUSED(pstrName);   // unused in release builds

   m_hObject = NULL;

#ifdef _DEBUG
   m_strName = pstrName;
#endif
}

template < typename THANDLE >
sync_object < THANDLE >::~sync_object()
{
   #ifdef _WIN32
   if (m_hObject != NULL)
   {
      ::CloseHandle(m_hObject);
      m_hObject = NULL;
   }
#endif
};

template < typename THANDLE >
bool sync_object < THANDLE >::lock(const duration & durationTimeout)
{
#ifdef WIN32
   DWORD dwRet = ::WaitForSingleObject(m_hObject, durationTimeout.os_lock_duration());
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return TRUE;
   else
      return FALSE;
#else
   throw not_implemented_exception();
#endif
}

#ifdef _DEBUG

template < typename THANDLE >
void sync_object < THANDLE >::dump(dump_context & dumpcontext) const
{
   dumpcontext << "Object ";
   dumpcontext << m_hObject;
   dumpcontext << " named " << m_strName << "\n";
   ::radix::object::dump(dumpcontext);
}

template < typename THANDLE >
void sync_object < THANDLE >::assert_valid() const
{
   ::radix::object::assert_valid();
}

#endif

template < typename THANDLE >
inline sync_object < THANDLE >::operator THANDLE() const
{
   return m_hObject;
}

template < typename THANDLE >
void * sync_object < THANDLE >::get_os_data() const
{
   return m_hObject;
}

