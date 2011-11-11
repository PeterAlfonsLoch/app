#pragma once


#include "ca/ca.h"


// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBCHARGUESS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBCHARGUESS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LINUX
#define LIBCHARGUESS_API
#elif LIBCHARGUESS_EXPORTS
#define LIBCHARGUESS_API CLASS_DECL__
#else
#define LIBCHARGUESS_API CLASS_DECL__
#endif

// This class is exported from the libcharguess.dll
class LIBCHARGUESS_API LibCharGuess {
public:
   LibCharGuess(void);
   // TODO: add your methods here.

   static int Init();
   static const char * GuessCharset(const char * lpsz);
   static unsigned long GuessCodePage(const char * lpsz);
   static int Done();
};

extern LIBCHARGUESS_API int nLibcharguess;

LIBCHARGUESS_API int fnLibcharguess(void);

