#include "framework.h"


bool call_stack::s_bDoStackTrace = false;


#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS)
call_stack::call_stack(sp(::base::application) papp, uint32_t uiSkip, void * address) :
   element(papp)
   ,m_caller_address(address)
#else
call_stack::call_stack(sp(::base::application) papp, uint32_t uiSkip) :
   element(papp)
#endif
{

   if(s_bDoStackTrace && uiSkip != 0xffffffffu)
   {

      m_strCallStack = call_stack::get(uiSkip);

   }

}

call_stack::call_stack(const ::call_stack & cs) :
   element(cs)
{

   m_strCallStack = cs.m_strCallStack;

}

string call_stack::get(uint32_t uiSkip)
{

   string str;

   UNREFERENCED_PARAMETER(uiSkip);

#ifdef LINUX
   System.eengine().stack_trace(str, uiSkip, m_caller_address);
#else
   System.eengine().stack_trace(str, uiSkip);
#endif

   return str;

}

const char * call_stack::stack_trace() const
{

   return m_strCallStack;

}
