#include "framework.h"

Display * x11_get_display();

#define CA2_CCVOTAGUS_WINDOW_LONG "ca2_ccvotagus_window_long"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE "ca2_ccvotagus_window_long_style"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_window_long_style_ex"

osdisplay_dataptra * osdisplay_data::s_pdataptra = NULL;
mutex * osdisplay_data::s_pmutex = NULL;

osdisplay_data::osdisplay_data()
{

   m_pdisplay           = NULL;
   m_atomLongType       = None;
   m_atomLongStyle      = None;
   m_atomLongStyleEx    = 0;

}




int32_t osdisplay_find(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   for(int32_t i = 0; i < osdisplay_data::s_pdataptra->get_count(); i++)
   {
      if(osdisplay_data::s_pdataptra->element_at(i)->m_pdisplay == pdisplay)
      {
         return i;
      }
   }

   return -1;

}

osdisplay_data * osdisplay_get(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   int_ptr iFind = osdisplay_find(pdisplay);

   if(iFind >= 0)
      return osdisplay_data::s_pdataptra->element_at(iFind);

   osdisplay_data * pdata     = new osdisplay_data;

   pdata->m_pdisplay          = pdisplay;
   pdata->m_atomLongType      = XInternAtom(pdisplay     , CA2_CCVOTAGUS_WINDOW_LONG            , False);
   pdata->m_atomLongStyle     = XInternAtom(pdisplay     , CA2_CCVOTAGUS_WINDOW_LONG_STYLE      , False);
   pdata->m_atomLongStyleEx   = XInternAtom(pdisplay     , CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX   , False);

   ::osdisplay_data::s_pdataptra->add(pdata);

   return pdata;

}



bool osdisplay_remove(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   int_ptr iFind = osdisplay_find(pdisplay);

   if(iFind < 0)
      return false;

   ::osdisplay_data::s_pdataptra->remove_at(iFind);

   return true;

}

Atom osdisplay_data::get_window_long_atom(int32_t nIndex)
{

   if(this == NULL)
      return 0;

   switch(nIndex)
   {
   case GWL_STYLE:

      return m_atomLongStyle;

   case GWL_EXSTYLE:

      return m_atomLongStyleEx;

   default:
      {

         string strProperty;

         strProperty = CA2_CCVOTAGUS_WINDOW_LONG + itoa_dup(nIndex);

         return XInternAtom(m_pdisplay, strProperty, False);

      }
   }

}


  xdisplay::xdisplay()
  {
      m_pdisplay    = NULL;
      m_bOwn        = false;
      m_bLocked     = false;
  }

  xdisplay::xdisplay(Display * pdisplay, bool bInitialLock)
  {
      m_pdisplay    = pdisplay;
      m_bOwn        = false;
      m_bLocked     = false;
      if(bInitialLock)
        lock();
  }

  bool xdisplay::open(char * display_name, bool bInitialLock)
  {
      unlock();
close();
    //m_pdisplay      = XOpenDisplay(display_name);
    m_pdisplay = x11_get_display();
    if(m_pdisplay == NULL)
    return false;
    //m_bOwn          = true;
    m_bOwn = false;
    if(bInitialLock)
        lock();
        return true;
  }

  bool xdisplay::close()
  {

           if(!m_bOwn || m_pdisplay == NULL)
            return false;

         XCloseDisplay(m_pdisplay);
         m_pdisplay = NULL;
         m_bOwn = false;
         return true;

  }

    xdisplay::~ xdisplay()
    {
        unlock();


        close();

    }


void xdisplay::lock()
    {
if(m_pdisplay == NULL || m_bLocked)
return;
m_bLocked = true;
XLockDisplay(m_pdisplay);

    }

void xdisplay::unlock()
{

    if(m_pdisplay == NULL || !m_bLocked)
    return;
    XUnlockDisplay(m_pdisplay);
    m_bLocked = false;
}




Window xdisplay::default_root_window()
{
    if(m_pdisplay == NULL)
    return None;
    return DefaultRootWindow(m_pdisplay);
}

int xdisplay::default_screen()
{
    if(m_pdisplay == NULL)
    return None;
    return DefaultScreen(m_pdisplay);
}
