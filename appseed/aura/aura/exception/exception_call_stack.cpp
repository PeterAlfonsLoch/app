//#include "framework.h"


#if defined(APPLE_IOS)

bool call_stack::s_bDoStackTrace = false;

#define CALL_STACK_DEFAULT_SKIP 3

#elif defined(VSNORD)

bool call_stack::s_bDoStackTrace = true;

#define CALL_STACK_DEFAULT_SKIP 4

#else

bool call_stack::s_bDoStackTrace = false;

#define CALL_STACK_DEFAULT_SKIP 3

#endif





#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS) || defined(VSNORD)
call_stack::call_stack(::aura::application * papp, uint32_t uiSkip, void * address) :
   object(papp)
   ,m_caller_address(address)
#else
call_stack::call_stack(::aura::application * papp, uint32_t uiSkip) :
   object(papp)
#endif
{

   if(s_bDoStackTrace && uiSkip != SKIP_CALL_STACK)
   {

      if (uiSkip == CALL_STACK_DEFAULT_SKIP_TRIGGER)
      {

         uiSkip = CALL_STACK_DEFAULT_SKIP;

      }

      m_strCallStack = call_stack::get(uiSkip);

      output_debug_string(m_strCallStack);

   }

}

call_stack::call_stack(const ::call_stack & cs) :
object(cs)
{

   m_strCallStack = cs.m_strCallStack;

}

string call_stack::get(uint32_t uiSkip)
{

   string str;

#if defined(LINUX)

   System.eengine().stack_trace(str, uiSkip, m_caller_address);

#else

   System.eengine().stack_trace(uiSkip);

   str = System.eengine()._strS;

#endif

   return str;

}

const char * call_stack::stack_trace() const
{

   return m_strCallStack;

}
