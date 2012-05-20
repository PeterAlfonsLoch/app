#include "framework.h"


sync_object::sync_object(const char * pstrName)
{

   m_object = NULL;

#ifdef DEBUG
   m_strName = pstrName;
#endif
}

sync_object::~sync_object()
{
   #ifdef _WIN32
   if (m_object != NULL)
   {
      ::CloseHandle(m_object);
      m_object = NULL;
   }
#endif
}

inline bool sync_object::lock(const duration & durationTimeout)
{
#ifdef WINDOWS
   DWORD dwRet = ::WaitForSingleObject(m_object, durationTimeout.os_lock_duration());
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return TRUE;
   else
      return FALSE;
#else
   throw not_implemented_exception();
#endif
}

inline void sync_object::dump(dump_context & dumpcontext) const
{

#ifdef WINDOWS
   dumpcontext << "Object ";
   dumpcontext << m_object;
#endif

   dumpcontext << " named " << m_strName << "\n";

   ::radix::object::dump(dumpcontext);

}

void sync_object::assert_valid() const
{
   ::radix::object::assert_valid();
}

#ifdef WINDOWS

inline sync_object::operator HANDLE() const
{
   return m_object;
}

#endif

inline int_ptr sync_object::get_os_data() const
{
   return (int_ptr) m_object;
}

inline bool sync_object::unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */)
{
   return TRUE;
}

