/*
 Copyright (ca) 2001
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 14:47:20
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 wrapper class for _set_standard_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#if defined(ANDROID)

#elif defined(WINDOWS)

#include <eh.h>


#if OSBIT == 64

#define DEFAULT_SE_EXCEPTION_CALL_STACK_SKIP 3000

#else

#define DEFAULT_SE_EXCEPTION_CALL_STACK_SKIP 0

#endif


#define DECLARE_SE_EXCEPTION_CLASS(name) class CLASS_DECL_AURA name : virtual public standard_exception \
   { \
    friend class translator; \
   protected: \
   name (::aura::application * papp, EXCEPTION_POINTERS * ppointers) : \
      object(papp), \
      ::call_stack(papp, DEFAULT_SE_EXCEPTION_CALL_STACK_SKIP), \
      ::exception::base(papp), \
      ::standard_exception(papp, ppointers) \
      {debug_print(":" #name);} \
   };

#else


#if !defined(APPLEOS)
#include <ucontext.h>
#endif
#include <sys/ucontext.h>
#include <signal.h>

#endif

class CLASS_DECL_AURA standard_exception :
   virtual public ::exception::base
{
public:


   friend class ::exception::translator;


#ifdef WINDOWS
   EXCEPTION_POINTERS * m_ppointers;
#else
   int32_t            m_iSignal;
   void *      m_psiginfo;
#ifndef ANDROID
   ucontext_t     m_ucontext;
#endif
#endif


#ifdef WINDOWS
   uint32_t         code() const         { return m_ppointers->ExceptionRecord->ExceptionCode; }
   void *               address() const      { return m_ppointers->ExceptionRecord->ExceptionAddress; }
   EXCEPTION_POINTERS * info() const         { return m_ppointers; }
   const char *         name() const         { return ::exception::translator::name(code()); }
   const char *         description() const  { return ::exception::translator::description(code()); }
#else
   uint32_t         code() const;
   void *               address() const;
   const void *    info() const;    // siginfo_t *
   const char *         name() const;
   const char *         description() const;
#ifndef ANDROID
   const ucontext_t *   context() const;
#endif
#endif



#ifdef WINDOWS
   standard_exception(::aura::application * papp, EXCEPTION_POINTERS * ppointers) :
      object(papp),
      ::call_stack(papp, DEFAULT_SE_EXCEPTION_CALL_STACK_SKIP),
      ::exception::base(papp),
      m_ppointers(ppointers)
   {

      debug_print(":standard");

      //_ASSERTE(ppointers != 0);

   }


   standard_exception(const standard_exception & se) :
      object(se.get_app()),
      ::call_stack(se.get_app()),
      ::exception::base(se),
      m_ppointers(se.m_ppointers)
   {

      debug_print(":standard(copy)");

   }


#else

   static void * siginfodup(void * psiginfo);
   static void siginfofree(void * psiginfo);
   standard_exception(::aura::application * papp, int32_t iSignal, void * psiginfo, void * pc) :
      object(papp),
      ::call_stack(papp),
      ::exception::base(papp),
      m_iSignal(iSignal),
      m_psiginfo(siginfodup(psiginfo))
#ifndef ANDROID
      ,m_ucontext(*(ucontext_t *)pc)
#endif
       { /*_ASSERTE(psiginfo != 0);*/ }
   standard_exception(const standard_exception& se) :
      ::object(se),
      ::call_stack(se),
      ::exception::base(se),
      m_iSignal(se.m_iSignal),
      m_psiginfo(siginfodup(se.m_psiginfo))
#ifndef ANDROID
      ,m_ucontext(se.m_ucontext)
#endif
       {}
#endif
   virtual ~standard_exception()
   {
#ifndef WINDOWS
      siginfofree(m_psiginfo);
#endif
   }


};

#if defined(LINUX)

typedef struct _sig_ucontext
{
   unsigned long     uc_flags;
   struct ucontext   *uc_link;
   stack_t           uc_stack;
   sigcontext uc_mcontext;
   sigset_t          uc_sigmask;

} sig_ucontext_t;

#endif

namespace exception
{

   class standard_access_violation : public standard_exception
   {
   public:
#if defined(ANDROID)
      
      
      standard_access_violation (::aura::application * papp, int32_t signal, void * psiginfo, void * pc) :
         object(papp),
         ::call_stack(papp),
         ::exception::base(papp),
         ::standard_exception(papp, signal, psiginfo, pc)
      {
         
         debug_print(":standard");
      
      }


#elif defined(LINUX) || defined(APPLEOS) || defined(SOLARIS)
      standard_access_violation (::aura::application * papp, int32_t signal, void * psiginfo, void * pc) :
         object(papp),
#ifdef LINUX
#ifdef _LP64
         ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
#else
         ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
#endif
#else
#ifdef _LP64
      ::call_stack(papp, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__rip),
#else
#ifdef SOLARIS
      ::call_stack(papp, 3, (void *) ((ucontext_t *) pc)->uc_mcontext.gregs[EIP]),
#elif defined(APPLE_IOS)
       ::call_stack(papp, 3, (void *) NULL),
#else
        ::call_stack(papp, 3, (void *) ((ucontext_t *) pc)->uc_mcontext.eip),
#endif
#endif
#endif
         ::exception::base(papp),
         ::standard_exception(papp, signal, psiginfo, pc)
      {
         
         debug_print(":standard");
   
      }

/*       sig_ucontext_t * uc = (sig_ucontext_t *)ucontext;

       void * caller_address = (void *) uc->uc_mcontext.eip; // x86 specific

       str += "signal " + itoa_dup(sig_num) +
                 +" (" + itoa_dup(sig_num) + "), address is "  +
                 itohex_dup(info->si_addr) + " from " + itohex_dup(caller_address) + "\n\n";*/

   #else
      
      
      standard_access_violation (::aura::application * papp, EXCEPTION_POINTERS * ppointers) :
         object(papp),
         ::call_stack(papp, DEFAULT_SE_EXCEPTION_CALL_STACK_SKIP),
         ::exception::base(papp),
         ::standard_exception(papp, ppointers)
      {

         debug_print(":standard");

      }


   public:
      bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      uint_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   #endif
   };
   #if defined(ANDROID)

   class standard_sigfpe : public standard_exception
   {
   public:
      
      
      standard_sigfpe(::aura::application * papp,int32_t iSignal,void * psiginfo,void * pc):
         object(papp),
      ::call_stack(papp),
         ::exception::base(papp),
         standard_exception(papp, iSignal, psiginfo, pc)
      {
         
         debug_print(":sigfpe");
      
      }



   //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
     // uint_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };

   #elif defined(LINUX) || defined(APPLEOS)

   class standard_sigfpe : public standard_exception
   {
   public:
      standard_sigfpe (::aura::application * papp, int32_t iSignal, siginfo_t * psiginfo, void * pc) :
         object(papp),
#ifdef LINUX
#ifdef _LP64
      ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
#else
      ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
#endif
#else
#ifdef _LP64
      ::call_stack(papp, 3, (void *) ((ucontext_t *) pc)->uc_mcontext->__ss.__rip),
#else
#if defined(APPLE_IOS)
       ::call_stack(papp, 3, NULL),
#else
      ::call_stack(papp, 3, (void *) ((ucontext_t *) pc)->uc_mcontext.eip),
#endif
#endif
#endif
         ::exception::base(papp),
         standard_exception(papp, iSignal, psiginfo, pc)
      {
         
         debug_print(":sigfpe");
      
      }


   public:
   //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
     // uint_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };

   #endif


   #ifdef WINDOWS

   class standard_no_memory : public standard_exception
   {
   public:
      
      
      standard_no_memory (::aura::application * papp, EXCEPTION_POINTERS * ppointers) :
         object(papp),
         ::call_stack(papp, DEFAULT_SE_EXCEPTION_CALL_STACK_SKIP),
         ::exception::base(papp),
         ::standard_exception(papp, ppointers)
      {

         debug_print(":nomem");

      }

   public:
      size_t mem_size() const { return info()->ExceptionRecord->ExceptionInformation [0]; }
   };

   //   DECLARE_EXCEPTION_CLASS(standard_no_memory)
   //   DECLARE_EXCEPTION_CLASS(standard_access_violation)
   DECLARE_SE_EXCEPTION_CLASS(standard_datatype_misalignment)
   DECLARE_SE_EXCEPTION_CLASS(standard_breakpoint)
   DECLARE_SE_EXCEPTION_CLASS(standard_single_step)
   DECLARE_SE_EXCEPTION_CLASS(standard_array_bounds_exceeded)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_denormal_operand)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_divide_by_zero)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_inexact_result)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_invalid_operation)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_overflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_stack_check)
   DECLARE_SE_EXCEPTION_CLASS(standard_flt_underflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_int_divide_by_zero)
   DECLARE_SE_EXCEPTION_CLASS(standard_int_overflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_priv_instruction)
   DECLARE_SE_EXCEPTION_CLASS(standard_in_page_error)
   DECLARE_SE_EXCEPTION_CLASS(standard_illegal_instruction)
   DECLARE_SE_EXCEPTION_CLASS(standard_noncontinuable_exception)
   DECLARE_SE_EXCEPTION_CLASS(standard_stack_overflow)
   DECLARE_SE_EXCEPTION_CLASS(standard_invalid_disposition)
   DECLARE_SE_EXCEPTION_CLASS(standard_guard_page)
   DECLARE_SE_EXCEPTION_CLASS(standard_invalid_handle)
   DECLARE_SE_EXCEPTION_CLASS(standard_microsoft_cpp)
   DECLARE_SE_EXCEPTION_CLASS(standard_winrt_originate_error)

   #endif

} // namespace exception

/*#else


#include "translator.h"
#if !defined(APPLEOS)
#include <ucontext.h>
#include <sys/ucontext.h>
#endif*/

/*class CLASS_DECL_AURA standard_exception :
   public bastandard_exception
{
public:
   friend class translator;


   ~standard_exception() {}

protected:

private:
};*/

/*class standard_sigsegv : public standard_exception
{
   friend class translator;
protected:
   standard_sigsegv (::aura::application * papp, siginfo_t * psiginfo, void * pc) : object(papp), standard_exception(papp, psiginfo, pc) {}
public:
   //bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
   //uint_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};*/

/*class standard_sigfpe : public standard_exception
{
   friend class translator;
protected:
   standard_sigfpe (::aura::application * papp, siginfo_t * psiginfo, void * pc) : object(papp), standard_exception(papp, psiginfo, pc) {}
public:
//   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
  // uint_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

#endif*/

