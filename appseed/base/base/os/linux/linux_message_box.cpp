#include "framework.h"

#include <X11/Xlib.h>

#define SIZEX 100
#define SIZEY  50


void message_box_paint(Display *dpy, Window win, const char * lpText)
{

   GC gc = XCreateGC(dpy, win, 0, NULL);

   int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
   int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));


   XSetForeground(dpy, gc, whiteColor);
   XSetBackground(dpy, gc, whiteColor);

   XFillRectangle(dpy, win, gc, 0, 0, SIZEX, SIZEY);

   XSetForeground(dpy, gc, blackColor);
   XSetBackground(dpy, gc, blackColor);

   XDrawString(dpy, win, gc, 10, 10, lpText, strlen(lpText));

   XFlush(dpy);


   XFreeGC(dpy, gc);

}

void message_box_show_xlib(::base::application * papp, const char * lpText,const char * lpCaption)
{
   Display *dpy;
   Window rootwin;
   Window win;
   XEvent e;
   int scr;

   if(!(dpy=XOpenDisplay(NULL))) {
      fprintf(stderr,"ERROR: Could not open display\n");
      exit(1);
   }

   scr=DefaultScreen(dpy);
   rootwin=RootWindow(dpy,scr);

   win=XCreateSimpleWindow(dpy,rootwin,1,1,SIZEX,SIZEY,0,
      BlackPixel(dpy,scr),BlackPixel(dpy,scr));

   XStoreName(dpy,win,lpCaption);
   XSelectInput(dpy,win,ExposureMask | ButtonPressMask);
   XMapWindow(dpy,win);


   while(1) {
      XNextEvent(dpy,&e);
      if(e.type == Expose && e.xexpose.count<1) {
         message_box_paint(dpy, win,lpText);
      }
      else if(e.type == ButtonPress) break;
   }

   XCloseDisplay(dpy);


}


