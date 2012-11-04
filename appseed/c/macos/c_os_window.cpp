#include "framework.h"


class oswindow_dataptra :
   public simple_array < oswindow::data * >
{
public:


};



oswindow_dataptra * oswindow::s_pdataptra = new oswindow_dataptra;


int oswindow::find(nswindow window)
{

   for(int i = 0; i < s_pdataptra->get_count(); i++)
   {
      if(s_pdataptra->element_at(i)->m_nswindow == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow::data * oswindow::get(nswindow window)
{

   int_ptr iFind = find(window);

   if(iFind >= 0)
      return s_pdataptra->element_at(iFind);

   ::oswindow::data * pdata = new data;

   pdata->m_nswindow    = window;

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

oswindow::oswindow(nswindow window)
{

   m_pdata = get(window);

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





bool oswindow::remove(nswindow window)
{

   int_ptr iFind = find(window);

   if(iFind < 0)
      return false;

   s_pdataptra->remove_at(iFind);

   return true;

}


