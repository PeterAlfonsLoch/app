#include "framework.h" // from "axis/user/user.h"
#include "ansios.h"


CLASS_DECL_AXIS int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam)
{

   HTHREAD  h = oswindow->get_user_interaction()->m_pauraapp->get_os_handle();

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.hwnd       = oswindow;
   msg.message    = Msg;
   msg.wParam     = wParam;
   msg.lParam     = lParam;
   msg.pt.x       = 0x80000000;
   msg.pt.y       = 0x80000000;


   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}




