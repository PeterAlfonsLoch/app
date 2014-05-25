#include "framework.h"

#include <X11/Xlib.h>

#define SIZEX 584
#define SIZEY 384

namespace simple_ui
{

   class CLASS_DECL_BASE message_box :
      virtual public ::simple_ui::interaction
   {
   public:

      stringa m_stra;

      sp(tap) m_ptap;

     message_box(sp(::base::application) papp);
     virtual ~message_box();


     bool show(const char * pszMessage, uint32_t uiFlags);

     DRAWDD();

     virtual void layout();

      bool on_action(const char * pszId);

   };


} // namespace simple_ui


namespace simple_ui
{

   message_box::message_box(sp(::base::application) papp) :
      element(papp)
   {
   m_ptap = new ::simple_ui::tap(get_app());
   }

   message_box::~message_box()
   {
   }

   bool message_box::show(const char * pszMessage, uint32_t uiFlags)
   {
      Application.defer_initialize_twf();

      if(!CreateEx(WS_EX_LAYERED, NULL, NULL, 0, null_rect(), NULL, "fontopus"))
         return "";


         m_ptap->create(this, "ok");

         m_ptap->SetWindowText("OK");

      ::rect rectDesktop;

      stringa stra;
      stra.add("\r");

      stra.add("\n");
      stra.add("\r\n");

      m_stra.add_smallest_tokens(pszMessage, stra);

      System.get_monitor_rect(0,&rectDesktop);

      SetWindowText( "fontopus Auth Windows");

      rect rectFontopus;

      int stdw = 884;

      int stdh = 184 + 23 + 184;

      int w = stdw;

      int h = stdh;

      //double d = (double) w / (double) h;

      if(w > rectDesktop.width())
      {

         w = rectDesktop.width();

//         if(d != 0.0)
  //       {

    //        h = (int) (w / d);

      //   }

      }

      if(h > rectDesktop.height())
      {

         h = rectDesktop.height();

        // w = (int) (h  * d);

      }


      rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;
      rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;
      rectFontopus.right = rectFontopus.left + w;
      rectFontopus.bottom = rectFontopus.top + h;



      SetWindowPos(ZORDER_TOP, rectFontopus, SWP_SHOWWINDOW);

      SetForegroundWindow();

      BringWindowToTop();

      BringToTop(SW_NORMAL);

      RunModalLoop();

      return "";
   }


   void message_box::_001OnDraw(::draw2d::graphics * pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient, ARGB(255, 0xcc, 0xcc, 0xc5));

      sp(::draw2d::font) font(allocer());

      font->create_point_font("Arial", 12);

      pdc->selectFont(font);

      ::draw2d::text_metric tm;

      pdc->get_text_metrics(&tm);

      int iHeight = tm.tmHeight;

      int y = 10;

      for(int i = 0; i < m_stra.get_size(); i++)
      {

         pdc->TextOut(10, y, m_stra[i]);

         y+= iHeight;

      }



   }

   void message_box::layout()
   {

         rect rectClient;

      GetClientRect(rectClient);


      m_ptap->SetWindowPos(ZORDER_TOP, rectClient.left + 10, rectClient.bottom - 94, 200, 84, SWP_SHOWWINDOW);


   }

   bool message_box::on_action(const char * pszId)
   {
      if(stricmp_dup(pszId, "ok") ==         0)
      {
      EndModalLoop(IDOK);
      }
   }


} // namespace simple_ui
/*
void message_box_paint(Display *dpy, Window win;, const char * lpText)
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
*/

void message_box_show_xlib(::base::application * papp, const char * lpText,const char * lpCaption)
{



   ::simple_ui::message_box m(papp);

   m.show(lpText, 0);

   return;

/*



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

*/
}


