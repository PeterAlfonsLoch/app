#include "framework.h"


#include <agile.h>


namespace user
{

   class interaction;

} // namespace user


class oswindow_data
{
public:

   ::user::interaction * m_pui;

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




int oswindow::find(::user::interaction * pui)
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

oswindow_data * oswindow::get(::user::interaction * pui)
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

oswindow::oswindow(::user::interaction * pui)
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





bool oswindow::remove(::user::interaction * pui)
{

   int_ptr iFind = find(pui);

   if(iFind < 0)
      return false;

   g_oswindow_dataptra()->remove_at(iFind);

   return true;

}




::user::interaction * oswindow::window()
{
   return m_pdata == NULL ? nullptr : m_pdata->m_pui;
}

::user::interaction * oswindow::window() const
{
   return m_pdata == NULL ? nullptr : m_pdata->m_pui;
}
