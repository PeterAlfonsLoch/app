//#include "framework.h"
//#include "metrowin.h"

DWORD get_tick_count()
{

   return (DWORD) (GetTickCount64() % 0x100000000ULL);

}
