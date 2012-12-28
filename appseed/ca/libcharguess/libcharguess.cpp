#include "framework.h"


#include "libcharguess.h"
#include "charguess.h"
#include <string.h>

#ifdef WIN32

#include <windows.h>

/*
extern "C" int32_t APIENTRY
DllMain( HINSTANCE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                )
{
    switch (ul_reason_for_call)
   {
      case DLL_PROCESS_ATTACH:
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
         break;
    }
    return TRUE;
}
*/
#endif

// This is an example of an exported var
LIBCHARGUESS_API int32_t nLibcharguess=0;

// This is an example of an exported function.
LIBCHARGUESS_API int32_t fnLibcharguess()
{
   return 42;
}

// This is the constructor of a class that has been exported.
// see libcharguess.h for the class definition
LibCharGuess::LibCharGuess()
{
   return;
}




int32_t LibCharGuess::Init()
{
   return CharGuessInit();
}
const char * LibCharGuess::GuessCharset(const char * lpsz)
{
   return GuessChardet(lpsz);
}

unsigned long LibCharGuess::GuessCodePage(const char * lpsz)
{
   if(lpsz == NULL)
      return 0;

   const char * lpszCharset = GuessCharset(lpsz);

   if(lpszCharset == NULL)
   {
      return 0;
   }
   else if(!stricmp_dup(lpszCharset, "Shift_JIS"))
   {
      return 932;
   }
   else if(!stricmp_dup(lpszCharset, "Big5"))
   {
      return 950;
   }
   else if(!stricmp_dup(lpszCharset, "windows-1252"))
   {
      return 1252;
   }
   else
   {
      return 0;
   }
}


int32_t LibCharGuess::Done()
{
   return CharGuessDone();
}
