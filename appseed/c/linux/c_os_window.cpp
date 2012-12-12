#include "framework.h"


class oswindow_dataptra :
   public simple_array < oswindow::data * >
{
public:


};

#define CA2_CCVOTAGUS_WINDOW_LONG "ca2_ccvotagus_fontopu_window_long"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE "ca2_ccvotagus_fontopu_window_long_style"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_fontopu_window_long_style_ex"

oswindow_dataptra * oswindow::s_pdataptra = new oswindow_dataptra;


int oswindow::find(Display * pdisplay, Window window)
{

   for(int i = 0; i < s_pdataptra->get_count(); i++)
   {
      if(s_pdataptra->element_at(i)->m_osdisplay == pdisplay
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

   pdata->m_osdisplay   = pdisplay;
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


void oswindow::set_user_interaction(::user::interaction_base * pui)
{

   if(m_pdata == NULL)
      throw "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction";

   m_pdata->m_pui = pui;

}
::user::interaction_base * oswindow::get_user_interaction()
{

   if(m_pdata == NULL)
      return NULL;

   return m_pdata->m_pui;

}

::user::interaction_base * oswindow::get_user_interaction() const
{

   if(m_pdata == NULL)
      return NULL;

   return m_pdata->m_pui;

}



bool oswindow::is_child(::oswindow oswindow)
{

   oswindow = oswindow.get_parent();
   while(!oswindow.is_null())
   {
      if(oswindow.m_pdata == m_pdata)
         return true;
   }

   return false;

}

oswindow oswindow::get_parent()
{

   if(m_pdata == NULL)
      return ::ca::null();

   Window root = 0;
   Window parent = 0;
   Window * pchildren = NULL;
   unsigned int ncount = 0;

   XQueryTree(display(), window(), &root, &parent, &pchildren, &ncount);

   if(pchildren != NULL)
      XFree(pchildren);

   return oswindow(display(), parent);

}


bool oswindow::show_window(int nCmdShow)
{

   if(nCmdShow == SW_HIDE)
   {

      XUnmapWindow(display(), window());

   }
   else
   {

      XMapWindow(display(), window());

   }

}



LONG oswindow::get_window_long(int nIndex)
{

   Atom type = 0;
   int format = 0;
   unsigned long itemcount = 0;
   unsigned long remaining = 0;
   LONG * pl = NULL;
   LONG l;

   XGetWindowProperty(display(), window(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), 0, 1, False, m_pdata->m_osdisplay.atom_long_type(), &type, &format, &itemcount, &remaining, (unsigned char **) &pl);

   l = *pl;

   XFree(pl);

   return l;

}


LONG oswindow::set_window_long(int nIndex, LONG l)
{

   LONG lOld = get_window_long(nIndex);

   XChangeProperty(display(), window(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), m_pdata->m_osdisplay.atom_long_type(), 32, PropModeReplace, (unsigned char *) &l, 1);

   return lOld;

}


Atom get_window_long_atom(int nIndex);
