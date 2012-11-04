#include "framework.h"


#include <agile.h>


class oswindow_data
{
public:

   Platform::Agile < Windows::UI::Core::CoreWindow > m_window;

};


class oswindow_dataptra :
   public simple_array < oswindow_data * >
{
public:


};



oswindow_dataptra * oswindow::s_pdataptra = new oswindow_dataptra;


int oswindow::find(Windows::UI::Core::CoreWindow ^ window)
{

   for(int i = 0; i < s_pdataptra->get_count(); i++)
   {
      if(s_pdataptra->element_at(i)->m_window.Get() == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow::get(Windows::UI::Core::CoreWindow ^ window)
{

   int_ptr iFind = find(window);

   if(iFind >= 0)
      return s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_window = window;

   s_pdataptra->add(pdata);

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

oswindow::oswindow(Windows::UI::Core::CoreWindow ^ window)
{

   m_pdata = get(window);

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





bool oswindow::remove(Windows::UI::Core::CoreWindow ^ window)
{

   int_ptr iFind = find(window);

   if(iFind < 0)
      return false;

   s_pdataptra->remove_at(iFind);

   return true;

}




Windows::UI::Core::CoreWindow ^ oswindow::window()
{
   return m_pdata == NULL ? nullptr : m_pdata->m_window.Get();
}

Windows::UI::Core::CoreWindow ^ oswindow::window() const
{
   return m_pdata == NULL ? nullptr : m_pdata->m_window.Get();
}
