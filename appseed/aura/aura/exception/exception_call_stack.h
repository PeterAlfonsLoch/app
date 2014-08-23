/*
 Copyright (ca) 2002
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

 exception2 : std_exception

 try {
 }
 catch(exception2& ex) {
   std_cout << ex.trace_call();
 }

*/
#pragma once


class CLASS_DECL_AURA call_stack :
   virtual public element
{
public:

   string m_strCallStack;

   static bool s_bDoStackTrace;

#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS)

   void * m_caller_address;

   call_stack(sp(::aura::application) papp, uint32_t uiSkip = 3, void * caller_address = NULL);

#else

   call_stack(sp(::aura::application) papp, uint32_t uiSkip = 3);

#endif

   call_stack(const ::call_stack & cs);

   string get(uint32_t uiSkip = 2);

   const char * stack_trace() const;

};


