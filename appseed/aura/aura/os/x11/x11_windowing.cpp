#include "framework.h"


//http://rosettacode.org/wiki/Window_creation/X11

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int display_line(const string & str, const string & strTitle)
{
   Display *d;
   Window w;
   XEvent e;
   int s;

   d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      return 0;
   }

   s = DefaultScreen(d);
   w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);
   XStoreName(d, w, strTitle);


   while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
         XDrawString(d, w, DefaultGC(d, s), 10, 50, str, str.length());
      }
      if (e.type == KeyPress)
         break;
   }

   XCloseDisplay(d);
   return 0;
}

int display_lines(const stringa & stra, const string & strTitle)
{
   Display *d;
   Window w;
   XEvent e;
   int s;

   d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      return 0;
   }

   s = DefaultScreen(d);
   w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);
   XStoreName(d, w, strTitle);

   while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
         for(index i = 0; i < stra; i++)
         {
            XDrawString(d, w, DefaultGC(d, s), 10, 50 + i * 25, stra[i], stra[i].length());
         }
      }
      if (e.type == KeyPress)
         break;
   }

   XCloseDisplay(d);
   return 0;
}


int_bool MessageBoxA(oswindow interaction_impl, const char * psz, const char * pszTitle, uint32_t uiFlags)
{

   stringa straSep;

   straSep.add("\n");
   straSep.add("\r");
   straSep.add("\r\n");
   straSep.add("\n\r");

   stringa stra;

   stra.add_smallest_tokens(psz, straSep);

   return display_lines(stra, pszTitle);

}


