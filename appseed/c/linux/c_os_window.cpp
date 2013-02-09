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


int32_t oswindow::find(Display * pdisplay, Window window)
{

   for(int32_t i = 0; i < s_pdataptra->get_count(); i++)
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

int32_t oswindow::store_name(const char * psz)
{

   return XStoreName(display(), window(), psz);

}


int32_t oswindow::select_input(int32_t iInput)
{

   return XSelectInput(display(), window(), iInput);

}


int32_t oswindow::select_all_input()
{

   return select_input(ExposureMask | ButtonPressMask);

}


int32_t oswindow::map_window()
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
   uint32_t ncount = 0;

   XQueryTree(display(), window(), &root, &parent, &pchildren, &ncount);

   if(pchildren != NULL)
      XFree(pchildren);

   return oswindow(display(), parent);

}

oswindow oswindow::set_parent(oswindow oswindow)
{

   if(m_pdata == NULL)
      return ::ca::null();

   ::oswindow oswindowOldParent = get_parent();

   XReparentWindow(display(), window(), oswindow.window(), 0, 0);

   return oswindowOldParent;

}

bool oswindow::show_window(int32_t nCmdShow)
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



LONG oswindow::get_window_long(int32_t nIndex)
{

   Atom type = 0;
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


   return l;

}


LONG oswindow::set_window_long(int32_t nIndex, LONG l)
{

   LONG lOld = get_window_long(nIndex);

   XChangeProperty(display(), window(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), m_pdata->m_osdisplay.atom_long_type(), 32, PropModeReplace, (unsigned char *) &l, 1);

   return lOld;

}


bool oswindow::client_to_screen(POINT * pp)
{

   return true;

}


bool oswindow::screen_to_client(POINT * pp)
{

   return true;

}

Atom get_window_long_atom(int32_t nIndex);




long oswindow::get_state()
{

  static const long WM_STATE_ELEMENTS = 2L;

  unsigned long nitems;
  unsigned long leftover;
  Atom xa_WM_STATE, actual_type;
  int32_t actual_format;
  int32_t status;
  unsigned char* p = NULL;

  xa_WM_STATE = XInternAtom(display(), "WM_STATE", false);

  status = XGetWindowProperty(display(), window(),
                xa_WM_STATE, 0L, WM_STATE_ELEMENTS,
                false, xa_WM_STATE, &actual_type, &actual_format,
                &nitems, &leftover, &p);

  if(status == 0)
  {
      XFree(p);
      return (p != NULL) ? (long)*p : -1;
  }

  return -1;

}




bool oswindow::is_iconic()
{

   return get_state() == IconicState;

}

bool oswindow::is_window_visible()
{

   return get_state() == IconicState || get_state() == NormalState;

}






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


#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>


#define SIZEX 100
#define SIZEY  50


void message_box_paint(cairo_surface_t * cs, stra_dup & stra, simple_array < bool >  & baTab, simple_array < int >  & ya,SIZE * psize)
{
	cairo_t *c;

	c=cairo_create(cs);
	cairo_rectangle(c, 0.0, 0.0, psize->cx, psize->cy);
	cairo_set_source_rgb(c, 0.84, 0.84, 0.77);
	cairo_fill(c);

	cairo_set_source_rgb(c, 0.0, 0.0, 0.0);

	for(index i = 0; i < stra.get_count(); i++)
	{
      cairo_move_to(c, 10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i]);
      cairo_show_text(c, stra[i]);
	}


	cairo_show_page(c);

	cairo_destroy(c);
}

void message_box_show_xlib(const char * lpText, const char * lpCaption)
{
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int32_t scr;
	cairo_surface_t *cs;

	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);


	simple_graphics g;

	g.create(NULL);

	SIZE sz;

	sz.cx = 0;
	sz.cy = 0;


	stra_dup stra;

	stra.add_tokens(lpText, "\n");

	simple_array < bool > baTab;

	simple_array < int > ya;

	for(index i = 0; i < stra.get_count(); i++)
	{

	   vsstring str = stra[i];

	   bool bTab = str_begins_dup(str, "\t");

	   str.trim();

	   bool bEmpty = str.is_empty();

	   if(bEmpty)
         str = "L";

	   SIZE sizeItem = g.get_text_extent(str);

	   int x = bTab ? 25 : 0;

	   if(sizeItem.cx + x > sz.cx)
	   {

	       sz.cx = sizeItem.cx + x;

	   }

	   baTab.add(bTab);

	   ya.add( sz.cy);

      sz.cy += sizeItem.cy;

      if(bEmpty)
      {
         stra[i] = "";
      }
      else
      {
         stra[i] = str;
      }

	}

	sz.cx += 100;
	sz.cy += 100;


	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, sz.cx, sz.cy, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, lpCaption);
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);

	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), sz.cx, sz.cy);

	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			message_box_paint(cs, stra, baTab, ya, &sz);
		} else if(e.type==ButtonPress) break;
	}

	cairo_surface_destroy(cs);
	XCloseDisplay(dpy);
}



int32_t WINAPI MessageBoxA(oswindow hWnd, const char * lpText, const char * lpCaption, UINT uType)
{

   message_box_show_xlib(lpText, lpCaption);

   return 0;

}


