#include "framework.h"


#include <agile.h>


namespace user
{

   class interaction;

} // namespace user


class oswindow_data
{
public:

   ::user::interaction_base * m_pui;

};


class oswindow_dataptra :
   public simple_array < oswindow_data * >
{
public:


};

oswindow_dataptra * g_oswindow_dataptra()
{
   static oswindow_dataptra * s_pdataptra = new oswindow_dataptra;

   return s_pdataptra;
}




int oswindow::find(::user::interaction_base * pui)
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

oswindow_data * oswindow::get(::user::interaction_base * pui)
{

   int_ptr iFind = find(pui);

   if(iFind >= 0)
      return g_oswindow_dataptra()->element_at(iFind);

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_pui = pui;

   g_oswindow_dataptra()->add(pdata);

   return pdata;

}

oswindow::oswindow(const ::ca::null & null)
{

   m_pdata = NULL;

}

oswindow::oswindow()
{

   m_pdata = NULL;

}

oswindow::oswindow(::user::interaction_base * pui)
{

   m_pdata = get(pui);

}

oswindow::oswindow(const oswindow & oswindow)
{

   m_pdata = oswindow.m_pdata;

}

oswindow::oswindow(const void * p)
{

   m_pdata = (oswindow_data *) p;

}

oswindow::oswindow(const LPARAM & lparam)
{

   m_pdata = (oswindow_data *) lparam;

}

oswindow::oswindow(const WPARAM & wparam)
{

   m_pdata = (oswindow_data *) wparam;

}





oswindow & oswindow::operator = (const oswindow & oswindow)
{

   m_pdata = oswindow.m_pdata;

   return *this;

}





bool oswindow::remove(::user::interaction_base * pui)
{

   int_ptr iFind = find(pui);

   if(iFind < 0)
      return false;

   g_oswindow_dataptra()->remove_at(iFind);

   return true;

}




::user::interaction * oswindow::window()
{
   return m_pdata == NULL ? nullptr : (m_pdata->m_pui == NULL ? nullptr : m_pdata->m_pui->m_pui);
}

::user::interaction * oswindow::window() const
{
   return m_pdata == NULL ? nullptr : (m_pdata->m_pui == NULL ? nullptr : m_pdata->m_pui->m_pui);
}

Platform::Agile<Windows::UI::Core::CoreWindow> oswindow::get_os_window()
{
   return m_pdata->m_pui->get_os_window();
}

static oswindow g_oswindowFocus;


CLASS_DECL_c oswindow WINAPI GetFocus()
{

   return g_oswindowFocus;

}

CLASS_DECL_c oswindow WINAPI SetFocus(oswindow oswindow)
{
   
   ::oswindow oswindowOldFocus = g_oswindowFocus;

   g_oswindowFocus = oswindow;

   // todo
   //SendMessage(oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) oswindow)

   return oswindowOldFocus;

}



static oswindow g_oswindowCapture;


CLASS_DECL_c oswindow WINAPI GetCapture()
{

   return g_oswindowCapture;

}

CLASS_DECL_c oswindow WINAPI SetCapture(oswindow oswindow)
{
   
   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = oswindow;

   // todo
   //SendMessage(oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) oswindow)

   return oswindowOldCapture;

}


CLASS_DECL_c oswindow WINAPI ReleaseCapture()
{
   
   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = ::ca::null();

   // todo
   //SendMessage(oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) oswindow)

   return oswindowOldCapture;

}