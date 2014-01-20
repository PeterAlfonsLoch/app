#include "framework.h"


dword get_tick_count()
{

   return (dword) (GetTickCount64() % 0x100000000ULL);

}
