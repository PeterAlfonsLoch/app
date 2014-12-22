#include "framework.h"




void __cdecl __crt_dump_client(void * pvData, size_t nBytes)
{
}

int32_t __cdecl __crt_report_hook(int32_t nRptType, char *szMsg, int32_t* pResult)
{
   return FALSE;
}


