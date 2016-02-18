#include "framework.h"


sync_object::sync_object(const char * pstrName)
{
   m_bOwner = true;
#ifdef WINDOWS
   m_object = NULL;
#endif
#ifdef DEBUG
   m_pszName = pstrName == NULL ? NULL : strdup(pstrName);
#endif
}

sync_object::~sync_object()
{
#ifdef _WIN32
   if (m_bOwner && m_object != NULL)
   {
      ::CloseHandle(m_object);
      m_object = NULL;
   }
   if (m_pszName != NULL)
   {
      ::free((void*) m_pszName);
   }
#endif
}


bool sync_object::lock(const duration & durationTimeout)
{

   if(!wait(durationTimeout).signaled())
   {

      return false;

   }

   return true;

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

   return wait_result(wait_result::Event0);

#endif
}

void sync_object::dump(dump_context & dumpcontext) const
{

#ifdef WINDOWS
   dumpcontext << "Object ";
   dumpcontext << m_object;
#endif

   dumpcontext << " named " << m_pszName << "\n";

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
