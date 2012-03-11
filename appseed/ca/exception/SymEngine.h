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


#ifdef _WINDOWS
#include <imagehlp.h>
#endif

class SymEngine
{
public:


   SymEngine(unsigned int);
   ~SymEngine();


   void address(DWORD_PTR a)      { m_uiAddress = a; }
   DWORD_PTR address(void) const   { return m_uiAddress; }

   // symbol handler queries
   size_t      module  (vsstring & str);
   size_t      symbol  (vsstring & str, DWORD_PTR * = 0);
   index       fileline(vsstring & str, DWORD_PTR *, DWORD_PTR * = 0);

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
   static bool stack_trace(vsstring & str, CONTEXT *, DWORD_PTR uiSkip = 0, const char * pszFormat = default_format());
   static bool stack_trace(vsstring & str, DWORD_PTR uiSkip = 1, const char * pszFormat = default_format());
   static bool stack_trace(vsstring & str, SymEngine&, CONTEXT *, DWORD_PTR uiSkip = 1, const char * pszFormat = default_format());
   static DWORD WINAPI stack_trace_ThreadProc(void * lpvoidParam);
 private:
   static const char * default_format(){ return "%f(%l) : %m at %s\n"; }
   static bool get_line_from_address(HANDLE hProc, DWORD_PTR uiAddress, DWORD_PTR * puiDisplacement, IMAGEHLP_LINE * pline);
   static size_t get_module_basename(HMODULE hmodule, vsstring & strName);



   bool check();

 private:
   DWORD_PTR      m_uiAddress;
   bool           m_bOk;
   STACKFRAME *   m_pstackframe;
   CONTEXT *      m_pcontext;

 private:
   class guard
   {
   private:
      guard();
   public:
      ~guard();
      bool init();
      bool fail() const { return m_iRef == -1; }
      static guard & instance()
      {
         static guard g;
         return g;
      }
   private:
      void clear();
      bool load_module(HANDLE, HMODULE);
      int  m_iRef;
   };
};

// Change Log:
//      25.12.2001  Konstantin, Initial version.
//      11.01.2002   Konstantin, added skip arg to stack_trace()
//      11.01.2002   Konstantin, format argument to stack_trace()
//      14.01.2002   Konstantin, fixed bug in thread's wait logic
//      16.01.2002, Konstantin, fixed bug in stack_trace(std::ostream&, CONTEXT *, const char*) with skip value
//      16.01.2002, Konstantin, made guard as singelton

