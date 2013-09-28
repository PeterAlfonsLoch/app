#include "framework.h"

#include <X11/Xatom.h>


extern cairo_surface_t *  g_cairosurface;
extern cairo_t *  g_cairo;



























































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


void message_box_paint(cairo_surface_t * cs, stringa & stra, bool_array  & baTab, int_array  & ya,SIZE * psize)
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


	if(c ==  ::ca_cairo_keep::g_cairo)
	{
         printf("123");

	}

	cairo_destroy(c);

}

void message_box_show_xlib(const char * lpText, const char * lpCaption)
{

	Window rootwin;
	Window win;
	XEvent e;
	int32_t scr;
	cairo_surface_t *cs;


	xdisplay dpy;

	dpy.open(NULL);

	if(dpy== NULL)
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		return ;
//		exit(1);
	}

	scr         = dpy.default_screen();
	rootwin     = RootWindow(dpy.m_pdisplay, scr);


	simple_graphics g;

	g.create(NULL);

	SIZE sz;

	sz.cx = 0;
	sz.cy = 0;


	stringa stra;

	stra.add_tokens(lpText, "\n");

	bool_array baTab;

	int_array ya;

	for(index i = 0; i < stra.get_count(); i++)
	{

	   string str = stra[i];

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


	win=XCreateSimpleWindow(dpy.m_pdisplay, rootwin, 1, 1, sz.cx, sz.cy, 0, BlackPixel(dpy.m_pdisplay, scr), BlackPixel(dpy.m_pdisplay, scr));

	XStoreName(dpy, win, lpCaption);
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);

	cs = cairo_xlib_surface_create(dpy.m_pdisplay, win, DefaultVisual(dpy.m_pdisplay, 0), sz.cx, sz.cy);

	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			message_box_paint(cs, stra, baTab, ya, &sz);
		} else if(e.type==ButtonPress) break;
	}

   if(cs == ::ca_cairo_keep::g_cairosurface)
   {

      printf("123");

   }

	cairo_surface_destroy(cs);

	XCloseDisplay(dpy);

}



int32_t WINAPI MessageBoxA_x11(oswindow hWnd, const char * lpText, const char * lpCaption, UINT uType)
{

   message_box_show_xlib(lpText, lpCaption);

   return 0;

}





__attribute__((constructor))
static void initialize_x11_message_box()
{

   g_messageboxa = &::MessageBoxA_x11;

}



