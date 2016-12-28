#include "framework.h"


void process_message(osdisplay_data * pdata, Display * pdisplay);
void send_message(MESSAGE & msg);


bool g_bSkipMouseMessageInXcess = true;
DWORD g_dwLastMotion = 0;
DWORD g_dwMotionSkipTimeout = 23;

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

   bool bPending;

   while(::aura::system::g_p != NULL && ::aura::system::g_p->get_run_thread())
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

      bPending = false;

      {

         xdisplay d(display);

         bPending = XPending(display);

      }

      if(bPending)
      {

         process_message(pdata, display);

      }
      else
      {

         Sleep(1);

      }

   }

}

int g_xxx = 0;

void process_message(osdisplay_data * pdata, Display * display)
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
   else if(e.type == PropertyNotify)
   {

      msg.hwnd = oswindow_get(display, e.xproperty.window);



      if(msg.hwnd != NULL && msg.hwnd->m_pimpl != NULL)
      {

         ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

         if(pui != NULL)
         {

            ::user::interaction_impl_base * pimpl = pui->m_pimpl;

            bool bHandled = false;

            if(pimpl != NULL)
            {

               g_xxx++;

               if(g_xxx >= 9)
               {
                  output_debug_string("g_xxx");
               }
               if(pui->m_eappearance == ::user::AppearanceIconic && !msg.hwnd->is_iconic())
               {

                  //file_put_contents_dup("/home/camilo/xxx.txt", "");

                  pui->m_eappearance == ::user::AppearanceNone;

                  ::fork(pui->get_app(), [=]()
                  {

                     if(pui->m_eappearanceBefore == ::user::AppearanceIconic)
                     {

                        pui->_001OnDeiconify(::user::AppearanceNormal);

                     }
                     else
                     {

                        pui->_001OnDeiconify(pui->m_eappearanceBefore);

                     }

                  });

                  bHandled = true;


               }

            }

         }
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

         ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

         if(pui != NULL)
         {

            ::user::interaction_impl_base * pimpl = pui->m_pimpl;

            bool bHandled = false;

            if(pimpl != NULL)
            {

               g_xxx++;

               if(g_xxx >= 9)
               {
                  output_debug_string("g_xxx");
               }
               if(pui->m_eappearance == ::user::AppearanceIconic)
               {

                  //file_put_contents_dup("/home/camilo/xxx.txt", "");

                  pui->m_eappearance == ::user::AppearanceNone;

                  ::fork(pui->get_app(), [=]()
                  {

                     if(pui->m_eappearanceBefore == ::user::AppearanceIconic)
                     {

                        pui->_001OnDeiconify(::user::AppearanceNormal);

                     }
                     else
                     {

                        pui->_001OnDeiconify(pui->m_eappearanceBefore);

                     }

                  });

                  bHandled = true;


               }


               if(!bHandled)
               {

                  //rect64 rectWindow;

                  //rectWindow.left = e.xconfigure.x;

                  //rectWindow.top = e.xconfigure.y;

                  //rectWindow.right = rectWindow.left + e.xconfigure.width;

                  //rectWindow.bottom = rectWindow.top + e.xconfigure.height;

                  ::rect rectWindow;

                  ::GetWindowRect(msg.hwnd, rectWindow);

                  ::copy(pimpl->m_rectParentClientRequest, rectWindow);

                  pui->set_need_layout();

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

      synch_lock sl(pdata->m_pmutexMouse);

      if(pdata->m_messsageaMouse.get_size() > 1000)
      {

         pdata->m_messsageaMouse.remove_at(0, 499);

      }

      pdata->m_messsageaMouse.add(msg);

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

         ::aura::system::g_p->post_message(msg.message, msg.wParam, msg.lParam);

      }
      else
      {

         if(msg.hwnd != NULL && msg.hwnd->m_pimpl != NULL && msg.hwnd->m_pimpl->m_pui != NULL)
         {

            ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

            pui->send_message(msg.message, msg.wParam, msg.lParam);

         }

      }

   }
   catch(...)
   {

   }

}




UINT __axis_x11mouse_thread(void * p)
{

   osdisplay_data * pdata = (osdisplay_data *) p;

   __begin_thread(::aura::system::g_p,&__axis_x11_thread,pdata,::multithreading::priority_normal,0,0,NULL);

   single_lock sl(pdata->m_pmutexMouse);

   MESSAGE msg;

   bool bOk;

   while(::aura::system::g_p != NULL && ::aura::system::g_p->get_run_thread())
   {

      bOk = false;

      {

         sl.lock();

         if(pdata->m_messsageaMouse.has_elements())
         {

            msg = pdata->m_messsageaMouse.last();

            pdata->m_messsageaMouse.remove_all();

            bOk = true;

         }

         sl.unlock();

      }

      if(bOk)
      {

         ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

         if(pui != NULL)
         {

            pui->send_message(msg.message, msg.wParam, msg.lParam);

         }

      }
      else
      {

         Sleep(23);

      }

   }

   return 0;

}



