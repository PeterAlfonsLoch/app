#include "framework.h"
#include <X11/Xatom.h>


/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


oswindow_data::oswindow_data()
{

   m_plongmap              = new int_to_int();

   m_hthread               = NULL;

   m_window                = None;

   m_pui                   = NULL;

   m_bMessageOnlyWindow    = false;

   m_bDestroying           = false;

   m_osdisplay             = NULL;

   ZERO(m_visual);

   m_iDepth                = -1;

   m_iScreen               = -1;

   m_colormap              = None;

}

oswindow_data::~oswindow_data()
{

   delete m_plongmap;

}



#define CA2_CCVOTAGUS_WINDOW_LONG "ca2_ccvotagus_fontopu_window_long"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE "ca2_ccvotagus_fontopu_window_long_style"
#define CA2_CCVOTAGUS_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_fontopu_window_long_style_ex"

oswindow_dataptra * oswindow_data::s_pdataptra = NULL;
mutex * oswindow_data::s_pmutex = NULL;


int32_t oswindow_find_message_only_window(::user::interaction * pui)
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

oswindow_data * oswindow_get_message_only_window(::user::interaction * pui)
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

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual, int iDepth, int iScreen, Colormap colormap)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind >= 0)
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_bMessageOnlyWindow      = false;
   pdata->m_osdisplay               = osdisplay_get(pdisplay);
   pdata->m_window                  = window;

   if(pvisual != NULL)
   {

      pdata->m_visual               = *pvisual;

   }

   pdata->m_iDepth                  = iDepth;
   pdata->m_iScreen                 = iScreen;
   pdata->m_colormap                = colormap;


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


bool oswindow_remove_message_only_window(::user::interaction * puibaseMessageOnlyWindow)
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


void oswindow_data::set_user_interaction(::user::interaction * pui)
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      throw "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction";

   m_pui = pui;

   m_hthread = pui->m_pthread->get_os_handle();

   oswindow_assign(this, pui->m_pimpl);

}


::user::interaction * oswindow_data::get_user_interaction_base()
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   return m_pui;

}

::user::interaction * oswindow_data::get_user_interaction_base() const
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

   return m_pui;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

   single_lock slOsWindow(s_pmutex, true);

   if(this == NULL)
      return NULL;

   return m_pui;

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

   XSync(display(), False);

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
   return (oswindow->get_user_interaction() == NULL && oswindow->display() != NULL && oswindow->window() != None)
   || (oswindow->get_user_interaction() != NULL && !oswindow->is_destroying());
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



#include "framework.h"

#include <X11/Xatom.h>


//extern cairo_surface_t *  g_cairosurface;
//extern cairo_t *  g_cairo;



























































/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Cairo)?oldid=10388
*/


//#include "cairo/cairo-xlib.h"
#include <X11/Xlib.h>


#define SIZEX 100
#define SIZEY  50


void message_box_paint(::draw2d::graphics * pdc, stringa & stra, bool_array  & baTab, int_array  & ya,SIZE * psize)
{

	pdc->FillSolidRect(0, 0, psize->cx, psize->cy, RGB(84, 84, 77));

   draw2d::brush_sp pen(pdc->allocer());

	pen->create_solid(0);

	for(index i = 0; i < stra.get_count(); i++)
	{
      pdc->TextOut(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
	}



}



int32_t message_box_show_xlib(::base::application * papp, const char * lpText, const char * lpCaption);


int32_t WINAPI MessageBoxA_x11(oswindow hWnd, const char * lpText, const char * lpCaption, UINT uType)
{

   ::base::application * papp = NULL;

   if(hWnd == NULL || hWnd->get_user_interaction() == NULL || hWnd->get_user_interaction()->get_app() == NULL)
   {

      papp = get_thread_app();

   }
   else
   {

      papp = hWnd->get_user_interaction()->get_app();

   }

   return message_box_show_xlib(get_thread_app(), lpText, lpCaption);

}





__attribute__((constructor))
static void initialize_x11_message_box()
{

   g_messageboxa = &::MessageBoxA_x11;

}





#include "framework.h"

#include <X11/Xatom.h>


//extern cairo_surface_t *  g_cairosurface;
//extern cairo_t *  g_cairo;




























































void wm_nodecorations(oswindow w,int map)
{
   Atom WM_HINTS;
   int set;


   single_lock sl(&user_mutex(),true);

   xdisplay d(w->display());
   Display * dpy = w->display();
   Window window = w->window();

   int scr=DefaultScreen(dpy);
   Window rootw=RootWindow(dpy,scr);

   WM_HINTS = XInternAtom(dpy,"_MOTIF_WM_HINTS",True);
   if(WM_HINTS != None) {
#define MWM_HINTS_DECORATIONS   (1L << 1)
      struct {
         unsigned long flags;
         unsigned long functions;
         unsigned long decorations;
         long input_mode;
         unsigned long status;
      } MWMHints ={MWM_HINTS_DECORATIONS,0,
         MWM_DECOR_NONE,0,0};
      XChangeProperty(dpy,window,WM_HINTS,WM_HINTS,32,
         PropModeReplace,(unsigned char *)&MWMHints,
         sizeof(MWMHints) / 4);
   }
//   WM_HINTS = XInternAtom(dpy,"KWM_WIN_DECORATION",True);
  // if(WM_HINTS != None) {
    //  long KWMHints = KDE_tinyDecoration;
      //XChangeProperty(dpy,window,WM_HINTS,WM_HINTS,32,
        // PropModeReplace,(unsigned char *)&KWMHints,
        // sizeof(KWMHints) / 4);
   //}

   WM_HINTS = XInternAtom(dpy,"_WIN_HINTS",True);
   if(WM_HINTS != None) {
      long GNOMEHints = 0;
      XChangeProperty(dpy,window,WM_HINTS,WM_HINTS,32,
         PropModeReplace,(unsigned char *)&GNOMEHints,
         sizeof(GNOMEHints) / 4);
   }
   WM_HINTS = XInternAtom(dpy,"_NET_WM_WINDOW_TYPE",True);
   if(WM_HINTS != None) {
      Atom NET_WMHints[2];
      NET_WMHints[0] = XInternAtom(dpy,
         "_KDE_NET_WM_WINDOW_TYPE_OVERRIDE",True);
      NET_WMHints[1] = XInternAtom(dpy,"_NET_WM_WINDOW_TYPE_NORMAL",True);
      XChangeProperty(dpy,window,
         WM_HINTS,XA_ATOM,32,PropModeReplace,
         (unsigned char *)&NET_WMHints,2);
   }
   XSetTransientForHint(dpy,window,rootw);
   if(map)
   {
      XUnmapWindow(dpy,window);
      XMapWindow(dpy,window);

   }
}
