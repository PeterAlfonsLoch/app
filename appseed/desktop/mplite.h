#ifndef _MPLITE_INCLUDE_FILE
#define _MPLITE_INCLUDE_FILE

#ifdef _MPLITE_DLL
   #define CLASS_DECL_MPLITE  _declspec(dllexport)
#else
   #define CLASS_DECL_MPLITE  _declspec(dllimport)
#endif

#endif
