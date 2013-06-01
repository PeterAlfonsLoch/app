#include "framework.h"


#include "libcharguess.h"
#include "charguess.h"



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

uint32_t LibCharGuess::GuessCodePage(const char * lpsz)
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
