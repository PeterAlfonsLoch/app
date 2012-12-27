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




void oswindow::set_user_interaction(::user::interaction_base * pui)
{
    
    if(m_pdata == NULL)
        throw "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction";
    
    m_pdata->m_pui = pui;
    
}
::user::interaction_base * oswindow::get_user_interaction_base()
{
    
    if(m_pdata == NULL)
        return NULL;
    
    return m_pdata->m_pui;
    
}

::user::interaction_base * oswindow::get_user_interaction_base() const
{
    
    if(m_pdata == NULL)
        return NULL;
    
    return m_pdata->m_pui;
    
}

::user::interaction * oswindow::get_user_interaction()
{
    
    if(m_pdata == NULL)
        return NULL;
    
    if(m_pdata->m_pui == NULL)
        return NULL;
    
    return m_pdata->m_pui->m_pui;
    
}

::user::interaction * oswindow::get_user_interaction() const
{
    
    if(m_pdata == NULL)
        return NULL;
    
    if(m_pdata->m_pui == NULL)
        return NULL;
    
    return m_pdata->m_pui->m_pui;
    
}





