/*
 Copyright (ca) 2001 - 2002
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 19:41:00
 Version: 1.0.2

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 sym_engine class incapsulate Symbol Handler and Debugging Service API

 the list of used API:
   SymInitialize, SymCleanup, SymGetLineFromAddr, SymGetModuleBase,
   SymGetSymbolInfo, SymGetSymFromAddr, SymGetSymFromName, SymGetSymNext,
   SymLoadModule, SymSetOptions
   StackWalk

 based on code\ideas from John Robbins's book "Debugging application"
 http://www.wintellect.com/robbins
*/

#pragma once


#ifdef WINDOWSEX
#pragma warning(disable: 4091)
#include <ImageHlp.h>


typedef struct _tagSTACKFRAME64 STACKFRAME64,*LPSTACKFRAME64;
typedef struct _IMAGEHLP_LINE64 IMAGEHLP_LINE64,*PIMAGEHLP_LINE64;
//#include <imagehlp.h>

#endif

class mutex;


namespace exception
{


   class CLASS_DECL_AURA engine :
      virtual public object
   {
   public:


      mutex                m_mutex;

#ifdef WINDOWSEX
      bool                 m_bSkip;
#if OSBIT == 32
      DWORD                m_uia[4096];
      STACKFRAME           m_stackframe;
#else
      DWORD64              m_uia[4096];
      STACKFRAME64         m_stackframe;
#endif
      int                  m_iAddressRead;
      int                  m_iAddressWrite;
      bool                 m_bOk;

      CONTEXT              m_context;

      int32_t              m_iRef;
      HMODULE              m_ha[4096];
      int                  m_iHa;

      HMODULE              m_ma[4096];
      int                  m_iMa;
      char *               m_szaModule[4096];

#else
      void *               m_uia[64];

      char                _str[4096];
      char                _strBuf[4096];
      char                _strFile[4096];
      char                _strSymbol[4096];
      char                _strS[1024 * 1024];

#endif




      engine(::aura::application * papp);
      ~engine();



      /*
         format argument
         %m  : module
         %f  : file
         %l  : line
         %ld : line's displacement
         %s  : symbol
         %sd : symbol's displacement

         for example
         "%f(%l) : %m at %s\n"
         "%m.%s + %sd bytes, in %f:line %l\n"
      */


      //static const char * default_format(){ return "%f(%l) : %m at %s\n"; }
      static const char * default_format() { return "%f(%l) : %s\n"; }



#ifdef WINDOWSEX

      bool stack_trace(CONTEXT *, uint_ptr uiSkip = 0, const char * pszFormat = default_format());
      bool stack_trace(uint_ptr uiSkip = 1, const char * pszFormat = default_format());
      bool stack_trace(CONTEXT *, uint_ptr uiSkip = 1, bool bSkip = false, const char * pszFormat = default_format());
#if OSBIT == 32
      char * stack_trace(DWORD * pui, int c, const char * pszFormat = default_format());
#else
      char * stack_trace(DWORD64 * pui, int c, const char * pszFormat = default_format());
#endif

#else

      char * stack_trace(uint_ptr uiSkip = 0, void * caller_address = NULL, const char * pszFormat = default_format());

#endif


      void reset();


#ifdef WINDOWSEX

      uint32_t WINAPI stack_trace_ThreadProc(void * lpvoidParam);

#if OSBIT == 32
      bool get_line_from_address(HANDLE hProc, DWORD uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE * pline);
#else
      bool get_line_from_address(HANDLE hProc, DWORD64 uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE64 * pline);
#endif
      //size_t get_module_basename(HMODULE hmodule, string & strName);
      size_t get_module_name(HMODULE hmodule, char * psz, int nCount);

      char * get_frame(const char * pszFormat);

      bool check();


#if OSBIT == 32
      void address(DWORD a)      { m_uia[m_iAddressWrite++] = a; }
      DWORD address()   { return m_uia[m_iAddressRead]; }
#else
      void address(DWORD64 a) { m_uia[m_iAddressWrite++] = a; }
      DWORD64 address() { return m_uia[m_iAddressRead]; }
#endif
      void backtrace();
      //DWORD64 * backtrace(int &c);
#if OSBIT == 32
      void backtrace(DWORD * pui, int &c);
#else
      void backtrace(DWORD64 * pui, int &c);
#endif

      // symbol handler queries
      size_t      module  (char * str, int nCount);
#if OSBIT == 32
      size_t      symbol  (char * str, int nCount, DWORD * pdisplacement = 0);
#else
      size_t      symbol(char * str, int nCount, DWORD64 * pdisplacement = 0);
#endif
      index       fileline(char * str, int nCount, uint32_t * pline, uint32_t * pdisplacement= 0);

      // stack walk
      bool stack_first (CONTEXT* pctx);
      bool stack_next  ();

      bool init();
      bool fail() const;
      bool load_modules();
      void clear();
      bool load_module(HANDLE, HMODULE);
#else

      void backtrace(void * pui, int &c);
      char * stack_trace(void * pui, int c, const char * pszFormat = default_format());

#endif

   };


} // namespace exception


// Change Log:
//      25.12.2001  Konstantin, Initial version.
//      11.01.2002   Konstantin, added skip arg to stack_trace()
//      11.01.2002   Konstantin, format argument to stack_trace()
//      14.01.2002   Konstantin, fixed bug in thread's wait logic
//      16.01.2002, Konstantin, fixed bug in stack_trace(::file::ostream&, CONTEXT *, const char*) with skip value
//      16.01.2002, Konstantin, made guard as singelton

