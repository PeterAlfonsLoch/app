/*
 Copyright (c) 2001 - 2002
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

#include <imagehlp.h>


class mutex;


namespace exception
{


   class CLASS_DECL_ca engine :
      virtual public ::ca::ca
   {
   public:


      bool                 m_bSkip;
      mutex *              m_pmutex;

      DWORD64              m_uiAddress;
      bool                 m_bOk;

      STACKFRAME64 *       m_pstackframe;
      CONTEXT *            m_pcontext;


      engine(::ca::application * papp);
      ~engine();


      void address(DWORD64 a)      { m_uiAddress = a; }
      DWORD64 address() const   { return m_uiAddress; }

      // symbol handler queries
      size_t      module  (vsstring & str);
      size_t      symbol  (vsstring & str, DWORD64 * pdisplacement = 0);
      index       fileline(vsstring & str, DWORD * pline, DWORD * pdisplacement= 0);

      // stack walk
      bool stack_first (CONTEXT* pctx);
      bool stack_next  ();

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
      bool stack_trace(vsstring & str, CONTEXT *, dword_ptr uiSkip = 0, const char * pszFormat = default_format());
      bool stack_trace(vsstring & str, dword_ptr uiSkip = 1, const char * pszFormat = default_format());
      bool stack_trace(vsstring & str, CONTEXT *, dword_ptr uiSkip = 1, bool bSkip = false, const char * pszFormat = default_format());
      DWORD WINAPI stack_trace_ThreadProc(void * lpvoidParam);

      static const char * default_format(){ return "%f(%l) : %m at %s\n"; }
      bool get_line_from_address(HANDLE hProc, DWORD64 uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE64 * pline);
      size_t get_module_basename(HMODULE hmodule, vsstring & strName);

      vsstring get_frame(const char * pszFormat);

      bool check();



      class CLASS_DECL_ca guard :
         virtual public ::ca::ca
      {
      public:
         

         int                        m_iRef;
         simple_array < HMODULE >   m_ha;


         guard(::ca::application * papp);
         ~guard();


         bool init();
         bool fail() const;
         bool load_modules();
         void clear();
         bool load_module(HANDLE, HMODULE);
         
      };


   };


} // namespace exception

#endif

// Change Log:
//      25.12.2001  Konstantin, Initial version.
//      11.01.2002   Konstantin, added skip arg to stack_trace()
//      11.01.2002   Konstantin, format argument to stack_trace()
//      14.01.2002   Konstantin, fixed bug in thread's wait logic
//      16.01.2002, Konstantin, fixed bug in stack_trace(std::ostream&, CONTEXT *, const char*) with skip value
//      16.01.2002, Konstantin, made guard as singelton

