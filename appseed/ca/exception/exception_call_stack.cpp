#include "framework.h"


bool call_stack::s_bDoStackTrace = false;


call_stack::call_stack (unsigned int uiSkip)
{

   if(s_bDoStackTrace && uiSkip != 0xffffffffu)
   {

      m_str = call_stack::get(uiSkip);

   }

}

vsstring call_stack::get(unsigned int uiSkip)
{

   vsstring str;

#ifndef AMD64

   UNREFERENCED_PARAMETER(uiSkip);

   ::exception::engine::stack_trace(str, uiSkip);

#endif

   return str;

}

const char * call_stack::stack_trace() const
{

   return m_str;

}
