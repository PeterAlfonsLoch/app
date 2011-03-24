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

#include "sym_engine.h"

namespace
{
   // the mixin class for exception
   struct call_stack
   {   
      call_stack (unsigned skip = 3)
         : m_s((skip == unsigned(-1)) ? "" : call_stack::get(skip))      
      {}
      static string get(unsigned skip = 2)
      {
         std::stringstream ss(std::ios::out);      
         sym_engine::stack_trace(ss, skip);         
         return ss.str();      
      }
      const char * stack_trace() const { return m_s; }
    private:
      string m_s;
   };
}

#pragma inline_depth(0) // must disable inlining due to using skip value
class exception2 : public std::exception, public call_stack 
{
  public:
     exception2(const __exString& s, unsigned skip = 4 /* -1 for disable call stack*/)
        : std::exception(s), call_stack(skip)      
     {}
};

#pragma inline_depth() // restore back the default value

