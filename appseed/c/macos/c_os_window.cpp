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

   if(&oswindow != this)
   {
   
      m_pdata = oswindow.m_pdata;
   
   }

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


oswindow oswindow::get_parent()
{
   
   if(m_pdata == NULL)
      return ::ca::null();
   
   return m_pdata->m_pui->get_parent();
   
}


oswindow oswindow::set_parent(oswindow oswindow)
{
   
   if(m_pdata == NULL)
      return ::ca::null();
   
   ::oswindow oswindowOldParent = get_parent();
   
   if(oswindow.m_pdata == NULL
   || oswindow.m_pdata->m_pui == NULL
   || oswindow.m_pdata->m_pui->m_pui == NULL)
   {
   
      m_pdata->m_pui->set_parent(NULL);
      
   }
   else
   {
      
      m_pdata->m_pui->set_parent(oswindow.m_pdata->m_pui->m_pui);
      
   }
   
   return oswindowOldParent;
   
}


int32_t oswindow::get_window_long(int32_t iIndex)
{
   
   return 0;
   
}




static oswindow g_oswindowCapture;


oswindow GetCapture()
{
   return g_oswindowCapture;
}

oswindow SetCapture(oswindow window)
{
   
   oswindow windowOld(g_oswindowCapture);
   
   if(window.window() == NULL)
      return ::ca::null();
   
/*   if(XGrabPointer(window.display(), window.window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, 8CurrentTime) == GrabSuccess)
   {
      
      g_oswindowCapture = window;
      
      return windowOld;
      
   }*/
   
   return ::ca::null();
   
}


WINBOOL ReleaseCapture()
{
   
   //ifGetCapture().display() == NULL)
     // return FALSE;
   
 //  WINBOOL bRet = XUngrabPointer(GetCapture().display(), CurrentTime) != FALSE;
   
   WINBOOL bRet = FALSE;
   
   if(bRet)
      g_oswindowCapture = ::ca::null();
   
   return bRet;
   
}


oswindow SetFocus(oswindow window)
{
   
   if(!IsWindow(window))
      return ::ca::null();
   
   oswindow windowOld = ::GetFocus();
   
//   if(!XSetInputFocus(window.display(), window.window(), RevertToNone, CurrentTime))
  //    return ::ca::null();
   
   return windowOld;
   
}

oswindow GetFocus()
{
   
   //isplay * pdisplay = XOpenDisplay(NULL);
   
//   Window window = None;
   
//   int revert_to = 0;
   
   //bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;
   
   //XCloseDisplay(pdisplay);
   
//   if(!bOk)
  //    return ::ca::null();
   
  // if(window == None || window == PointerRoot)
    //  return ::ca::null();
   
   //return oswindow::defer_get(window);
   return ::ca::null();
   
}

