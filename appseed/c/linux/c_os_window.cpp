#include "framework.h"


class oswindow_dataptra :
   public simple_array < oswindow::data * >
{
public:


};



oswindow_dataptra * oswindow::s_pdataptra = new oswindow_dataptra;


int oswindow::find(Display * pdisplay, Window window)
{

   for(int i = 0; i < s_pdataptra->get_count(); i++)
   {
      if(s_pdataptra->element_at(i)->m_pdisplay == pdisplay
      && s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow::data * oswindow::get(Display * pdisplay, Window window)
{

   int_ptr iFind = find(pdisplay, window);

   if(iFind >= 0)
      return s_pdataptra->element_at(iFind);

   ::oswindow::data * pdata = new data;

   pdata->m_pdisplay    = pdisplay;
   pdata->m_window      = window;

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

oswindow::oswindow(Display * pdisplay, Window window)
{

   m_pdata = get(pdisplay, window);

}

oswindow::oswindow(const oswindow & oswindow)
{

   m_pdata = oswindow.m_pdata;

}

oswindow::oswindow(const void * p)
{

   m_pdata = (data *) p;

}

oswindow::oswindow(const LPARAM & lparam)
{

   m_pdata = (data *) lparam;

}

oswindow::oswindow(const WPARAM & wparam)
{

   m_pdata = (data *) wparam;

}





oswindow & oswindow::operator = (const oswindow & oswindow)
{

   m_pdata = oswindow.m_pdata;

   return *this;

}





bool oswindow::remove(Display * pdisplay, Window window)
{

   int_ptr iFind = find(pdisplay, window);

   if(iFind < 0)
      return false;

   s_pdataptra->remove_at(iFind);

   return true;

}

int oswindow::store_name(const char * psz)
{

   return XStoreName(display(), window(), psz);

}


int oswindow::select_input(int iInput)
{

   return XSelectInput(display(), window(), iInput);

}


int oswindow::select_all_input()
{

   return select_input(ExposureMask | ButtonPressMask);

}


int oswindow::map_window()
{

   return XMapWindow(display(), window());

}


void oswindow::post_nc_destroy()
{

   remove(display(), window());

}


void oswindow::set_user_interaction(::user::interaction * pui)
{

   if(m_pdata == NULL)
      throw "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction";

   m_pdata->m_pui = pui;

}
::user::interaction * oswindow::get_user_interaction()
{

   if(m_pdata == NULL)
      return NULL;

   return m_pdata->m_pui;

}

::user::interaction * oswindow::get_user_interaction() const
{

   if(m_pdata == NULL)
      return NULL;

   return m_pdata->m_pui;

}

