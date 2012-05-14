/*
 Copyright (c) 2002
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 16.01.2002 12:36:26
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 the exception class holding the call stack's information

 exception2 : std::exception

 try {
 }
 catch(exception2& ex) {
   std::cout << ex.trace_call();
 }

*/

#pragma once

#ifdef _WINDOWS

CLASS_DECL_ca BOOL IsWow64();



class CLASS_DECL_ca call_stack
{
public:

   call_stack (unsigned int uiSkip = 3) :
      m_str((uiSkip == 0xffffffff) ? "" : call_stack::get(uiSkip))
   {
   }

   static vsstring get(unsigned int uiSkip = 2)
   {
      vsstring str;
#ifndef _AMD64_
      if(!IsWow64())
      {
         ::exception::engine::stack_trace(str, uiSkip);
      }
#endif
      return str;
   }

   const char * stack_trace() const { return m_str; }
private:
   vsstring m_str;
};


#pragma inline_depth() // restore back the default value





#endif
