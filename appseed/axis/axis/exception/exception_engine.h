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

#include <imagehlp.h>

#endif

class mutex;


namespace exception
{


   class CLASS_DECL_AXIS engine :
      virtual public element
   {
   public:



      mutex *              m_pmutex;


#ifdef WINDOWSEX

      bool                 m_bSkip;
      DWORD64              m_uiAddress;
      bool                 m_bOk;

      STACKFRAME64 *       m_pstackframe;
      CONTEXT *            m_pcontext;

      int32_t                        m_iRef;
      array < HMODULE >   m_ha;


#endif




      engine(sp(::base::application) papp);
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


      static const char * default_format(){ return "%f(%l) : %m at %s\n"; }



#ifdef WINDOWSEX

      bool stack_trace(string & str, CONTEXT *, uint_ptr uiSkip = 0, const char * pszFormat = default_format());
      bool stack_trace(string & str, uint_ptr uiSkip = 1, const char * pszFormat = default_format());
      bool stack_trace(string & str, CONTEXT *, uint_ptr uiSkip = 1, bool bSkip = false, const char * pszFormat = default_format());

#else

      bool stack_trace(string & str, uint_ptr uiSkip = 0, void * caller_address = NULL, const char * pszFormat = default_format());

#endif


      void reset();


#ifdef WINDOWSEX

      uint32_t WINAPI stack_trace_ThreadProc(void * lpvoidParam);


      bool get_line_from_address(HANDLE hProc, DWORD64 uiAddress, DWORD * puiDisplacement, IMAGEHLP_LINE64 * pline);
      size_t get_module_basename(HMODULE hmodule, string & strName);

      string get_frame(const char * pszFormat);

      bool check();


      void address(DWORD64 a)      { m_uiAddress = a; }
      DWORD64 address() const   { return m_uiAddress; }

      // symbol handler queries
      size_t      module  (string & str);
      size_t      symbol  (string & str, DWORD64 * pdisplacement = 0);
      index       fileline(string & str, uint32_t * pline, uint32_t * pdisplacement= 0);

      // stack walk
      bool stack_first (CONTEXT* pctx);
      bool stack_next  ();

      bool init();
      bool fail() const;
      bool load_modules();
      void clear();
      bool load_module(HANDLE, HMODULE);

#endif

   };


} // namespace exception


// Change Log:
//      25.12.2001  Konstantin, Initial version.
//      11.01.2002   Konstantin, added skip arg to stack_trace()
//      11.01.2002   Konstantin, format argument to stack_trace()
//      14.01.2002   Konstantin, fixed bug in thread's wait logic
//      16.01.2002, Konstantin, fixed bug in stack_trace(::file::output_stream&, CONTEXT *, const char*) with skip value
//      16.01.2002, Konstantin, made guard as singelton

