/*
Copyright (ca) 2001
Author: Konstantin Boukreev
E-mail: konstantin@mail.primorye.ru
Created: 25.12.2001 15:18:21
Version: 1.0.0

Permission to use, copy, modify, distribute and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation.  Konstantin Boukreev makes no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.

*/
#include "framework.h"


#ifdef WINDOWSEX

// 0x40010005 control C
// 0xc0000135 Dll Not Found
// 0xc0000142 Dll Initialization failed
// 0xc06d007e Module Not Found
// 0xc06d007f Procedure Not Found
// 0x40010008 control-Break

#define EXCEPTION_NO_MEMORY STATUS_NO_MEMORY

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(
   LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
{
   UNREFERENCED_PARAMETER(lpTopLevelExceptionFilter);
   return NULL;
}

bool PreventSetUnhandledExceptionFilter()
{
   /*HMODULE hKernel32 = LoadLibrary("kernel32.dll");
   if (hKernel32 == NULL) return FALSE;
   void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
   if(pOrgEntry ==  NULL) return FALSE;
   uchar newJump[ 100 ];
   uint32_t dwOrgEntryAddr = (uint32_t) pOrgEntry;
   dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far
   void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
   uint32_t dwNewEntryAddr = (uint32_t) pNewFunc;
   uint32_t dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
   newJump[ 0 ] = 0xE9;  // JMP absolute
   memcpy(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));
   SIZE_T bytesWritten;
   bool bRet = WriteProcessMemory(GetCurrentProcess(),
   pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
   return bRet;*/
   return FALSE;
}

#endif


namespace exception
{


   translator::translator()
   {
      m_bSet = false;
   }

   translator::~translator()
   {
   }

#ifdef WINDOWS
   void __cdecl translator::filter2(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
   {
      if(g_bExiting)
         return;
      UNREFERENCED_PARAMETER(uiCode);
      sp(::base::application) papp = get_thread_app();
      switch (ppointers->ExceptionRecord->ExceptionCode)
      {
#ifdef WINDOWSEX
      case EXCEPTION_NO_MEMORY:                 throw standard_no_memory(papp, ppointers);                  break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:          throw standard_access_violation(papp, ppointers);           break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:     throw standard_datatype_misalignment(papp, ppointers);      break;
      case EXCEPTION_BREAKPOINT:                throw standard_breakpoint(papp, ppointers);                 break;
      case EXCEPTION_SINGLE_STEP:               throw standard_single_step(papp, ppointers);                break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     throw standard_array_bounds_exceeded(papp, ppointers);      break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:      throw standard_flt_denormal_operand(papp, ppointers);       break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        throw standard_flt_divide_by_zero(papp, ppointers);         break;
      case EXCEPTION_FLT_INEXACT_RESULT:        throw standard_flt_inexact_result(papp, ppointers);         break;
      case EXCEPTION_FLT_INVALID_OPERATION:     throw standard_flt_invalid_operation(papp, ppointers);      break;
      case EXCEPTION_FLT_OVERFLOW:              throw standard_flt_overflow(papp, ppointers);               break;
      case EXCEPTION_FLT_STACK_CHECK:           throw standard_flt_stack_check(papp, ppointers);            break;
      case EXCEPTION_FLT_UNDERFLOW:             throw standard_flt_underflow(papp, ppointers);              break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:        throw standard_int_divide_by_zero(papp, ppointers);         break;
      case EXCEPTION_INT_OVERFLOW:              throw standard_int_overflow(papp, ppointers);               break;
      case EXCEPTION_PRIV_INSTRUCTION:          throw standard_priv_instruction(papp, ppointers);           break;
      case EXCEPTION_IN_PAGE_ERROR:             throw standard_in_page_error(papp, ppointers);              break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:       throw standard_illegal_instruction(papp, ppointers);        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  throw standard_noncontinuable_exception(papp, ppointers);   break;
      case EXCEPTION_STACK_OVERFLOW:            throw standard_stack_overflow(papp, ppointers);             break;
      case EXCEPTION_INVALID_DISPOSITION:       throw standard_invalid_disposition(papp, ppointers);        break;
      case EXCEPTION_GUARD_PAGE:                throw standard_guard_page(papp, ppointers);                 break;
      case EXCEPTION_INVALID_HANDLE:            throw standard_invalid_handle(papp, ppointers);             break;
      case 0xE06D7363:                          throw standard_microsoft_cpp(papp, ppointers);              break;
      default:                                  throw standard_exception(papp, ppointers);                  break;
      };
   }

#endif
   
#ifdef APPLEOS
   
   void InstallUncaughtExceptionHandler();

#endif

   bool translator::attach()
   {
      if(!m_bSet)
      {
#ifdef WINDOWS
         m_pfn = _set_se_translator(&translator::filter2);
         //m_pfn = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) GetThunk());
         //PreventSetUnhandledExceptionFilter();
         //EnforceFilter(true);
#else
         
#ifdef APPLEOS
         void InstallUncaughtExceptionHandler();
#endif

         memset(&m_saSeg, 0, sizeof(m_saSeg));
         sigemptyset(&m_saSeg.sa_mask);
         //sigaddset(&m_saSeg.sa_mask, SIGSEGV);
         //m_saSeg.sa_flags = SA_NODEFER | SA_SIGINFO;
         m_saSeg.sa_flags = SA_SIGINFO;
         m_saSeg.sa_sigaction = &translator::filter_sigsegv;
         sigaction(SIGSEGV, &m_saSeg, &m_saSegOld);

         memset(&m_saFpe, 0, sizeof(m_saFpe));
         sigemptyset(&m_saFpe.sa_mask);
         //sigaddset(&m_saFpe.sa_mask, SIGFPE);
         //m_saSeg.sa_flags = SA_NODEFER | SA_SIGINFO;
         m_saSeg.sa_flags = SA_SIGINFO;
         m_saFpe.sa_sigaction = &translator::filter_sigfpe;
         sigaction(SIGFPE, &m_saFpe, &m_saFpeOld);

         memset(&m_saPipe, 0, sizeof(m_saPipe));
         sigemptyset(&m_saPipe.sa_mask);
         //sigaddset(&m_saPipe.sa_mask, SIGPIPE);
         //m_saSeg.sa_flags = SA_NODEFER | SA_SIGINFO;
         m_saSeg.sa_flags = SA_SIGINFO;
         m_saPipe.sa_sigaction = &translator::filter_sigpipe;
         sigaction(SIGPIPE, &m_saPipe, &m_saPipeOld);


#endif
         m_bSet = true;
         return true;
      }
      else
      {
         return false;
      }
   }



   bool translator::detach()
   {
      if(m_bSet)
      {
#ifdef WINDOWS
         _set_se_translator(m_pfn);
#else
         sigaction(SIGSEGV, &m_saSegOld, NULL);
         sigaction(SIGFPE, &m_saFpeOld, NULL);
#endif
         m_bSet = false;
         return true;
      }
      else
      {
         return false;
      }
   }
#ifdef WINDOWS
   void translator::filter(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
   {
      UNREFERENCED_PARAMETER(uiCode);
      switch (ppointers->ExceptionRecord->ExceptionCode)
      {
#ifdef WINDOWSEX
      case EXCEPTION_NO_MEMORY:                 throw standard_no_memory(get_app(), ppointers);                  break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:          throw standard_access_violation(get_app(), ppointers);           break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:     throw standard_datatype_misalignment(get_app(), ppointers);      break;
      case EXCEPTION_BREAKPOINT:                throw standard_breakpoint(get_app(), ppointers);                 break;
      case EXCEPTION_SINGLE_STEP:               throw standard_single_step(get_app(), ppointers);                break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     throw standard_array_bounds_exceeded(get_app(), ppointers);      break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:      throw standard_flt_denormal_operand(get_app(), ppointers);       break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        throw standard_flt_divide_by_zero(get_app(), ppointers);         break;
      case EXCEPTION_FLT_INEXACT_RESULT:        throw standard_flt_inexact_result(get_app(), ppointers);         break;
      case EXCEPTION_FLT_INVALID_OPERATION:     throw standard_flt_invalid_operation(get_app(), ppointers);      break;
      case EXCEPTION_FLT_OVERFLOW:              throw standard_flt_overflow(get_app(), ppointers);               break;
      case EXCEPTION_FLT_STACK_CHECK:           throw standard_flt_stack_check(get_app(), ppointers);            break;
      case EXCEPTION_FLT_UNDERFLOW:             throw standard_flt_underflow(get_app(), ppointers);              break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:        throw standard_int_divide_by_zero(get_app(), ppointers);         break;
      case EXCEPTION_INT_OVERFLOW:              throw standard_int_overflow(get_app(), ppointers);               break;
      case EXCEPTION_PRIV_INSTRUCTION:          throw standard_priv_instruction(get_app(), ppointers);           break;
      case EXCEPTION_IN_PAGE_ERROR:             throw standard_in_page_error(get_app(), ppointers);              break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:       throw standard_illegal_instruction(get_app(), ppointers);        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  throw standard_noncontinuable_exception(get_app(), ppointers);   break;
      case EXCEPTION_STACK_OVERFLOW:            throw standard_stack_overflow(get_app(), ppointers);             break;
      case EXCEPTION_INVALID_DISPOSITION:       throw standard_invalid_disposition(get_app(), ppointers);        break;
      case EXCEPTION_GUARD_PAGE:                throw standard_guard_page(get_app(), ppointers);                 break;
      case EXCEPTION_INVALID_HANDLE:            throw standard_invalid_handle(get_app(), ppointers);             break;
      case 0xE06D7363:                          throw standard_microsoft_cpp(get_app(), ppointers);              break;
      default:                                  throw standard_exception(get_app(), ppointers);                  break;
      };
   }

   string translator::name(uint32_t uiCode)
   {

      string str;

      switch (uiCode)
      {
#ifdef WINDOWSEX
      case EXCEPTION_NO_MEMORY:                 str = "No Memory";                  break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:          str = "Access Violation";           break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:     str = "Datatype Misalignment";      break;
      case EXCEPTION_BREAKPOINT:                str = "Breakpoint";                 break;
      case EXCEPTION_SINGLE_STEP:               str = "Single Step";                break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     str = "Array Bounds Exceeded";      break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:      str = "Float Denormal Operand";     break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:        str = "Float Divide by Zero";       break;
      case EXCEPTION_FLT_INEXACT_RESULT:        str = "Float Inexact Result";       break;
      case EXCEPTION_FLT_INVALID_OPERATION:     str = "Float Invalid Operation";    break;
      case EXCEPTION_FLT_OVERFLOW:              str = "Float Overflow";             break;
      case EXCEPTION_FLT_STACK_CHECK:           str = "Float Stack Check";          break;
      case EXCEPTION_FLT_UNDERFLOW:             str = "Float Underflow";            break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:        str = "Integer Divide by Zero";     break;
      case EXCEPTION_INT_OVERFLOW:              str = "Integer Overflow";           break;
      case EXCEPTION_PRIV_INSTRUCTION:          str = "Privileged Instruction";     break;
      case EXCEPTION_IN_PAGE_ERROR:             str = "In Page Error";              break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:       str = "Illegal Instruction";        break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:  str = "Noncontinuable Exception";   break;
      case EXCEPTION_STACK_OVERFLOW:            str = "Stack Overflow";             break;
      case EXCEPTION_INVALID_DISPOSITION:       str = "Invalid Disposition";        break;
      case EXCEPTION_GUARD_PAGE:                str = "Guard Page";                 break;
      case EXCEPTION_INVALID_HANDLE:            str = "Invalid Handle";             break;
      case 0xE06D7363:                          str = "Microsoft C++ Exception";    break;
      default:
         str = "0x";
         str += hex::lower_from(uiCode);
         break;
      };

      return str;

   }

   string translator::description(uint32_t uiCode)
   {

      string str;

      switch(uiCode)
      {
#ifdef WINDOWSEX
      case EXCEPTION_NO_MEMORY:
         str = "The allocation attempt failed because of a lack of available primitive::memory or heap corruption.";
         break;
#endif
      case EXCEPTION_ACCESS_VIOLATION:
         str = "The thread attempted to read from or write to a virtual address for which it does not have the appropriate access";
         break;
      case EXCEPTION_DATATYPE_MISALIGNMENT:
         str = "The thread attempted to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries, 32-bit values on 4-byte boundaries, and so on";
         break;
      case EXCEPTION_BREAKPOINT:
         str = "A breakpoint was encountered";
         break;
      case EXCEPTION_SINGLE_STEP:
         str = "A trace trap or other single-instruction mechanism signaled that one instruction has been executed";
         break;
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
         str = "The thread attempted to access an bastandard_array element that is out of bounds, and the underlying hardware supports bounds checking";
         break;
      case EXCEPTION_FLT_DENORMAL_OPERAND:
         str = "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value";
         break;
      case EXCEPTION_FLT_DIVIDE_BY_ZERO:
         str = "The thread attempted to divide a floating-point value by a floating-point divisor of zero";
         break;
      case EXCEPTION_FLT_INEXACT_RESULT:
         str = "The result of a floating-point operation cannot be represented exactly as a decimal fraction";
         break;
      case EXCEPTION_FLT_INVALID_OPERATION:
         str = "This exception represents any floating-point exception not included in this list";
         break;
      case EXCEPTION_FLT_OVERFLOW:
         str = "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type";
         break;
      case EXCEPTION_FLT_STACK_CHECK:
         str = "The stack overflowed or underflowed as the result of a floating-point operation";
         break;
      case EXCEPTION_FLT_UNDERFLOW:
         str = "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type";
         break;
      case EXCEPTION_INT_DIVIDE_BY_ZERO:
         str = "The thread attempted to divide an integer value by an integer divisor of zero";
         break;
      case EXCEPTION_INT_OVERFLOW:
         str = "The result of an integer operation caused a carry out of the most significant bit of the result";
         break;
      case EXCEPTION_PRIV_INSTRUCTION:
         str = "The thread attempted to execute an instruction whose operation is not allowed in the current machine mode";
         break;
      case EXCEPTION_IN_PAGE_ERROR:
         str = "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network";
         break;
      case EXCEPTION_ILLEGAL_INSTRUCTION:
         str = "The thread tried to execute an invalid instruction";
         break;
      case EXCEPTION_NONCONTINUABLE_EXCEPTION:
         str = "The thread attempted to continue execution after a noncontinuable exception occurred";
         break;
      case EXCEPTION_STACK_OVERFLOW:
         str = "The thread used up its stack";
         break;
      case EXCEPTION_INVALID_DISPOSITION:
         str = "An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception";
         break;
      case EXCEPTION_GUARD_PAGE:
         str = "Guard Page Exception";
         break;
      case EXCEPTION_INVALID_HANDLE:
         str = "Invalid Handle Exception";
         break;
      case 0xE06D7363:
         str = "Microsoft C++ Exception";
         break;
      default:
         str = "Unknown Exception (Not currently known by core platform)";
         break;
      };

      return str;

   }
#else

   void translator::filter_sigsegv(int32_t signal, siginfo_t * psiginfo, void * pc)
   {

      sigset_t set;
      sigemptyset(&set);
      sigaddset(&set, SIGSEGV);
      pthread_sigmask(SIG_UNBLOCK, &set, NULL);

      throw standard_access_violation(NULL, signal, psiginfo, pc);

   }

   void translator::filter_sigfpe(int32_t signal, siginfo_t * psiginfo, void * pc)
   {

      //sigset_t set;
      //sigemptyset(&set);
      //sigaddset(&set, SIGSEGV);
      //sigprocmask(SIG_UNBLOCK, &set, NULL);

      throw standard_sigfpe(NULL, signal, psiginfo, pc);

   }


   void translator::filter_sigpipe(int32_t signal, siginfo_t * psiginfo, void * pc)
   {

      sigset_t set;
      sigemptyset(&set);
      sigaddset(&set, SIGSEGV);
      sigprocmask(SIG_UNBLOCK, &set, NULL);

      //throw standard_sigfpe(NULL, signal, psiginfo, pc);

   }


#endif
   /*

   the_standard_translator the_standard_translator::s_thesetranslator;

   the_standard_translator::the_standard_translator()
   {
   attach();
   }

   the_standard_translator::~the_standard_translator()
   {
   detach();
   }
   */


} // namespace exception


CLASS_DECL_BASE bool g_bExiting;



