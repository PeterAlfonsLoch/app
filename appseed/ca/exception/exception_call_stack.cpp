#include "framework.h"


bool call_stack::s_bDoStackTrace = true;


call_stack::call_stack(::ca::application * papp, unsigned int uiSkip) :
   ca(papp)
{

   if(s_bDoStackTrace && uiSkip != 0xffffffffu)
   {

      m_strCallStack = call_stack::get(uiSkip);

   }

}

call_stack::call_stack(const ::call_stack & cs) :
   ca(cs)
{
   
   m_strCallStack = cs.m_strCallStack;

}

vsstring call_stack::get(unsigned int uiSkip)
{

   vsstring str;

   UNREFERENCED_PARAMETER(uiSkip);

   System.eengine().stack_trace(str, uiSkip);

   return str;

}

const char * call_stack::stack_trace() const
{

   return m_strCallStack;

}
