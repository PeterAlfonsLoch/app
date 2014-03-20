#include "framework.h"



int32_t ___()
{

   MessageBox(NULL, "___ library of ca", "___ library of ca", MB_ICONINFORMATION | MB_OK);

   return 0;

}


void __post_quit_message(int32_t nExitCode)
{

#ifdef WINDOWSEX

   ::PostQuitMessage(nExitCode);

#else

   throw not_implemented(get_thread_app());

#endif

}


string_map < INT_PTR, INT_PTR > & __library()
{
   static string_map < INT_PTR, INT_PTR > map;
   return map;
}