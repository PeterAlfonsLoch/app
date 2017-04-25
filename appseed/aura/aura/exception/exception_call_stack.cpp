//#include "framework.h"


#if defined(APPLE_IOS)

bool call_stack::s_bDoStackTrace = true;

#elif defined(VSNORD)

bool call_stack::s_bDoStackTrace = true;

#else

bool call_stack::s_bDoStackTrace = true;

#endif

// 0 - most deep call stack logging
// 4 - most lite call stack logging
int g_iCallStackLevel = 4; 



#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS) || defined(VSNORD)
call_stack::call_stack(::aura::application * papp, uint32_t uiSkip, void * address) :
   object(papp)
   ,m_caller_address(address)
#else
call_stack::call_stack(::aura::application * papp, uint32_t uiSkip) :
   object(papp)
#endif
{

   if (m_pauraapp == NULL)
   {

      m_pauraapp = get_thread_app();

   }

   if(s_bDoStackTrace && uiSkip != SKIP_CALL_STACK)
   {

      if (uiSkip == CALL_STACK_DEFAULT_SKIP_TRIGGER)
      {

         uiSkip = CALL_STACK_DEFAULT_SKIP;

      }

      m_pszCallStack = call_stack::get_dup(uiSkip);

   }

}

call_stack::call_stack(const ::call_stack & cs) :
object(cs)
{

   m_pszCallStack = cs.m_pszCallStack == NULL? NULL: strdup(cs.m_pszCallStack);

}


call_stack::~call_stack()
{

   if (m_pszCallStack != NULL)
   {

      free((void*)m_pszCallStack);

   }

}

const char * call_stack::get_dup(uint32_t uiSkip)
{

   const char * psz;

   synch_lock sl(::exception::engine().m_pmutex);

#if defined(LINUX)

   psz = System.eengine().stack_trace_dup(uiSkip, m_caller_address);

#else

   ::exception::engine().stack_trace(uiSkip);

   psz = strdup(::exception::engine()._strS);

#endif

   return psz;

}

const char * call_stack::stack_trace() const
{

   return m_pszCallStack;

}
