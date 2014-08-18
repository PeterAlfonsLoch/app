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

 wrapper class for _set_se_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#ifdef WINDOWS
#include <eh.h>
#else
#include <signal.h>
#endif

extern CLASS_DECL_AXIS bool g_bExiting;


namespace exception
{


   class CLASS_DECL_AXIS translator :
      virtual public element
   {
   public:

   #if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
      struct sigaction m_saSeg;
      struct sigaction m_saFpe;
      struct sigaction m_saPipe;
      struct sigaction m_saSegOld;
      struct sigaction m_saFpeOld;
      struct sigaction m_saPipeOld;
   #endif

      translator();
      virtual ~translator();

   #ifdef WINDOWS
      void filter(uint32_t uiCode, _EXCEPTION_POINTERS * p);
      static void __cdecl filter2(uint32_t uiCode, _EXCEPTION_POINTERS * p);
      //void filter( _EXCEPTION_POINTERS * p);
   #else
      static void filter_sigsegv(int32_t signal, siginfo_t * psiginfo, void * pc);
      static void filter_sigfpe(int32_t signal, siginfo_t * psiginfo, void * pc);
      static void filter_sigpipe(int32_t signal, siginfo_t * psiginfo, void * pc);
   #endif

      static string name(uint32_t uiCode);
      static string description(uint32_t uiCode);


      bool attach();
      bool detach();



    private:
       bool                      m_bSet;
       //LPTOP_LEVEL_EXCEPTION_FILTER m_pfn;
   #ifdef WINDOWS
       _se_translator_function   m_pfn;
   #endif
   };


} // namespace exception


/*
class CLASS_DECL_AXIS the_se_translator : public translator
{
public:
   the_se_translator();
   virtual ~the_se_translator();
   static the_se_translator s_thesetranslator;
};*/
