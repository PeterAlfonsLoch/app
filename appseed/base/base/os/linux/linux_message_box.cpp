
#define SIZEX 100
#define SIZEY  50


void message_box_paint(cairo_surface_t * cs,const char * lpText)
{
   cairo_t *c;

   c=cairo_create(cs);
   cairo_rectangle(c,0.0,0.0,SIZEX,SIZEY);
   cairo_set_source_rgb(c,0.0,0.0,0.5);
   cairo_fill(c);

   cairo_move_to(c,10.0,10.0);
   cairo_set_source_rgb(c,1.0,1.0,0.0);
   cairo_show_text(c,lpText);

   cairo_show_page(c);

   cairo_destroy(c);
}

void message_box_show_xlib(const char * lpText,const char * lpCaption)
{
   Display *dpy;
   Window rootwin;
   Window win;
   XEvent e;
   int scr;
   cairo_surface_t *cs;

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

   cs=cairo_xlib_surface_create(dpy,win,DefaultVisual(dpy,0),SIZEX,SIZEY);

   while(1) {
      XNextEvent(dpy,&e);
      if(e.type == Expose && e.xexpose.count<1) {
         message_box_paint(cs,lpText);
      }
      else if(e.type == ButtonPress) break;
   }

   cairo_surface_destroy(cs);
   XCloseDisplay(dpy);
}


