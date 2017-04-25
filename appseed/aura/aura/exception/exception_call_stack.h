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


#define CALL_STACK_DEFAULT_SKIP_TRIGGER ((uint32_t) -2)

#define SKIP_CALL_STACK ((uint32_t) -1)


#if defined(APPLE_IOS)

#define CALL_STACK_DEFAULT_SKIP 3

#elif defined(VSNORD)

#define CALL_STACK_DEFAULT_SKIP 4

#else

#define CALL_STACK_DEFAULT_SKIP 3

#endif

class CLASS_DECL_AURA call_stack :
   virtual public object
{
public:

   const char *      m_pszCallStack;

   static bool s_bDoStackTrace;


   /* -1 for disable call stack*/

#if defined(LINUX) || defined(APPLEOS) || defined(SOLARIS) || defined(VSNORD)

   void * m_caller_address;

   call_stack(::aura::application * papp, uint32_t uiSkip = CALL_STACK_DEFAULT_SKIP_TRIGGER, void * caller_address = NULL);

#else

   call_stack(::aura::application * papp, uint32_t uiSkip = CALL_STACK_DEFAULT_SKIP_TRIGGER);

#endif

   call_stack(const ::call_stack & cs);
   virtual ~call_stack();

   const char * get_dup(uint32_t uiSkip = CALL_STACK_DEFAULT_SKIP_TRIGGER);

   const char * stack_trace() const;

};


