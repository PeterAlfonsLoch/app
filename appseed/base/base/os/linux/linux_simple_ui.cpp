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

   simple_ui::simple_ui(sp(base_application) papp) :
      element(papp),
      interaction(papp)
   {

      m_w = 840;
      m_h = 284;
      m_window = NULL;
      m_bShiftKey = false;


   }

   simple_ui::~simple_ui()
   {
   }


   bool simple_ui::prepare_window(LPCRECT lpcrect)
   {

      oswindow hWnd;


      single_lock ml(&user_mutex());

      Display *display;
      Window rootwin;

      XEvent e;
      int32_t scr;
//      cairo_surface_t *cs;





      //single_lock sl(user_mutex(), true);


      if(!(display=XOpenDisplay(NULL)))
      {
         fprintf(stderr, "ERROR: Could not open display\n");
//            exit(1);
         return false;
      }

     xdisplay d(display);

      scr      =  DefaultScreen(display);
      rootwin  =  RootWindow(display, scr);

      //if(cs.cx <= 256)
        // cs.cx = 256;
      //if(cs.cy <= 256)
        // cs.cy = 256;

//      Window window = XCreateSimpleWindow(dpy, rootwin, 256, 256, cs.cx, cs.cy, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));

      const char * xserver = getenv( "DISPLAY" ) ;



      if (display == 0)

      {

      printf("Could not establish a connection to X-server '%s'\n", xserver ) ;

      return false;

      }



      // query Visual for "TrueColor" and 32 bits depth (RGBA)
      Visual * vis = DefaultVisual(display, DefaultScreen(display));
      int depth = 0;
      {



         if(XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_visualinfo))
         {
             vis = m_visualinfo.visual;
             depth = m_visualinfo.depth;
         }
         else
         {
            memset(&m_visualinfo, 0, sizeof(m_visualinfo));
         }


      }
      // create window

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
                           depth,
                           InputOutput,
                           vis,
                           CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel,
                           &attr);




      /*oswindow hWnd = ::CreateWindowEx(cs.dwExStyle, cs.lpszClass,
         cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy,
         cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);*/

#ifdef DEBUG
      if (window == 0)
      {
         DWORD dwLastError = GetLastError();
/*         string strLastError = FormatMessageFromSystem(dwLastError);
         string strMessage;
         strMessage.Format("%s\n\nSystem Error Code: %d", strLastError, dwLastError);

         TRACE(::core::trace::category_AppMsg, 0, "Warning: oswindow creation failed: GetLastError returned:\n");
         TRACE(::core::trace::category_AppMsg, 0, "%s\n", strMessage);
         try
         {
            if(dwLastError == 0x0000057e)
            {
               System.simple_message_box(NULL, "cannot create a top-level child window.");
            }
            else
            {
               System.simple_message_box(NULL, strMessage);
            }
         }
         catch(...)
         {
         }*/
         return false;
      }
#endif

      m_window = oswindow_get(display, window, vis);

      //m_window->set_user_interaction(m_pguie);

      XGetWindowAttributes(m_window->display(), m_window->window(), &m_attr);


      m_pgraphics = new window_cairo();

      m_iDepth = depth;

      int event_base, error_base, major_version, minor_version;

      //m_bComposite = XCompositeQueryExtension(m_oswindow->display(), &event_base, &error_base) != False
      //            && XCompositeQueryVersion(m_oswindow->display(), &major_version, &minor_version) != 0
      //            && (major_version > 0 || minor_version >= 3);

      m_bComposite = XGetSelectionOwner(m_window->display(), XInternAtom(m_window->display(), "_NET_WM_CM_S0", True));


      if(m_strText.get_length() > 0)
      {
         XStoreName(m_window->display(), m_window->window(), m_strText);
      }

      wm_nodecorations(m_window, 0);

      //XSelectInput(m_oswindow->display(), m_oswindow->window(), ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask);

      bool bShow = true;

      if(bShow)
      {
         XMapWindow(m_window->display(), m_window->window());
      }

      m_pmutexGraphics = new mutex(get_app());

d.unlock();
      ml.unlock();

   //if (!unhook_window_create())
     // PostNcDestroy();        // cleanup if CreateWindowEx fails too soon


      //send_message(WM_CREATE, 0, (LPARAM) &cs);
//      ::PostMessage(m_window, WM_CREATE, 0, 0);

//      m_pguie->SetWindowPos(0, 256, 256, cs.cx, cs.cy, 0);

  //    ::PostMessage(m_window, WM_SIZE, 0, 0);

      //LNX_THREAD(m_pthread->m_pthread->m_p.m_p)->m_oswindowa.add(m_oswindow);


//      m_window = hWnd;

  //    SetTimer(hWnd, 123, 23, NULL);

    //  ShowWindow(hWnd, SW_SHOW);

      //UpdateWindow(hWnd);

      //::SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE);


      return true;

   }




   void simple_ui::run_loop()
   {

      m_bRunLoop = true;

      XEvent e;

      while(m_bRunLoop)
      {

         if(XPending(m_window->display()) > 0)
         {

            if(XNextEvent(m_window->display(), &e))
            {

               if(e.xany.window == m_window->window())
               {

                  if(e.type==Expose && e.xexpose.count < 1)
                  {
                     on_draw_framebuffer();
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
                           on_lbutton_down(e.xbutton.x_root, e.xbutton.y_root);
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
                           on_lbutton_up(e.xbutton.x_root, e.xbutton.y_root);
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

                        on_key_down(e.xkey.keycode);
                       // lpMsg->message = WM_KEYDOWN;

                     }
                     else if(e.xkey.type == KeyRelease)
                     {

                        //lpMsg->message = WM_KEYUP;
                        on_key_up(e.xkey.keycode);

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

                     on_mouse_move(e.xmotion.x_root, e.xmotion.y_root);

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

            on_draw_framebuffer();

            Sleep(84);

         }

      }

   }


   void simple_ui::client_to_screen(POINT * ppt)
   {
      ::ClientToScreen(m_window, ppt);
   }

   void simple_ui::screen_to_client(POINT * ppt)
   {
      ::ScreenToClient(m_window, ppt);
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
      ::GetWindowRect(m_window, prect);
   }
   void simple_ui::get_client_rect(RECT * prect)
   {

      ::GetClientRect(m_window, prect);

   }


   void simple_ui::on_draw_framebuffer()
   {

      rect rectWindow;

      GetWindowRect(rectWindow);

      if(rectWindow.size() != m_size)
      {
         on_size(rectWindow.width(), rectWindow.height());
      }

      if(rectWindow.top_left() != m_pt)
      {
         on_move(rectWindow.left, rectWindow.top);
      }


      if (m_dib->get_graphics() != NULL)
      {
         RECT rectClient;
         rectClient.left = 0;
         rectClient.top = 0;
         rectClient.right = m_size.cx;
         rectClient.bottom = m_size.cy;
         m_dib->get_graphics()->set_alpha_mode(draw2d::alpha_mode_set);
         m_dib->get_graphics()->SetViewportOrg(0, 0);
         m_dib->get_graphics()->FillSolidRect(&rectClient, ARGB(0, 0, 0, 0));
         draw(m_dib->get_graphics());
         RECT rect;
         rect.left = m_pt.x;
         rect.top = m_pt.y;

         rect.right = m_pt.x + m_size.cx;
         rect.bottom = m_pt.y + m_size.cy;

         BYTE *dst = (BYTE*)m_dib->get_data();
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

         m_gdi.update_window(m_window, (COLORREF *)m_dib->get_data(), &rect);

      }

   }

   bool simple_ui::on_move(int32_t x, int32_t y)
   {

      m_pt.x = x;
      m_pt.y = y;

      return true;

   }

   bool simple_ui::on_size(int32_t cx, int32_t cy)
   {

      m_size.cx = cx;
      m_size.cy = cy;

      m_dib.create(::get_thread_app()->allocer());
      m_dib->create(m_size.cx, m_size.cy);

      m_gdi.create(m_window, cx, cy);

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
