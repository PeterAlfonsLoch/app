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

namespace os
{

   map < oswindow, oswindow, simple_ui *, simple_ui * > m_windowmap;

   simple_ui::simple_ui(sp(::base::application) papp) :
      element(papp),
      interaction(papp)
   {

      m_w = 840;
      m_h = 284;
      m_window = NULL;
      m_bShiftKey = false;

      m_bNoDecorations = false;

      ZERO(m_size);
      ZERO(m_pt);


   }

   simple_ui::~simple_ui()
   {

      ::DestroyWindow(m_window);

   }


   bool simple_ui::create_window(LPCRECT lpcrect)
   {

      single_lock ml(&user_mutex());

      Display *display;

      Window rootwin;

      XEvent e;

      if(!(display = XOpenDisplay(NULL)))
      {

         fprintf(stderr, "ERROR: Could not open display\n");

         return false;

      }

      xdisplay d(display);

      m_iScreen            =  DefaultScreen(display);

      rootwin              =  RootWindow(display, m_iScreen);

      const char * xserver = getenv( "DISPLAY" ) ;

      if (display == 0)
      {

         printf("Could not establish a connection to X-server '%s'\n", xserver ) ;

         return false;

      }

      // query Visual for "TrueColor" and 32 bits depth (RGBA)
      Visual * vis = DefaultVisual(display, m_iScreen);

      m_iDepth = 0;

      {

         if(XMatchVisualInfo(display, m_iScreen, 32, TrueColor, &m_visualinfo))
         {

             vis = m_visualinfo.visual;

         }
         else
         {

            memset(&m_visualinfo, 0, sizeof(m_visualinfo));

         }

      }

      m_iDepth = m_visualinfo.depth;

      XSetWindowAttributes attr;

      ZERO(attr);

      attr.colormap = XCreateColormap( display, rootwin, vis, AllocNone);

      attr.event_mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask;

      attr.background_pixmap = None ;

      attr.border_pixmap = None;

      attr.border_pixel = 0 ;

      attr.override_redirect = True;

      Window window = XCreateWindow(
                           display,
                           DefaultRootWindow(display),
                           lpcrect->left,
                           lpcrect->top,
                           width(lpcrect),
                           height(lpcrect),
                           0,
                           m_iDepth,
                           InputOutput,
                           vis,
                           CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel,
                           &attr);



      if (window == 0)
      {

         return false;

      }

      m_pt.x = lpcrect->left;
      m_pt.y = lpcrect->top;
      m_size.cx = width(lpcrect);
      m_size.cy = height(lpcrect);

      m_rectWindow = *lpcrect;
      m_rectWindow.deflate(1, 1); // make intentionally different from actual rect to trigger simple_ui on_move and on_size events

      m_window = oswindow_get(display, window, vis, m_iDepth, m_iScreen, attr.colormap);

      return true;

   }


   bool simple_ui::show_window(bool bShow)
   {

      if(!::simple_ui::interaction::show_window(bShow))
         return false;

      if(bShow)
      {

         SetWindowPos(m_window, NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW | SWP_NOZORDER);

      }
      else
      {

         ShowWindow(m_window, SW_HIDE);

      }

      return true;

   }



   bool simple_ui::prepare_window(LPCRECT lpcrect)
   {

      single_lock ml(&user_mutex());

      XGetWindowAttributes(m_window->display(), m_window->window(), &m_attr);

      m_pgraphics = new window_xlib();

      m_bComposite = XGetSelectionOwner(m_window->display(), XInternAtom(m_window->display(), "_NET_WM_CM_S0", True));

      if(m_strText.get_length() > 0)
      {
         XStoreName(m_window->display(), m_window->window(), m_strText);
      }

      m_pmutexGraphics = new mutex(get_app());

      //on_size(width(lpcrect), height(lpcrect));

      //on_move(lpcrect->left, lpcrect->top);

      xdisplay d(m_window->display());

      XGetWindowAttributes(m_window->display(), m_window->window(), &m_attr);

      m_pgraphics = new window_xlib();

      if(m_bNoDecorations)
      {

         wm_nodecorations(m_window, 0);

      }

      //bool bShow = true;

//      XMoveResizeWindow(m_window->display(), m_window->window(), m_rectDesktop.right-m_pt.x, m_rectDesktop.bottom-m_pt.y, m_size.cx, m_size.cy);

      //XMoveResizeWindow(m_window->display(), m_window->window(), 500, 0, 200, 200);


      //if(bShow)
      //{

        // XMapWindow(m_window->display(), m_window->window());

      //}

      d.unlock();

      ml.unlock();

      m_bVisible = true;

      return true;

   }


#define MAX_MAPPED_STRING_LENGTH 500

   void simple_ui::run_loop()
   {

      m_bRunLoop = true;

      XEvent e;

      char buffer[MAX_MAPPED_STRING_LENGTH];
      int bufsize=MAX_MAPPED_STRING_LENGTH;
      KeySym keysym;
      XComposeStatus compose;

      single_lock sl(&user_mutex(), false);

      xdisplay x(m_window->display(), false);

      bool bEnableFB = false;

      while(m_bRunLoop)
      {

         {

            sl.lock();

            x.lock();

            if(XPending(m_window->display()) > 0)
            {

               if(XNextEvent(m_window->display(), &e) == Success)
               {

                  x.unlock();

                  sl.unlock();

                  if(e.xany.window == m_window->window())
                  {

                     if(e.type==Expose && e.xexpose.count < 1)
                     {

                        bEnableFB = true;

                     //   on_draw_framebuffer();
                     }
                     else if(e.type == ButtonPress || e.type == ButtonRelease)
                     {

   //                     bRet                 = true;
   //                     if(bRet)
                        {

           //                lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
         //                  lpMsg->wParam        = 0;
             //              lpMsg->lParam        = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);

                        }

                        if(e.xbutton.type == ButtonPress)
                        {
                           if(e.xbutton.button == Button1)
                           {
                              on_lbutton_down(e.xbutton.x, e.xbutton.y);
                           }
                           else if(e.xbutton.button == Button2)
                           {
                     //         lpMsg->message = WM_MBUTTONDOWN;
                           }
                           else if(e.xbutton.button == Button3)
                           {
                       //       lpMsg->message = WM_RBUTTONDOWN;
                           }
                           else
                           {
                         //     bRet = false;
                           }

                        }
                        else if(e.xbutton.type == ButtonRelease)
                        {
                           if(e.xbutton.button == Button1)
                           {
                              on_lbutton_up(e.xbutton.x, e.xbutton.y);
                           }
                           else if(e.xbutton.button == Button2)
                           {
                              //lpMsg->message = WM_MBUTTONUP;
                           }
                           else if(e.xbutton.button == Button3)
                           {
                              //lpMsg->message = WM_RBUTTONUP;
                           }
                           else
                           {
                              //bRet = false;
                           }

                        }
                        else
                        {

                           //bRet = false;

                        }



                     }
                     else if(e.type == KeyPress || e.type == KeyRelease)
                     {

                        //oswindow w = oswindow_get(display, e.xexpose.window);

   //                     bRet                 = true;

                        if(e.xkey.type == KeyPress)
                        {

                           int count = XLookupString(&e.xkey, buffer, bufsize, &keysym, &compose);
                           if(keysym == XK_Tab)
                           {
                              //on_key_down(VK_TAB);
                              on_char(::user::key_tab, "");

                           }
                           else if(keysym == XK_Return)
                           {
                              //on_key_down(VK_RETURN);
                              on_char(::user::key_return, "");
                           }
                           else if(keysym == XK_BackSpace)
                           {
                              //on_key_down(VK_RETURN);
                              on_char(::user::key_back, "");
                           }
                           else if(keysym == XK_Delete)
                           {
                              //on_key_down(VK_RETURN);
                              on_char(::user::key_delete, "");
                           }
                           else if(keysym == XK_Shift_L || keysym == XK_Shift_R)
                           {
                              on_key_down(::user::key_shift);
                           }
                           else
                           {
                              if(strlen(buffer) > 0)
                              {
                                 on_char(0, buffer);
                                 buffer[0] = '\0';
                              }
                           }
                          // lpMsg->message = WM_KEYDOWN;

                        }
                        else if(e.xkey.type == KeyRelease)
                        {

                           //lpMsg->message = WM_KEYUP;
                           if(keysym == XK_Tab)
                           {
                              //on_key_up(VK_TAB);

                           }
                           else if(keysym == XK_Return)
                           {
                              //on_key_up(VK_RETURN);
                           }
                           else if(keysym == XK_Shift_L || keysym == XK_Shift_R)
                           {
                              on_key_up(::user::key_shift);
                           }

                        }
                        else
                        {

   //                        bRet = false;

                        }

                        //lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                        //lpMsg->wParam        = e.xkey.keycode;
                        //lpMsg->lParam        = MAKELONG(0, e.xkey.keycode);



                     }
                     else if(e.type == MotionNotify)
                     {

                        //lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                        //lpMsg->message       = WM_MOUSEMOVE;
                        //lpMsg->wParam        = 0;
                        //lpMsg->lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);

                        on_mouse_move(e.xmotion.x, e.xmotion.y);

                        //bRet                 = true;

                     }
                     else if(e.type == DestroyNotify)
                     {

                        //lpMsg->hwnd          = oswindow_get(display, e.xdestroywindow.window);
                        //lpMsg->message       = WM_DESTROY;

                        m_bRunLoop = false;

                        //bRet                 = true;

                     }

                     //if(bPeek && bRet)
                       // XPutBackEvent(display, &e);



                  }


               }

            }
            else
            {

               x.unlock();

               sl.unlock();

               if(bEnableFB && m_bVisible)
               {

                  on_draw_framebuffer();

               }

               Sleep(5);

            }

         }

      }

   }


   void simple_ui::client_to_screen(POINT * ppt)
   {
      //::ClientToScreen(m_window, ppt);
      ::simple_ui::interaction::client_to_screen(ppt);
   }

   void simple_ui::screen_to_client(POINT * ppt)
   {
      //::ScreenToClient(m_window, ppt);
      ::simple_ui::interaction::screen_to_client(ppt);
   }

   bool simple_ui::on_key_down(uint32_t uiKey)
   {
      if (uiKey == 12) // VKSHIFT
      {
         m_bShiftKey = true;
      }
      else if (uiKey == 13) // VK_ESCAPE)
      {
         on_action("escape");
      }

      return false;

   }

   bool simple_ui::on_key_up(uint32_t uiKey)
   {

      string str;
      //wchar_t wsz[32];

      BYTE baState[256];

      ZERO(baState);
      for (int i = 0; i < 256; i++)
      {
//         baState[i] = (BYTE)GetAsyncKeyState(i);
      }

      baState[uiKey & 0xff] = 0x80;

      /*if((GetAsyncKeyState(::user::key_shift) & 0x80000000) != 0)
      {
      baState[::user::key_shift] |= 0x80;
      }
      */
      if (m_bShiftKey)
      {
         baState[VK_SHIFT] |= 0x80;
      }

      char sz[2];


      sz[0] = uiKey;
      sz[1]  = '\0';

      //int32_t iRet = ToUnicodeEx((UINT)wparam, 0, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));
      str = sz;
      on_char(static_cast<UINT>(uiKey), str);

      if (m_bShiftKey && uiKey == VK_SHIFT)
      {
         m_bShiftKey = false;
      }


      return false;

   }



   void simple_ui::GetWindowRect(RECT * prect)
   {

      *prect = m_rectWindow;

   }
   void simple_ui::get_client_rect(RECT * prect)
   {

      *prect = m_rectWindow;

      prect->right -= prect->left;
      prect->bottom -= prect->top;
      prect->left = 0;
      prect->top = 0;

   }


   void simple_ui::on_draw_framebuffer()
   {

      rect rectWindow;

      ::GetWindowRect(m_window, rectWindow);

      if(rectWindow.size() != m_rectWindow.size())
      {

         on_size(rectWindow.width(), rectWindow.height());

      }

      if(rectWindow.top_left() != m_rectWindow.top_left())
      {

         on_move(rectWindow.left, rectWindow.top);

      }

      m_rectWindow = rectWindow;


      if (m_dib.is_set() && m_dib->get_graphics() != NULL)
      {

         rect rectClient = rectWindow;

         rectClient -= rectWindow.top_left();

         rect rect;

         rect = rectWindow;

         m_dib->get_graphics()->set_alpha_mode(draw2d::alpha_mode_set);

         m_dib->get_graphics()->SetViewportOrg(0, 0);

         m_dib->get_graphics()->FillSolidRect(&rectClient, ARGB(255, 255, 255, 255));

         draw(m_dib->get_graphics());

         //m_dib->map();

         m_dib->fill_channel(255, ::visual::rgba::channel_alpha);

         //m_dib->Fill(255, 184, 184, 177);

         BYTE *dst = (BYTE*) m_dib->get_data();

         int64_t size = m_size.cx * m_size.cy;


         // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


         while (size >= 8)
         {
            dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3]) >> 8);
            dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3]) >> 8);
            dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3]) >> 8);

            dst[4 + 0] = LOBYTE(((int32_t)dst[4 + 0] * (int32_t)dst[4 + 3]) >> 8);
            dst[4 + 1] = LOBYTE(((int32_t)dst[4 + 1] * (int32_t)dst[4 + 3]) >> 8);
            dst[4 + 2] = LOBYTE(((int32_t)dst[4 + 2] * (int32_t)dst[4 + 3]) >> 8);

            dst[8 + 0] = LOBYTE(((int32_t)dst[8 + 0] * (int32_t)dst[8 + 3]) >> 8);
            dst[8 + 1] = LOBYTE(((int32_t)dst[8 + 1] * (int32_t)dst[8 + 3]) >> 8);
            dst[8 + 2] = LOBYTE(((int32_t)dst[8 + 2] * (int32_t)dst[8 + 3]) >> 8);

            dst[12 + 0] = LOBYTE(((int32_t)dst[12 + 0] * (int32_t)dst[12 + 3]) >> 8);
            dst[12 + 1] = LOBYTE(((int32_t)dst[12 + 1] * (int32_t)dst[12 + 3]) >> 8);
            dst[12 + 2] = LOBYTE(((int32_t)dst[12 + 2] * (int32_t)dst[12 + 3]) >> 8);

            dst[16 + 0] = LOBYTE(((int32_t)dst[16 + 0] * (int32_t)dst[16 + 3]) >> 8);
            dst[16 + 1] = LOBYTE(((int32_t)dst[16 + 1] * (int32_t)dst[16 + 3]) >> 8);
            dst[16 + 2] = LOBYTE(((int32_t)dst[16 + 2] * (int32_t)dst[16 + 3]) >> 8);

            dst[20 + 0] = LOBYTE(((int32_t)dst[20 + 0] * (int32_t)dst[20 + 3]) >> 8);
            dst[20 + 1] = LOBYTE(((int32_t)dst[20 + 1] * (int32_t)dst[20 + 3]) >> 8);
            dst[20 + 2] = LOBYTE(((int32_t)dst[20 + 2] * (int32_t)dst[20 + 3]) >> 8);

            dst[24 + 0] = LOBYTE(((int32_t)dst[24 + 0] * (int32_t)dst[24 + 3]) >> 8);
            dst[24 + 1] = LOBYTE(((int32_t)dst[24 + 1] * (int32_t)dst[24 + 3]) >> 8);
            dst[24 + 2] = LOBYTE(((int32_t)dst[24 + 2] * (int32_t)dst[24 + 3]) >> 8);

            dst[28 + 0] = LOBYTE(((int32_t)dst[28 + 0] * (int32_t)dst[28 + 3]) >> 8);
            dst[28 + 1] = LOBYTE(((int32_t)dst[28 + 1] * (int32_t)dst[28 + 3]) >> 8);
            dst[28 + 2] = LOBYTE(((int32_t)dst[28 + 2] * (int32_t)dst[28 + 3]) >> 8);

            dst += 4 * 8;
            size -= 8;
         }
         while (size--)
         {
            dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3]) >> 8);
            dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3]) >> 8);
            dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3]) >> 8);
            dst += 4;
         }

         m_xlib.update_window(m_window, (COLORREF *)m_dib->get_data(), &rect, m_dib->m_iScan);

      }

   }

   bool simple_ui::on_move(int32_t x, int32_t y)
   {

      m_pt.x = x;
      m_pt.y = y;

      m_rect.left = m_pt.x;
      m_rect.right = m_pt.x + m_size.cx;
      m_rect.top = m_pt.y;
      m_rect.bottom = m_pt.y + m_size.cy;

      return true;

   }

   bool simple_ui::on_size(int32_t cx, int32_t cy)
   {

      m_size.cx = cx;
      m_size.cy = cy;

      m_rect.left = m_pt.x;
      m_rect.right = m_pt.x + m_size.cx;
      m_rect.top = m_pt.y;
      m_rect.bottom = m_pt.y + m_size.cy;

      m_dib.create(::get_thread_app()->allocer());
      m_dib->create(m_size.cx, m_size.cy);

      m_xlib.create(m_window, cx, cy);

      layout();

      return true;

   }


   void simple_ui::set_capture()
   {

      ::SetCapture(m_window);

   }


   void simple_ui::release_capture()
   {

      ::ReleaseCapture();

   }


   bool simple_ui::destroy_window()
   {

      if(m_bRunLoop)
      {

         m_bRunLoop = false;

      }

      bool b = ::DestroyWindow(m_window) != FALSE;

      m_window = NULL;

      return b;

   }


   bool simple_ui::move_window(int32_t x, int32_t y)
   {

      ::SetWindowPos(m_window, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      m_rect.left = x;
      m_rect.top = y;
      m_rect.right = x + m_size.cx;
      m_rect.bottom = y + m_size.cy;

      m_pt.x = x;
      m_pt.y = y;

      return true;

   }


   bool simple_ui::set_window_pos(int32_t x, int32_t y, int32_t cx, int32_t cy, bool bShow)
   {

      ::SetWindowPos(m_window, NULL, x, y, cx, cy, SWP_NOZORDER | (bShow ? SWP_SHOWWINDOW : 0));

      return true;

   }



} // namespace os






void wm_nodecorations(oswindow w, int map)
{
    Atom WM_HINTS;
    int set;


   single_lock sl(&user_mutex(), true);

xdisplay d(w->display());
    Display * dpy = w->display();
    Window window = w->window();

   int scr=DefaultScreen(dpy);
   Window rootw=RootWindow(dpy, scr);

    WM_HINTS = XInternAtom(dpy, "_MOTIF_WM_HINTS", True);
    if ( WM_HINTS != None ) {
        #define MWM_HINTS_DECORATIONS   (1L << 1)
        struct {
          unsigned long flags;
          unsigned long functions;
          unsigned long decorations;
                   long input_mode;
          unsigned long status;
        } MWMHints = { MWM_HINTS_DECORATIONS, 0,
            MWM_DECOR_NONE, 0, 0 };
        XChangeProperty(dpy, window, WM_HINTS, WM_HINTS, 32,
                        PropModeReplace, (unsigned char *)&MWMHints,
                        sizeof(MWMHints)/4);
    }
    WM_HINTS = XInternAtom(dpy, "KWM_WIN_DECORATION", True);
    if ( WM_HINTS != None ) {
        long KWMHints = KDE_tinyDecoration;
        XChangeProperty(dpy, window, WM_HINTS, WM_HINTS, 32,
                        PropModeReplace, (unsigned char *)&KWMHints,
                        sizeof(KWMHints)/4);
    }

    WM_HINTS = XInternAtom(dpy, "_WIN_HINTS", True);
    if ( WM_HINTS != None ) {
        long GNOMEHints = 0;
        XChangeProperty(dpy, window, WM_HINTS, WM_HINTS, 32,
                        PropModeReplace, (unsigned char *)&GNOMEHints,
                        sizeof(GNOMEHints)/4);
    }
    WM_HINTS = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", True);
    if ( WM_HINTS != None ) {
        Atom NET_WMHints[2];
        NET_WMHints[0] = XInternAtom(dpy,
            "_KDE_NET_WM_WINDOW_TYPE_OVERRIDE", True);
        NET_WMHints[1] = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_NORMAL", True);
        XChangeProperty(dpy, window,
                        WM_HINTS, XA_ATOM, 32, PropModeReplace,
                        (unsigned char *)&NET_WMHints, 2);
    }
    XSetTransientForHint(dpy, window, rootw);
    if(map)
    {
    XUnmapWindow(dpy, window);
    XMapWindow(dpy, window);

    }
 }
