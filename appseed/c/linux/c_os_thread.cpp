#include "framework.h"

bool defer_process_x_message(HTHREAD hthread, LPMESSAGE lpMsg, oswindow window, bool bPeek)
{
   
   static simple_mutex s_m;
   
   mutex_lock l(s_m, true);
   
   bool bRet = false;
   
   bool bContinue = true;
   
   while(bContinue)
   {
      
      bContinue = false;
      
      for(int i = 0; i < ::oswindow::s_pdataptra->get_count(); i++)
      {
         
         ::oswindow::data * pdata = ::oswindow::s_pdataptra->element_at(i);
         
         if(pdata == NULL)
            continue;
         
         if(pdata->m_hthread != hthread)
            continue;
         
         Display * display = pdata->m_osdisplay.display();
         
         if(display == NULL)
            continue;
         
         XEvent e;
         
         if(XPending(display))
         {
            
            bContinue = false;
            
            XNextEvent(display, &e);
            
            if(bPeek)
               XPutBackEvent(display, &e);
            
            if(e.type == Expose)
            {
               
               lpMsg->message       = WM_PAINT;
               lpMsg->hwnd          = oswindow(display, e.xbutton.window);
               lpMsg->lParam        = 0;
               lpMsg->wParam        = 0;
               
               bRet                 = true;
               
            }
            else if(e.type == ConfigureNotify)
            {
               //               XClearWindow(w.display(), w.window());
            }
            else if(e.type == ButtonPress || e.type == ButtonRelease)
            {
               
               if(e.xbutton.type == ButtonPress)
               {
                  if(e.xbutton.button == Button1)
                  {
                     lpMsg->message = WM_LBUTTONDOWN;
                  }
                  else
                  {
                  }
                  
               }
               else if(e.xbutton.type == ButtonRelease)
               {
                  if(e.xbutton.button == Button1)
                  {
                     lpMsg->message = WM_LBUTTONUP;
                  }
                  else
                  {
                  }
                  
               }
               
               lpMsg->hwnd          = oswindow(display, e.xbutton.window);
               lpMsg->wParam        = 0;
               lpMsg->lParam        = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);
               
               bRet                 = true;
               
            }
            else if(e.type == KeyPress || e.type == KeyRelease)
            {
               
               oswindow w(display, e.xexpose.window);
               
               if(e.xkey.type == KeyPress)
               {
                  
                  lpMsg->message = WM_KEYDOWN;
                  
               }
               else if(e.xkey.type == KeyRelease)
               {
                  
                  lpMsg->message = WM_KEYUP;
                  
               }
               
               lpMsg->hwnd          = oswindow(display, e.xbutton.window);
               lpMsg->wParam        = e.xkey.keycode;
               lpMsg->lParam        = 0;
               
               bRet                 = true;
               
            }
            else if(e.type == MotionNotify)
            {
               
               lpMsg->hwnd          = oswindow(display, e.xbutton.window);
               lpMsg->message       = WM_MOUSEMOVE;
               lpMsg->wParam        = 0;
               lpMsg->lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);
               
               bRet                 = true;
               
            }
            
            
         }
         
         if(bRet && lpMsg->hwnd.window() != None)
         {
            
            if(lpMsg->hwnd.m_pdata->m_hthread != hthread)
            {
               
               bRet = false;
               
               bContinue = true;
               
               PostMessage(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
               
            }
            
         }
         
      }
      
   }
   
   return bRet;
   
}

