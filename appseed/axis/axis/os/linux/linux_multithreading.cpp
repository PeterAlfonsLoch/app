#include "framework.h"


bool axis_defer_process_x_message(HTHREAD hthread, LPMESSAGE lpMsg, oswindow window, bool bPeek)
{

   if(hthread == NULL)
      return false;

   //single_lock sl(&user_mutex(), true);

   bool bRet = false;

   bool bContinue = true;

   single_lock slOsDisplay(::osdisplay_data::s_pmutex, false);

   while(bContinue && !bRet)
   {

      bContinue = false;

      slOsDisplay.lock();

      for(int i = 0; i < ::osdisplay_data::s_pdataptra->get_count() && !bRet; i++)
      {

         //::oswindow_data * pdata = ::oswindow_data::s_pdataptra->element_at(i);

         ::osdisplay_data * pdata = ::osdisplay_data::s_pdataptra->element_at(i);

         //if(pdata == NULL || pdata->m_bMessageOnlyWindow)
         //   continue;

         // if(pdata->m_hthread != hthread)
            // continue;

         Display * display = pdata->display();

         slOsDisplay.unlock();

         if(display == NULL)
         {

            slOsDisplay.lock();

            continue;

         }


         xdisplay d(display);

         XEvent e;

         if(XPending(display))
         {

            bContinue = false;

            XNextEvent(display, &e);

            if(e.type == Expose)
            {

               lpMsg->message       = WM_PAINT;
               lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
               lpMsg->lParam        = 0;
               lpMsg->wParam        = 0;

               bRet                 = true;

            }
            else if(e.type == ConfigureNotify)
            {

               if(e.xconfigure.window == g_oswindowDesktop->window())
               {

                  for(int j = 0; j < ::oswindow_data::s_pdataptra->get_count(); j++)
                  {

                     PostMessage(::oswindow_data::s_pdataptra->element_at(j), WM_DISPLAYCHANGE, 0, 0);

                  }

                  d.unlock();

                  slOsDisplay.lock();

                  continue;

               }
                              //               XClearWindow(w.display(), w.window());
            }
            else if(e.type == ButtonPress || e.type == ButtonRelease)
            {

               bRet                 = true;

               if(e.xbutton.type == ButtonPress)
               {
                  if(e.xbutton.button == Button1)
                  {
                     lpMsg->message = WM_LBUTTONDOWN;
                  }
                  else if(e.xbutton.button == Button2)
                  {
                     lpMsg->message = WM_MBUTTONDOWN;
                  }
                  else if(e.xbutton.button == Button3)
                  {
                     lpMsg->message = WM_RBUTTONDOWN;
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
                     lpMsg->message = WM_LBUTTONUP;
                  }
                  else if(e.xbutton.button == Button2)
                  {
                     lpMsg->message = WM_MBUTTONUP;
                  }
                  else if(e.xbutton.button == Button3)
                  {
                     lpMsg->message = WM_RBUTTONUP;
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

                  lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                  lpMsg->wParam        = 0;
                  lpMsg->lParam        = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);

               }

            }
            else if(e.type == KeyPress || e.type == KeyRelease)
            {

               oswindow w = oswindow_get(display, e.xexpose.window);

               bRet                 = true;

               if(e.xkey.type == KeyPress)
               {

                  lpMsg->message = WM_KEYDOWN;

               }
               else if(e.xkey.type == KeyRelease)
               {

                  lpMsg->message = WM_KEYUP;

               }
               else
               {

                  bRet = false;

               }

               lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
               lpMsg->wParam        = e.xkey.keycode;
               lpMsg->lParam        = MAKELONG(0, e.xkey.keycode);



            }
            else if(e.type == MotionNotify)
            {

               lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
               lpMsg->message       = WM_MOUSEMOVE;
               lpMsg->wParam        = 0;
               lpMsg->lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);

               bRet                 = true;

            }
            else if(e.type == DestroyNotify)
            {

               lpMsg->hwnd          = oswindow_get(display, e.xdestroywindow.window);
               lpMsg->message       = WM_DESTROY;

               bRet                 = true;

            }

            if(bPeek && bRet)
               XPutBackEvent(display, &e);



         }

         if(bRet && lpMsg->hwnd->window() != None)
         {

            if(lpMsg->hwnd->m_hthread != hthread)
            {

               //bRet = false;

               //bContinue = true;

               //PostMessage(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);

            }

         }

         slOsDisplay.lock();

      }

      slOsDisplay.unlock();

   }

   return bRet;

}









