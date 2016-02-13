#include "framework.h"


void process_message(Display * pdisplay);
void post_message(MESSAGE & msg);

UINT __axis_x11_thread(void * p)
{

   osdisplay_data * pdata = (osdisplay_data *) p;

   Display * display = pdata->display();

   if(display == NULL)
   {

      return 0;

   }

   int x11_fd = ConnectionNumber(display);

   fd_set in_fds;

   MESSAGE msg;

   struct timeval tv;

   while(::aura::system::g_p != NULL && ::aura::system::g_p->m_bRun)
   {

//      ZERO(msg);
//
//      FD_ZERO(&in_fds);
//
//      FD_SET(x11_fd, &in_fds);
//
//      tv.tv_usec = 0;
//
//      tv.tv_sec = 1;
//
//      int num_ready_fds = select(x11_fd + 1, &in_fds, NULL, NULL, &tv);
//
//      if (num_ready_fds > 0)
//      {
//
//         // Event Received
//
//      }
//      else if (num_ready_fds == 0)
//      {
//
//         // Timer fired
//
//      }
//      else
//      {
//
//         // Error
//
//      }

      {

         while(XPending(display))
         {

            process_message(display);

         }

         Sleep(1);

      }

   }

}


void process_message(Display * display)
{

   xdisplay d(display);
   //if(!XPending(display))
   //return false;


   XEvent e;

   MESSAGE msg;

   ZERO(msg);

   XNextEvent(display, &e);
         //xdisplay d(display);

   bool bRet = false;

   if(e.type == Expose)
   {

      msg.message       = WM_PAINT;
      msg.hwnd          = oswindow_get(display, e.xbutton.window);
      msg.lParam        = 0;
      msg.wParam        = 0;

      post_message(msg);

   }
   else if(e.type == MapNotify)
   {
//      xdisplay d(display());

  // if(d.m_pdata->m_pdisplay == NULL)
    //return false;
//      oswindow window = oswindow_get(display, e.xbutton.window);
//
//   XWindowAttributes attr;
//   if(XGetWindowAttributes(display, e.xbutton.window, &attr))
//   {
//   window->get_user_interaction()->m_bVisible = attr.map_state == IsViewable;
//
//   }
//   window->get_user_interaction()->m_pimpl->m_bVisible = attr.map_state == IsViewable;

   }
   else if(e.type == ConfigureNotify)
   {

      if(e.xconfigure.window == g_oswindowDesktop->window())
      {

         for(int j = 0; j < ::oswindow_data::s_pdataptra->get_count(); j++)
         {

            PostMessage(::oswindow_data::s_pdataptra->element_at(j), WM_DISPLAYCHANGE, 0, 0);

         }


      }

//      oswindow window = oswindow_get(display, e.xbutton.window);
//
//      XWindowAttributes attrs;

      /* Fill attribute structure with information about root window */

//      if(XGetWindowAttributes(window->display(), window->window(), &attrs))
//      {
//
//      int x;
//      int y;
//      Window child;
//
//      if(XTranslateCoordinates(window->display(), window->window(), DefaultRootWindow(window->display()), 0, 0, &x, &y, &child))
//      {
//
//
//      window->m_rect.left      = x;
//      window->m_rect.top       = y;
//      window->m_rect.right     = x    + attrs.width;
//      window->m_rect.bottom    = y    + attrs.height;
//
//
//      }
//
//      }

   }
   else if(e.type == ButtonPress || e.type == ButtonRelease)
   {

      bRet                 = true;

      if(e.xbutton.type == ButtonPress)
      {

         if(e.xbutton.button == Button1)
         {

            msg.message = WM_LBUTTONDOWN;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = WM_MBUTTONDOWN;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = WM_RBUTTONDOWN;

         }
         else
         {

            bRet = false;

         }

      }
      else if(e.xbutton.type == ButtonRelease)
      {

         if(e.xbutton.button == Button1)
         {

            msg.message = WM_LBUTTONUP;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = WM_MBUTTONUP;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = WM_RBUTTONUP;

         }
         else
         {

            bRet = false;

         }

      }
      else
      {

         bRet = false;

      }


      if(bRet)
      {

         msg.hwnd          = oswindow_get(display, e.xbutton.window);
         msg.wParam        = 0;
         msg.lParam        = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);

         post_message(msg);

      }

   }
   else if(e.type == KeyPress || e.type == KeyRelease)
   {

      oswindow w = oswindow_get(display, e.xexpose.window);

      bRet                 = true;

      if(e.xkey.type == KeyPress)
      {

         msg.message = WM_KEYDOWN;

      }
      else if(e.xkey.type == KeyRelease)
      {

         msg.message = WM_KEYUP;

      }
      else
      {

         bRet = false;

      }

      if(bRet)
      {

         msg.hwnd          = oswindow_get(display, e.xbutton.window);
         msg.wParam        = e.xkey.keycode;
         msg.lParam        = MAKELONG(0, e.xkey.keycode);

         post_message(msg);

      }
   }
   else if(e.type == MotionNotify)
   {

      msg.hwnd          = oswindow_get(display, e.xbutton.window);
      msg.message       = WM_MOUSEMOVE;
      msg.wParam        = 0;
      msg.lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);

      post_message(msg);

   }
   else if(e.type == DestroyNotify)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_DESTROY;

      post_message(msg);

   }


}








void post_message(MESSAGE & msg)
{

   try
   {

      if(msg.hwnd == NULL)
      {

         ::aura::system::g_p->post_thread_message(msg.message, msg.wParam, msg.lParam);

      }
      else
      {

         ::user::interaction * pui = msg.hwnd->get_user_interaction();

         if(pui != NULL)
         {

            pui->post_message(msg.message, msg.wParam, msg.lParam);

         }

      }

   }
   catch(...)
   {

   }

}
