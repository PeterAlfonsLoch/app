/*
 Copyright (c) 2001
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

#include "StdAfx.h"
#include "se_translator.h"

#ifdef _WINDOWS

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

  BOOL PreventSetUnhandledExceptionFilter()
  {
    /*HMODULE hKernel32 = LoadLibrary("kernel32.dll");
    if (hKernel32 == NULL) return FALSE;
    void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
    if(pOrgEntry ==  NULL) return FALSE;
    unsigned char newJump[ 100 ];
    DWORD dwOrgEntryAddr = (DWORD) pOrgEntry;
    dwOrgEntryAddr += 5; // add 5 for 5 op-codes for jmp far
    void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
    DWORD dwNewEntryAddr = (DWORD) pNewFunc;
    DWORD dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
    newJump[ 0 ] = 0xE9;  // JMP absolute
    memcpy(&newJump[ 1 ], &dwRelativeAddr, sizeof(pNewFunc));
    SIZE_T bytesWritten;
    BOOL bRet = WriteProcessMemory(GetCurrentProcess(),
      pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
    return bRet;*/
     return FALSE;
  }

#endif

se_translator::se_translator()
{
   m_bSet = false;
}

se_translator::~se_translator()
{
}

#ifdef _WINDOWS
void __cdecl se_translator::filter2(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   ::ca::application * papp = NULL;
   switch (ppointers->ExceptionRecord->ExceptionCode)
   {
   case EXCEPTION_NO_MEMORY:                 throw se_no_memory(papp, ppointers);                  break;
   case EXCEPTION_ACCESS_VIOLATION:          throw se_access_violation(papp, ppointers);           break;
   case EXCEPTION_DATATYPE_MISALIGNMENT:     throw se_datatype_misalignment(papp, ppointers);      break;
   case EXCEPTION_BREAKPOINT:                throw se_breakpoint(papp, ppointers);                 break;
   case EXCEPTION_SINGLE_STEP:               throw se_single_step(papp, ppointers);                break;
   case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     throw se_array_bounds_exceeded(papp, ppointers);      break;
   case EXCEPTION_FLT_DENORMAL_OPERAND:      throw se_flt_denormal_operand(papp, ppointers);       break;
   case EXCEPTION_FLT_DIVIDE_BY_ZERO:        throw se_flt_divide_by_zero(papp, ppointers);         break;
   case EXCEPTION_FLT_INEXACT_RESULT:        throw se_flt_inexact_result(papp, ppointers);         break;
   case EXCEPTION_FLT_INVALID_OPERATION:     throw se_flt_invalid_operation(papp, ppointers);      break;
   case EXCEPTION_FLT_OVERFLOW:              throw se_flt_overflow(papp, ppointers);               break;
   case EXCEPTION_FLT_STACK_CHECK:           throw se_flt_stack_check(papp, ppointers);            break;
   case EXCEPTION_FLT_UNDERFLOW:             throw se_flt_underflow(papp, ppointers);              break;
   case EXCEPTION_INT_DIVIDE_BY_ZERO:        throw se_int_divide_by_zero(papp, ppointers);         break;
   case EXCEPTION_INT_OVERFLOW:              throw se_int_overflow(papp, ppointers);               break;
   case EXCEPTION_PRIV_INSTRUCTION:          throw se_priv_instruction(papp, ppointers);           break;
   case EXCEPTION_IN_PAGE_ERROR:             throw se_in_page_error(papp, ppointers);              break;
   case EXCEPTION_ILLEGAL_INSTRUCTION:       throw se_illegal_instruction(papp, ppointers);        break;
   case EXCEPTION_NONCONTINUABLE_EXCEPTION:  throw se_noncontinuable_exception(papp, ppointers);   break;
   case EXCEPTION_STACK_OVERFLOW:            throw se_stack_overflow(papp, ppointers);             break;
   case EXCEPTION_INVALID_DISPOSITION:       throw se_invalid_disposition(papp, ppointers);        break;
   case EXCEPTION_GUARD_PAGE:                throw se_guard_page(papp, ppointers);                 break;
   case EXCEPTION_INVALID_HANDLE:            throw se_invalid_handle(papp, ppointers);             break;
   case 0xE06D7363:                          throw se_microsoft_cpp(papp, ppointers);              break;
   default:                                  throw se_exception(papp, ppointers);                  break;
   };
}

#endif

bool se_translator::attach()
{
   if(!m_bSet)
   {
      #ifdef _WINDOWS
      m_pfn = _set_se_translator(&se_translator::filter2);
      //m_pfn = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) GetThunk());
      //PreventSetUnhandledExceptionFilter();
      //EnforceFilter(true);
      #else

      struct sigaction sa;

      sa.sa_flags = SA_NODEFER;
      sigemptyset(&sa.sa_mask);
      sigaddset(&sa.sa_mask, SISGSEGV);

      sa.sa_action = &se_translator::filter_sigsegv;
      sigaction(SIGSEGV, &sa, NULL);

      sa.sa_action = &se_translator::filter_sigfpe;
      sigaction(SIGFPE, &sa, NULL);



      #endif
      m_bSet = true;
      return true;
   }
   else
   {
      return false;
   }
}



bool se_translator::detach()
{
   if(m_bSet)
   {
      _set_se_translator(m_pfn);
      m_bSet = false;
      return true;
   }
   else
   {
      return false;
   }
}
#ifdef WINDOWS
void se_translator::filter(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   switch (ppointers->ExceptionRecord->ExceptionCode)
   {
   case EXCEPTION_NO_MEMORY:                 throw se_no_memory(get_app(), ppointers);                  break;
   case EXCEPTION_ACCESS_VIOLATION:          throw se_access_violation(get_app(), ppointers);           break;
   case EXCEPTION_DATATYPE_MISALIGNMENT:     throw se_datatype_misalignment(get_app(), ppointers);      break;
   case EXCEPTION_BREAKPOINT:                throw se_breakpoint(get_app(), ppointers);                 break;
   case EXCEPTION_SINGLE_STEP:               throw se_single_step(get_app(), ppointers);                break;
   case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:     throw se_array_bounds_exceeded(get_app(), ppointers);      break;
   case EXCEPTION_FLT_DENORMAL_OPERAND:      throw se_flt_denormal_operand(get_app(), ppointers);       break;
   case EXCEPTION_FLT_DIVIDE_BY_ZERO:        throw se_flt_divide_by_zero(get_app(), ppointers);         break;
   case EXCEPTION_FLT_INEXACT_RESULT:        throw se_flt_inexact_result(get_app(), ppointers);         break;
   case EXCEPTION_FLT_INVALID_OPERATION:     throw se_flt_invalid_operation(get_app(), ppointers);      break;
   case EXCEPTION_FLT_OVERFLOW:              throw se_flt_overflow(get_app(), ppointers);               break;
   case EXCEPTION_FLT_STACK_CHECK:           throw se_flt_stack_check(get_app(), ppointers);            break;
   case EXCEPTION_FLT_UNDERFLOW:             throw se_flt_underflow(get_app(), ppointers);              break;
   case EXCEPTION_INT_DIVIDE_BY_ZERO:        throw se_int_divide_by_zero(get_app(), ppointers);         break;
   case EXCEPTION_INT_OVERFLOW:              throw se_int_overflow(get_app(), ppointers);               break;
   case EXCEPTION_PRIV_INSTRUCTION:          throw se_priv_instruction(get_app(), ppointers);           break;
   case EXCEPTION_IN_PAGE_ERROR:             throw se_in_page_error(get_app(), ppointers);              break;
   case EXCEPTION_ILLEGAL_INSTRUCTION:       throw se_illegal_instruction(get_app(), ppointers);        break;
   case EXCEPTION_NONCONTINUABLE_EXCEPTION:  throw se_noncontinuable_exception(get_app(), ppointers);   break;
   case EXCEPTION_STACK_OVERFLOW:            throw se_stack_overflow(get_app(), ppointers);             break;
   case EXCEPTION_INVALID_DISPOSITION:       throw se_invalid_disposition(get_app(), ppointers);        break;
   case EXCEPTION_GUARD_PAGE:                throw se_guard_page(get_app(), ppointers);                 break;
   case EXCEPTION_INVALID_HANDLE:            throw se_invalid_handle(get_app(), ppointers);             break;
   case 0xE06D7363:                          throw se_microsoft_cpp(get_app(), ppointers);              break;
   default:                                  throw se_exception(get_app(), ppointers);                  break;
   };
}

vsstring se_translator::name(unsigned int uiCode)
{

   vsstring str;

   switch (uiCode)
   {
   case EXCEPTION_NO_MEMORY:                 str = "No Memory";                  break;
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
      str += itohexpad_dup(uiCode, 8);
      break;
   };

   return str;

}

vsstring se_translator::description(unsigned int uiCode)
{
   
   vsstring str;

   switch(uiCode)
   {
   case EXCEPTION_NO_MEMORY:
      str = "The allocation attempt failed because of a lack of available primitive::memory or heap corruption.";
      break;
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
      str = "The thread attempted to access an base_array element that is out of bounds, and the underlying hardware supports bounds checking";
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
      str = "Unknown Exception (Not currently known by ca2 platform)";
      break;
   };

   return str;

}
#else

   void se_translator::filter_sigsegv(int signal, siginfo_t * psiginfo, void * pc)
   {
      throw se_access_violation(NULL, psiginfo, pc);
   }

   void se_translator::filter_fpe(int signal, siginfo_t * psiginfo, void * pc)
   {


   }

#endif
/*

the_se_translator the_se_translator::s_thesetranslator;

the_se_translator::the_se_translator()
{
   attach();
}

the_se_translator::~the_se_translator()
{
   detach();
}
*/
