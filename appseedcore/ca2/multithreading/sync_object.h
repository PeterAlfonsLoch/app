#pragma once


/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object

/** templatization of sync_object inspired my class 
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/
class CLASS_DECL_ca sync_object_base : 
   public ::radix::object
{
public:

#ifdef _WIN32
   virtual HANDLE get_handle() = 0;
#endif

// Operations
   virtual BOOL Lock(DWORD dwTimeout = INFINITE) = 0;
   virtual BOOL Unlock() = 0;
   virtual BOOL Unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */)
   {
      return TRUE; 
   }

// Implementation
public:
   virtual ~sync_object_base();
   friend class CSingleLock;
   friend class CMultiLock;
};


template < typename THANDLE >
class sync_object : 
   public sync_object_base
{
public:
   explicit sync_object(LPCTSTR pstrName);

   virtual THANDLE get_handle();

   operator THANDLE() const;
   THANDLE  m_hObject;

// Operations
   virtual BOOL Lock(DWORD dwTimeout = INFINITE);
   virtual BOOL Unlock() = 0;
   virtual BOOL Unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */);

// Implementation
public:
   virtual ~sync_object();
#ifdef _DEBUG
   string m_strName;
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
   friend class CSingleLock;
   friend class CMultiLock;
};


template < typename THANDLE >
BOOL sync_object<THANDLE>::Unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */)
   { return TRUE; }

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
BOOL sync_object < THANDLE >::Lock(DWORD dwTimeout)
{
#ifdef WIN32
   DWORD dwRet = ::WaitForSingleObject(m_hObject, dwTimeout);
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
   { return m_hObject;}

template < typename THANDLE >
THANDLE sync_object < THANDLE >::get_handle()
   { return m_hObject;}

