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

 wrapper class for _set_se_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#ifdef _WINDOWS

#include <eh.h>
#include "se_translator.h"

#define DECLARE_SE_EXCEPTION_CLASS(name) class CLASS_DECL_ca name : public se_exception \
   { \
    friend class se_translator; \
   protected: \
   name (::ca::application * papp, EXCEPTION_POINTERS * ppointers) : ca(papp), se_exception(papp, ppointers) {} \
   };

class CLASS_DECL_ca se_exception :
   public base_exception
{
public:
   friend class se_translator;

   unsigned int         code() const         { return m_ppointers->ExceptionRecord->ExceptionCode; }
   void *               address() const      { return m_ppointers->ExceptionRecord->ExceptionAddress; }
   EXCEPTION_POINTERS * info() const         { return m_ppointers; }
   const char *         name() const         { return se_translator::name(code()); }
   const char *         description() const  { return se_translator::description(code()); }

   ~se_exception() {}

protected:
   se_exception(::ca::application * papp, EXCEPTION_POINTERS * ppointers) : ca(papp), m_ppointers(ppointers) { _ASSERTE(ppointers != 0); }
   se_exception(const se_exception& se) : ca(((se_exception &) se).get_app()), m_ppointers(se.m_ppointers) {}

private:
   EXCEPTION_POINTERS * m_ppointers;
};

class se_access_violation : public se_exception
{
   friend class se_translator;
protected:
   se_access_violation (::ca::application * papp, EXCEPTION_POINTERS * ppointers) : ca(papp), se_exception(papp, ppointers) {}
public:
   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
   ULONG_PTR inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

class se_no_memory : public se_exception
{
   friend class se_translator;
protected:
   se_no_memory (::ca::application * papp, EXCEPTION_POINTERS * ppointers) : ca(papp), se_exception(papp, ppointers) {}
public:
   size_t mem_size() const { return info()->ExceptionRecord->ExceptionInformation [0]; }
};

//   DECLARE_EXCEPTION_CLASS(se_no_memory)
//   DECLARE_EXCEPTION_CLASS(se_access_violation)
DECLARE_SE_EXCEPTION_CLASS(se_datatype_misalignment)
DECLARE_SE_EXCEPTION_CLASS(se_breakpoint)
DECLARE_SE_EXCEPTION_CLASS(se_single_step)
DECLARE_SE_EXCEPTION_CLASS(se_array_bounds_exceeded)
DECLARE_SE_EXCEPTION_CLASS(se_flt_denormal_operand)
DECLARE_SE_EXCEPTION_CLASS(se_flt_divide_by_zero)
DECLARE_SE_EXCEPTION_CLASS(se_flt_inexact_result)
DECLARE_SE_EXCEPTION_CLASS(se_flt_invalid_operation)
DECLARE_SE_EXCEPTION_CLASS(se_flt_overflow)
DECLARE_SE_EXCEPTION_CLASS(se_flt_stack_check)
DECLARE_SE_EXCEPTION_CLASS(se_flt_underflow)
DECLARE_SE_EXCEPTION_CLASS(se_int_divide_by_zero)
DECLARE_SE_EXCEPTION_CLASS(se_int_overflow)
DECLARE_SE_EXCEPTION_CLASS(se_priv_instruction)
DECLARE_SE_EXCEPTION_CLASS(se_in_page_error)
DECLARE_SE_EXCEPTION_CLASS(se_illegal_instruction)
DECLARE_SE_EXCEPTION_CLASS(se_noncontinuable_exception)
DECLARE_SE_EXCEPTION_CLASS(se_stack_overflow)
DECLARE_SE_EXCEPTION_CLASS(se_invalid_disposition)
DECLARE_SE_EXCEPTION_CLASS(se_guard_page)
DECLARE_SE_EXCEPTION_CLASS(se_invalid_handle)
DECLARE_SE_EXCEPTION_CLASS(se_microsoft_cpp)

#else


#include "se_translator.h"
#if !defined(MACOS)
#include <ucontext.h>
#include <sys/ucontext.h>
#endif

class CLASS_DECL_ca se_exception :
   public base_exception
{
public:
   friend class se_translator;

   const siginfo_t * info() const         { return &m_siginfo; }
   const ucontext_t * context() const         { return &m_ucontext; }

   ~se_exception() {}

protected:
   se_exception(::ca::application * papp, siginfo_t * psiginfo, void * pc) : ca(papp), m_siginfo(*psiginfo), m_ucontext(*(ucontext_t *)pc) { _ASSERTE(psiginfo != 0); }
   se_exception(const se_exception& se) : ca(((se_exception &) se).get_app()), m_siginfo(se.m_siginfo), m_ucontext(se.m_ucontext) {}

private:
   siginfo_t      m_siginfo;
   ucontext_t     m_ucontext;
};

class se_sigsegv : public se_exception
{
   friend class se_translator;
protected:
   se_sigsegv (::ca::application * papp, siginfo_t * psiginfo, void * pc) : ca(papp), se_exception(papp, psiginfo, pc) {}
public:
   //bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
   //ULONG_PTR inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

class se_sigfpe : public se_exception
{
   friend class se_translator;
protected:
   se_sigfpe (::ca::application * papp, siginfo_t * psiginfo, void * pc) : ca(papp), se_exception(papp, psiginfo, pc) {}
public:
//   bool is_read_op() const { return !info()->ExceptionRecord->ExceptionInformation [0]; }
  // ULONG_PTR inaccessible_address() const { return info()->ExceptionRecord->ExceptionInformation [1]; }
};

#endif
