#include "framework.h"



#define CA2_CCVOTAGUS_WINDOW_LONG "ca2_ccvotagus_window_long"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE "ca2_ccvotagus_window_long_style"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_window_long_style_ex"

osdisplay_dataptra * osdisplay::s_pdataptra = new osdisplay_dataptra;
simple_mutex * osdisplay::s_pmutex = new simple_mutex;


int32_t osdisplay::find(Display * pdisplay)
{

   mutex_lock sl(user_mutex(), true);

   for(int32_t i = 0; i < s_pdataptra->get_count(); i++)
   {
      if(s_pdataptra->element_at(i)->m_pdisplay == pdisplay)
      {
         return i;
      }
   }

   return -1;

}

osdisplay::data * osdisplay::get(Display * pdisplay)
{

   mutex_lock sl(user_mutex(), true);

   int_ptr iFind = find(pdisplay);

   if(iFind >= 0)
      return s_pdataptra->element_at(iFind);

   ::osdisplay::data * pdata = new data;

   pdata->m_pdisplay          = pdisplay;
   pdata->m_atomLongType      = XInternAtom(pdisplay     , CA2_CCVOTAGUS_WINDOW_LONG            , False);
   pdata->m_atomLongStyle     = XInternAtom(pdisplay     , CA2_CCVOTAGUS_WINDOW_LONG_STYLE      , False);
   pdata->m_atomLongStyleEx   = XInternAtom(pdisplay     , CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX   , False);

   s_pdataptra->add(pdata);

   return pdata;

}

osdisplay::osdisplay(const ::caNULL & NULL)
{

   m_pdata = NULL;

}

osdisplay::osdisplay()
{

   m_pdata = NULL;

}

osdisplay::osdisplay(Display * pdisplay)
{

   m_pdata = get(pdisplay);

}

osdisplay::osdisplay(const osdisplay & osdisplay)
{

   m_pdata = osdisplay.m_pdata;

}


osdisplay & osdisplay::operator = (const osdisplay & osdisplay)
{

   m_pdata = osdisplay.m_pdata;

   return *this;

}

bool osdisplay::remove(Display * pdisplay)
{

   mutex_lock sl(user_mutex(), true);

   int_ptr iFind = find(pdisplay);

   if(iFind < 0)
      return false;

   s_pdataptra->remove_at(iFind);

   return true;

}

Atom osdisplay::get_window_long_atom(int32_t nIndex)
{

   if(m_pdata == NULL)
      return 0;

   switch(nIndex)
   {
   case GWL_STYLE:

      return m_pdata->m_atomLongStyle;

   case GWL_EXSTYLE:

      return m_pdata->m_atomLongStyleEx;

   default:
      {

         vsstring strProperty;

         strProperty = CA2_CCVOTAGUS_WINDOW_LONG + itoa_dup(nIndex);

         return XInternAtom(m_pdata->m_pdisplay, strProperty, False);

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
      if(bInitialLock)
        lock();
  }

  bool xdisplay::open(char * display_name, bool bInitialLock)
  {
      unlock();
close();
    m_pdisplay      = XOpenDisplay(display_name);
    if(m_pdisplay == NULL)
    return false;
    m_bOwn          = true;
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
