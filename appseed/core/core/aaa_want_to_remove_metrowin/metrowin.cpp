#include "framework.h"


#ifdef METROWIN
[Platform::MTAThread]
#endif
extern "C" int APIENTRY
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


DWORD get_tick_count()
{
    return GetTickCount64() % 0xffffffffULL;
}




/*
CLASS_DECL_ca2 errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode)
{
   if(pFile == NULL)
   {
      return EINVAL;
   }

   *pFile = fopen(pFileName, mode);

   if(*pFile == NULL)
   {
      return errno;
   }

   return 0;

}
*/





CLASS_DECL_ca2 BOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   if(oswindow->window() == NULL || oswindow->window()->m_pthread == NULL)
      return FALSE;

   HTHREAD h = (HTHREAD) oswindow->window()->m_pthread->get_os_handle();

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.oswindow   = oswindow;
   msg.message    = Msg;
   msg.wParam     = wParam;
   msg.lParam     = lParam;

   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}
