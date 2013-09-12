#include "framework.h"

#include <X11/Xatom.h>



oswindow_data::oswindow_data()
{

   m_plongmap              = new int_to_int();

   m_hthread               = NULL;

   m_window                = None;

   m_pui                   = NULL;

   m_bMessageOnlyWindow    = false;

   m_bDestroying           = false;

   m_osdisplay             = NULL;

}

oswindow_data::~oswindow_data()
{

   delete m_plongmap;

}



#define CA2_CCVOTAGUS_WINDOW_LONG "ca2_ccvotagus_fontopu_window_long"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE "ca2_ccvotagus_fontopu_window_long_style"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_fontopu_window_long_style_ex"

oswindow_dataptra * oswindow_data::s_pdataptra = new oswindow_dataptra;
mutex * oswindow_data::s_pmutex = new mutex;


int32_t oswindow_find_message_only_window(::user::base_interaction * pui)
{

   if(pui == NULL)
      return -1;

   single_lock slOsWindow(oswindow_data::s_pmutex, true);

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
      && ::oswindow_data::s_pdataptra->element_at(i)->m_pui == pui)
      {
         return i;
      }
   }

   return -1;

}

int32_t oswindow_find(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
      &&  ::oswindow_data::s_pdataptra->element_at(i)->m_osdisplay->display() == pdisplay
      &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

int32_t oswindow_find(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
      &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get_message_only_window(::user::base_interaction * pui)
{

   if(pui == NULL)
      return NULL;

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find_message_only_window(pui);

   if(iFind >= 0)
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_bMessageOnlyWindow      = true;
   pdata->m_window                  = None;
   pdata->m_pui                     = pui;
   pdata->m_osdisplay               = NULL;
   pdata->m_pvisual                 = NULL;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind >= 0)
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_bMessageOnlyWindow      = false;
   pdata->m_osdisplay               = osdisplay_get(pdisplay);
   pdata->m_window                  = window;
   pdata->m_pvisual                 = pvisual;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}

oswindow_data * oswindow_get(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(window);

   if(iFind < 0)
      return NULL;

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}

/*
oswindow::oswindow()
{

   m_pdata = NULL;

}

oswindow::oswindow(::user::interaction_base * pui)
{

   single_lock slOsWindow(s_pmutex, true);

   m_pdata = get_message_only_window(pui);



}

oswindow::oswindow(Display * pdisplay, Window window, Visual * pvisual)
{

   single_lock slOsWindow(s_pmutex, true);

   m_pdata = get(pdisplay, window);

   if(pvisual != NULL)
   {

      m_pdata->m_pvisual = pvisual;

   }


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



*/


oswindow oswindow_defer_get(Window window)
{

   return oswindow_get(window);

}



bool oswindow_remove(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind < 0)
      return false;

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


bool oswindow_remove_message_only_window(::user::base_interaction * puibaseMessageOnlyWindow)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);

   if(iFind < 0)
      return false;

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


int32_t oswindow_data::store_name(const char * psz)
{

   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XStoreName(display(), window(), psz);

}


int32_t oswindow_data::select_input(int32_t iInput)
{


   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XSelectInput(display(), window(), iInput);

}


int32_t oswindow_data::select_all_input()
{

   xdisplay d(display());

   return select_input(ExposureMask | ButtonPressMask);

}


int32_t oswindow_data::map_window()
{


   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XMapWindow(display(), window());

}


void oswindow_data::post_nc_destroy()
{

   single_lock slOsWindow(s_pmutex, true);

   oswindow_remove(display(), window());

}


void oswindow_data::set_user_interaction(::user::base_interaction * pui)
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      throw "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction";

   m_pui = pui;

   m_hthread = pui->m_pthread->get_os_handle();

}


::user::base_interaction * oswindow_data::get_user_interaction_base()
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   return m_pui;

}

::user::base_interaction * oswindow_data::get_user_interaction_base() const
{

   if(this == NULL)
      return NULL;

   return m_pui;

}

::user::interaction * oswindow_data::get_user_interaction()
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   if(m_pui == NULL)
      return NULL;

   return m_pui->m_pui;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   if(m_pui == NULL)
      return NULL;

   return m_pui->m_pui;

}


bool oswindow_data::is_child(::oswindow oswindow)
{

   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   oswindow = oswindow->get_parent();

   while(!oswindow->is_null())
   {
      if(oswindow == this)
         return true;
   }

   return false;

}

oswindow oswindow_data::get_parent()
{

   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   return NULL;

   Window root = 0;
   Window parent = 0;
   Window * pchildren = NULL;
   uint32_t ncount = 0;

   XQueryTree(display(), window(), &root, &parent, &pchildren, &ncount);

   if(pchildren != NULL)
      XFree(pchildren);

   return oswindow_get(display(), parent);

}

oswindow oswindow_data::set_parent(oswindow oswindow)
{

   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   xdisplay d(display());

   ::oswindow oswindowOldParent = get_parent();

   XReparentWindow(display(), window(), oswindow->window(), 0, 0);

   return oswindowOldParent;

}

bool oswindow_data::show_window(int32_t nCmdShow)
{

   single_lock sl(&user_mutex(), true);

   single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   if(nCmdShow == SW_HIDE)
   {

      XUnmapWindow(display(), window());

   }
   else
   {

      XMapWindow(display(), window());

   }

}



LONG oswindow_data::get_window_long(int32_t nIndex)
{

   return m_plongmap->operator[](nIndex);

/*   Atom type = 0;
   int32_t format = 0;
   unsigned long itemcount = 0;
   unsigned long remaining = 0;
   LONG * pl = NULL;
   LONG l;

   if(XGetWindowProperty(display(), window(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), 0, 1, False, m_pdata->m_osdisplay.atom_long_type(), &type, &format, &itemcount, &remaining, (unsigned char **) &pl) == Success)
   {

      if(pl != NULL)
      {

         l = *pl;

         XFree(pl);

      }
      else
      {

         l = 0;

      }

   }
   else
   {

      l = 0;

   }


   return l;*/

}


LONG oswindow_data::set_window_long(int32_t nIndex, LONG l)
{

   LONG lOld = m_plongmap->operator[](nIndex);

   m_plongmap->operator[](nIndex) = l;
/*   LONG lOld = get_window_long(nIndex);

   XChangeProperty(display(), window(), m_osdisplay.get_window_long_atom(nIndex), m_osdisplay.atom_long_type(), 32, PropModeReplace, (unsigned char *) &l, 1);*/

   return lOld;

}


bool oswindow_data::client_to_screen(POINT * pp)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT * pp)
{

   return true;

}

Atom get_window_long_atom(int32_t nIndex);




long oswindow_data::get_state()
{


   single_lock sl(&user_mutex(), true);

   xdisplay d(display());

  static const long WM_STATE_ELEMENTS = 2L;

  unsigned long nitems = 0;
  unsigned long leftover = 0;
  Atom xa_WM_STATE = 0;
  Atom actual_type = 0;
  int32_t actual_format = 0;
  int32_t status = 0;
  unsigned char* p = NULL;

  xa_WM_STATE = XInternAtom(display(), "WM_STATE", false);

  status = XGetWindowProperty(display(), window(), xa_WM_STATE, 0L, WM_STATE_ELEMENTS, False, xa_WM_STATE, &actual_type, &actual_format, &nitems, &leftover, &p);


  if(status == 0)
  {
     long lStatus = -1;
     if(p!= NULL)
      lStatus = (long)*p;
      XFree(p);
      return lStatus;
  }

  return -1;

}




bool oswindow_data::is_iconic()
{

   return get_state() == IconicState;

}

bool oswindow_data::is_window_visible()
{

   single_lock sl(&user_mutex(), true);
   xdisplay d(display());

   if(d.m_pdisplay == NULL)
    return false;

   XWindowAttributes attr;
   if(!XGetWindowAttributes(display(), window(), &attr))
      return false;
   return attr.map_state == IsViewable;

}






static oswindow g_oswindowCapture;


oswindow GetCapture()
{
      return g_oswindowCapture;
}

oswindow SetCapture(oswindow window)
{

   single_lock sl(&user_mutex(), true);

   oswindow windowOld(g_oswindowCapture);

   if(window->display() == NULL)
      return NULL;

   if(window->window() == None)
      return NULL;

   xdisplay d(window->display());

   if(XGrabPointer(window->display(), window->window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime) == GrabSuccess)
   {

      g_oswindowCapture = window;

      return windowOld;

   }

   return NULL;

}


WINBOOL ReleaseCapture()
{

   single_lock sl(&user_mutex(), true);

   xdisplay d(g_oswindowCapture->display());


   WINBOOL bRet = XUngrabPointer(g_oswindowCapture->display(), CurrentTime) != FALSE;

   if(bRet)
      g_oswindowCapture = NULL;

   return bRet;

}


oswindow SetFocus(oswindow window)
{

   single_lock sl(&user_mutex(), true);

   xdisplay display(window->display());

   if(!IsWindow(window))
      return NULL;

   oswindow windowOld = ::GetFocus();

   if(!XSetInputFocus(window->display(), window->window(), RevertToNone, CurrentTime))
      return NULL;

   return windowOld;

}

oswindow GetFocus()
{

   single_lock sl(&user_mutex(), true);

   xdisplay pdisplay;

   pdisplay.open(NULL);

   if(pdisplay == NULL)
   return NULL;

   Window window = None;

   int revert_to = 0;

   bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;

    pdisplay.close();

   if(!bOk)
      return NULL;

   if(window == None || window == PointerRoot)
      return NULL;

   return oswindow_defer_get(window);

}


oswindow GetActiveWindow()
{

   return GetFocus();

}


oswindow SetActiveWindow(oswindow window)
{

   return SetFocus(window);

}


oswindow GetWindow(oswindow windowParam, int iParentHood)
{

   single_lock sl(&user_mutex(), true);




   oswindow window = windowParam;

   if(window == NULL)
      return NULL;

   xdisplay d(window->display());

   if(iParentHood == GW_HWNDFIRST
   || iParentHood == GW_HWNDLAST
   || iParentHood == GW_HWNDNEXT
   || iParentHood == GW_HWNDPREV)
   {

      window = ::GetParent(window);

      if(window == NULL)
         return NULL;

   }


   Window root = 0;
   Window parent = 0;
   Window * pchildren = NULL;
   uint32_t ncount = 0;

   XQueryTree(window->display(), window->window(), &root, &parent, &pchildren, &ncount);

   switch(iParentHood)
   {
      case GW_CHILD:
      case GW_HWNDFIRST:
      {

         if(pchildren == NULL)
            return NULL;

         window = ::oswindow_get(window->display(), pchildren[0]);

      }
      break;
      case GW_HWNDLAST:
      {

         if(pchildren == NULL)
            return NULL;

         window = ::oswindow_get(window->display(), pchildren[ncount - 1]);

      }
      break;
      case GW_HWNDNEXT:
      case GW_HWNDPREV:
      {

         if(pchildren == NULL) // ????
            return NULL;

         int iFound = -1;

         for(int i = 0; i < ncount; i++)
         {
               if(pchildren[i] == windowParam->window())
               {
                  iFound = i;
                  break;
               }
         }

         if(iFound < 0)
            return NULL;

         if(iParentHood == GW_HWNDNEXT)
         {

            if(iFound + 1 >= ncount)
               return NULL;

            window = ::oswindow_get(window->display(), pchildren[iFound - 1]);

         }
         else
         {

            if(iFound - 1 < 0)
               return NULL;

            window = ::oswindow_get(window->display(), pchildren[iFound - 1]);

         }

      }

   }


   if(pchildren != NULL)
      XFree(pchildren);


   return window;

}



WINBOOL DestroyWindow(oswindow window)
{

   single_lock sl(&user_mutex(), true);

   if(!IsWindow(window))
      return FALSE;

   Display * pdisplay = window->display();

   Window win = window->window();

   xdisplay d(pdisplay);


   oswindow_data * pdata = (oswindow_data *) (void *) window;

   pdata->m_bDestroying = true;

   bool bIs = IsWindow(window);

   XDestroyWindow(pdisplay, win);

   return true;

}


bool oswindow_data::is_destroying()
{

   if(this == NULL)
      return true;

   if(m_bDestroying)
      return true;

   return false;

}


bool IsWindow(oswindow oswindow)
{
   return oswindow->get_user_interaction() != NULL && !oswindow->is_destroying();
}


oswindow g_oswindowDesktop;


bool c_xstart()
{

   Display * dpy = XOpenDisplay(NULL);

   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));

   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->window(), StructureNotifyMask);

   return true;

}



oswindow GetDesktopWindow()
{

return g_oswindowDesktop;
}
