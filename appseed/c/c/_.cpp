#include "framework.h"



CLASS_DECL_c int ___()
{

   MessageBox(NULL, "___ library of ca2", "___ library of ca2", MB_ICONINFORMATION | MB_OK);

   return 0;

}


CLASS_DECL_c dword get_tick_count()
{

#ifdef MERDE_WINDOWS

   return (dword) (GetTickCount64() % 0x100000000ULL);

#else

   return (dword) GetTickCount();

#endif

}