#include "framework.h"


void process_message(Display * pdisplay);
void send_message(MESSAGE & msg);

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

   XEvent e;

   MESSAGE msg;

   ZERO(msg);

   {

      xdisplay d(display);

      XNextEvent(display, &e);

   }

   bool bRet = false;

   if(e.type == Expose)
   {

      if(e.xexpose.count == 0)
      {

         msg.message       = WM_PAINT;
         msg.hwnd          = oswindow_get(display, e.xexpose.window);
         msg.lParam        = 0;
         msg.wParam        = 0;

         send_message(msg);

      }

   }
   else if(e.type == MapNotify || e.type == UnmapNotify)
   {

      msg.message       = WM_SHOWWINDOW;
      msg.hwnd          = oswindow_get(display, e.xmap.window);
      msg.wParam        = e.type == MapNotify;
      msg.lParam        = 0;

      send_message(msg);

   }
   else if(e.type == ConfigureNotify)
   {

      msg.hwnd = oswindow_get(display, e.xconfigure.window);

      if(msg.hwnd != NULL)
      {

         ::user::interaction * pui = msg.hwnd->m_pui;

         if(pui != NULL)
         {

            ::user::interaction_impl * pimpl = dynamic_cast < ::user::interaction_impl * > (pui->m_pimpl.m_p);

            if(pimpl != NULL)
            {

               bool bMove;

               bool bSize;

               rect64 rectWindow;

               rectWindow.left = e.xconfigure.x;

               rectWindow.top = e.xconfigure.y;

               rectWindow.right = rectWindow.left + e.xconfigure.width;

               rectWindow.bottom = rectWindow.top + e.xconfigure.height;

               if(rectWindow.top_left() == pimpl->m_rectParentClient.top_left())
               {

                  bMove = false;

                  if(rectWindow.size() == pimpl->m_rectParentClient.size())
                  {

                     bSize = false;

                  }
                  else
                  {

                     pimpl->m_rectParentClient.right  = rectWindow.right;

                     pimpl->m_rectParentClient.bottom  = rectWindow.bottom;

                     bSize = true;

                  }

               }
               else
               {

                  bMove = true;

                  if(rectWindow.size() == pimpl->m_rectParentClient.size())
                  {

                     pimpl->m_rectParentClient = rectWindow;;

                     bSize = false;

                  }
                  else
                  {

                     pimpl->m_rectParentClient = rectWindow;;

                     bSize = true;
                  }

               }

               if(bSize || bMove)
               {

                  if(bSize)
                  {

                     //pimpl->m_bUpdateGraphics = true;

                     pui->send_message(WM_SIZE, 0, rectWindow.size().lparam());

                  }

                  if(bMove)
                  {

                     pui->send_message(WM_MOVE, 0, rectWindow.top_left().lparam());

                  }

               }

            }

         }

      }

      if(e.xconfigure.window == g_oswindowDesktop->window())
      {

         for(int j = 0; j < ::oswindow_data::s_pdataptra->get_count(); j++)
         {

            PostMessage(::oswindow_data::s_pdataptra->element_at(j), WM_DISPLAYCHANGE, 0, 0);

         }

      }

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

         send_message(msg);

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

         send_message(msg);

      }
   }
   else if(e.type == MotionNotify)
   {

      msg.hwnd          = oswindow_get(display, e.xbutton.window);
      msg.message       = WM_MOUSEMOVE;
      msg.wParam        = 0;
      msg.lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);

      send_message(msg);

   }
   else if(e.type == DestroyNotify)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_DESTROY;

      send_message(msg);

   }
   else if(e.type == FocusIn)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_SETFOCUS;

      send_message(msg);

   }
   else if(e.type == FocusOut)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_KILLFOCUS;

      send_message(msg);

   }


}








void send_message(MESSAGE & msg)
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
