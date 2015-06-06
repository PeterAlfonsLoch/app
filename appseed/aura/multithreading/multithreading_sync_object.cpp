#include "framework.h"


sync_object::sync_object(const char * pstrName)
{
#ifdef WINDOWS
   m_object = NULL;
#endif
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

bool sync_object::lock(const duration & durationTimeout)
{
#ifdef WINDOWS

   uint32_t dwRet = ::WaitForSingleObjectEx(m_object, durationTimeout.lock_duration(), FALSE);
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return TRUE;
   else
      return FALSE;
#else
   
   if(wait(durationTimeout).failed())
   {

      return false;

   }

   return true;

#endif
}

wait_result sync_object::wait(const duration & durationTimeout)
{
#ifdef WINDOWS
   return wait_result((uint32_t) ::WaitForSingleObjectEx(m_object,durationTimeout.lock_duration(),FALSE));
#else

   if(!lock(durationTimeout))
   {

      return wait_result(wait_result::Failure);

   }

   return wait_result(wait_result::Success);

#endif
}

void sync_object::dump(dump_context & dumpcontext) const
{

#ifdef WINDOWS
   dumpcontext << "Object ";
   dumpcontext << m_object;
#endif

   dumpcontext << " named " << m_strName << "\n";

   object::dump(dumpcontext);

}

void sync_object::assert_valid() const
{
   object::assert_valid();
}

#ifdef WINDOWS

sync_object::operator HANDLE() const
{
   return m_object;
}

#endif

void * sync_object::get_os_data() const
{
#ifdef WINDOWS
   return (void *) m_object;
#else
   return 0;
#endif
}

bool sync_object::unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */)
{

   return TRUE;

}

bool sync_object::unlock()
{

   return true;

}