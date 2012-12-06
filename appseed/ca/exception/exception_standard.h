/*
 Copyright (c) 2001
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

#ifdef WINDOWS

#include <eh.h>


#define DECLARE_SE_EXCEPTION_CLASS(name) class CLASS_DECL_ca name : virtual public standard_exception \
   { \
    friend class translator; \
   protected: \
   name (::ca::application * papp, EXCEPTION_POINTERS * ppointers) : \
      ca(papp), \
      ::call_stack(papp), \
      ::base_exception(papp), \
      ::standard_exception(papp, ppointers) \
      {} \
   };

#else


#if !defined(MACOS)
#include <ucontext.h>
#include <sys/ucontext.h>
#include <signal.h>
#endif

#endif

class CLASS_DECL_ca standard_exception :
   virtual public base_exception
{
public:


   friend class ::exception::translator;


#ifdef WINDOWS
   EXCEPTION_POINTERS * m_ppointers;
#else
   int            m_iSignal;
   siginfo_t      m_siginfo;
   ucontext_t     m_ucontext;
#endif


#ifdef WINDOWS
   unsigned int         code() const         { return m_ppointers->ExceptionRecord->ExceptionCode; }
   void *               address() const      { return m_ppointers->ExceptionRecord->ExceptionAddress; }
   EXCEPTION_POINTERS * info() const         { return m_ppointers; }
   const char *         name() const         { return ::exception::translator::name(code()); }
   const char *         description() const  { return ::exception::translator::description(code()); }
#else
   unsigned int         code() const         { return m_siginfo.si_code; }
   void *               address() const      { return m_siginfo.si_addr; }
   const siginfo_t *    info() const         { return &m_siginfo; }
   const ucontext_t *   context() const      { return &m_ucontext; }
   const char *         name() const         { return ::exception::translator::name(code()); }
   const char *         description() const  { return ::exception::translator::description(code()); }
#endif


#ifdef WINDOWS
   standard_exception(::ca::application * papp, EXCEPTION_POINTERS * ppointers) :
      ca(papp),
      ::call_stack(papp),
      ::base_exception(papp),
      m_ppointers(ppointers)
   {

      _ASSERTE(ppointers != 0);

   }

   standard_exception(const standard_exception & se) :
      ca(((standard_exception &) se).get_app()),
      ::call_stack(((standard_exception &) se).get_app()),
      ::base_exception(se),
      m_ppointers(se.m_ppointers)
   {

   }

#else
   standard_exception(::ca::application * papp, int iSignal, siginfo_t * psiginfo, void * pc) :
      ca(papp),
      ::call_stack(papp),
      ::base_exception(papp),
      m_iSignal(iSignal),
      m_siginfo(*psiginfo),
      m_ucontext(*(ucontext_t *)pc) { _ASSERTE(psiginfo != 0); }
   standard_exception(const standard_exception& se) :
      ca(se),
      ::call_stack(se),
      ::base_exception(se),
      m_iSignal(se.m_iSignal),
      m_siginfo(se.m_siginfo),
      m_ucontext(se.m_ucontext) {}
#endif
   virtual ~standard_exception()
   {

   }


};

#ifdef LINUX
typedef struct _sig_ucontext {
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
      friend class translator;
   protected:
   #if defined(LINUX) || defined(MACOS)
      standard_access_violation (::ca::application * papp, int signal, siginfo_t * psiginfo, void * pc) :
         ca(papp),
#ifdef _LP64
         ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
#else
         ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
#endif
         ::base_exception(papp),
         ::standard_exception(papp, signal, psiginfo, pc)
         {}

/*       sig_ucontext_t * uc = (sig_ucontext_t *)ucontext;

       void * caller_address = (void *) uc->uc_mcontext.eip; // x86 specific

       str += "signal " + itoa_dup(sig_num) +
                 +" (" + itoa_dup(sig_num) + "), address is "  +
                 itohex_dup(info->si_addr) + " from " + itohex_dup(caller_address) + "\n\n";*/

   #else
      standard_access_violation (::ca::application * papp, EXCEPTION_POINTERS * ppointers) :
         ca(papp),
         ::call_stack(papp),
         ::base_exception(papp),
         ::standard_exception(papp, ppointers)
         {}
   public:
      bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
      ulong_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   #endif
   };

   #ifdef LINUX

   class standard_sigfpe : public standard_exception
   {
      friend class translator;
   protected:
      standard_sigfpe (::ca::application * papp, int iSignal, siginfo_t * psiginfo, void * pc) :
         ca(papp),
#ifdef _LP64
         ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.rip),
#else
         ::call_stack(papp, 3, (void *) ((sig_ucontext_t *) pc)->uc_mcontext.eip),
#endif
         ::base_exception(papp),
          standard_exception(papp, iSignal, psiginfo, pc) {}
   public:
   //   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
     // ulong_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
   };

   #endif


   #ifdef WINDOWS

   class standard_no_memory : public standard_exception
   {
      friend class translator;
   protected:
      standard_no_memory (::ca::application * papp, EXCEPTION_POINTERS * ppointers) :
         ca(papp),
         ::call_stack(papp),
         ::base_exception(papp),
         ::standard_exception(papp, ppointers)
         {}
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

   #endif

} // namespace exception

/*#else


#include "translator.h"
#if !defined(MACOS)
#include <ucontext.h>
#include <sys/ucontext.h>
#endif*/

/*class CLASS_DECL_ca standard_exception :
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
   standard_sigsegv (::ca::application * papp, siginfo_t * psiginfo, void * pc) : ca(papp), standard_exception(papp, psiginfo, pc) {}
public:
   //bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
   //ulong_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};*/

/*class standard_sigfpe : public standard_exception
{
   friend class translator;
protected:
   standard_sigfpe (::ca::application * papp, siginfo_t * psiginfo, void * pc) : ca(papp), standard_exception(papp, psiginfo, pc) {}
public:
//   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
  // ulong_ptr inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

#endif*/

