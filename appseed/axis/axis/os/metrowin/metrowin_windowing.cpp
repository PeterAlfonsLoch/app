//#include "framework.h"
//#include "metrowin_window_impl.h"
//#include "base/user/user.h"


//#include <agile.h>


namespace user
{

   class interaction;

} // namespace user


class oswindow_dataptra :
   public comparable_raw_array < oswindow_data * >
{
public:


};

oswindow_dataptra * g_oswindow_dataptra()
{
   static oswindow_dataptra * s_pdataptra = new oswindow_dataptra;

   return s_pdataptra;
}


::user::interaction * oswindow_data::window()
{

   if(this == NULL)
      return NULL;
   
   return m_pui;

}


int oswindow_find(::user::interaction * pui)
{

   for(int i = 0; i < g_oswindow_dataptra()->get_count(); i++)
   {
      if(g_oswindow_dataptra()->element_at(i)->m_pui == pui)
      {
         return i;
      }
   }

   return -1;

}


oswindow oswindow_get(::user::interaction * pui)
{

   int_ptr iFind = oswindow_find(pui);

   if(iFind >= 0)
      return g_oswindow_dataptra()->element_at(iFind);

   oswindow pdata  = new oswindow_data;

   pdata->m_pui = pui;

   g_oswindow_dataptra()->add(pdata);

   return pdata;

}




//int_bool oswindow_remove(::user::interaction * pui)
//{
//
//   int_ptr iFind = oswindow_find(pui);
//
//   if(iFind < 0)
//      return false;
//
//   g_oswindow_dataptra()->remove_at(iFind);
//
//   return true;
//
//}



Agile < Windows::UI::Core::CoreWindow > get_os_window(oswindow window)
{

   return window->m_pui->get_os_window();

}


static oswindow g_oswindowFocus;


oswindow WINAPI GetFocus()
{

   return g_oswindowFocus;

}

oswindow WINAPI SetFocus(oswindow __oswindow)
{
   
   ::oswindow oswindowOldFocus = g_oswindowFocus;

   g_oswindowFocus = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldFocus;

}



static oswindow g_oswindowCapture;


oswindow WINAPI GetCapture()
{

   return g_oswindowCapture;

}

oswindow WINAPI SetCapture(oswindow __oswindow)
{
   
   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


oswindow WINAPI ReleaseCapture()
{
   
   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = NULL;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


static oswindow g_oswindowActive;


oswindow WINAPI GetActiveWindow()
{

   return g_oswindowActive;

}

oswindow WINAPI SetActiveWindow(oswindow __oswindow)
{

   ::oswindow oswindowOldActive = g_oswindowActive;

   g_oswindowActive = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldActive;

}



oswindow_data * WINAPI GetParent(oswindow_data * pdata)
{

   if(pdata == NULL)
      return NULL;

   if(!IsWindow(pdata))
      return NULL;

   return (oswindow_data *) pdata->m_pui->GetParent()->get_os_data();


}



WINBOOL IsWindow(oswindow oswindow)
{

   if(((void *)oswindow) == NULL)
   return FALSE;

   return TRUE;

}

