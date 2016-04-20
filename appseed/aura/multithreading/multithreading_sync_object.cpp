#include "framework.h"


sync_object::sync_object(const char * pszName)
{

   m_bOwner = true;

#ifdef WINDOWS

   m_object = NULL;

#endif

   if(pszName == NULL)
   {

      m_pszName = NULL;

   }
   else
   {

      m_pszName = strdup(pszName);

   }

}

sync_object::~sync_object()
{
#ifdef _WIN32
   if (m_bOwner && m_object != NULL)
   {
      ::CloseHandle(m_object);
      m_object = NULL;
   }
#endif

   if(m_pszName != NULL)
   {

      ::free(m_pszName);

   }

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

   return wait_result(wait_result::Failure);

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

   return true;

}


bool sync_object::unlock()
{

   return true;

}




