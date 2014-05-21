#include "framework.h"



bool defer_process_x_message(HTHREAD hthread, LPMESSAGE lpMsg, oswindow window, bool bPeek)
{
#ifndef ANDROID


   if(hthread == NULL || hthread->m_pthread == NULL || hthread->get_x_window_count() <= 0)
      return false;

   synch_lock sl(&user_mutex());

   bool bRet = false;

   bool bContinue = true;

   while(bContinue && !bRet)
   {

      bContinue = false;

      for(int i = 0; i < ::oswindow_data::s_pdataptra->get_count() && !bRet; i++)
      {

         ::oswindow_data * pdata = ::oswindow_data::s_pdataptra->element_at(i);

         if(pdata == NULL || pdata->m_bMessageOnlyWindow)
            continue;

         if(pdata->m_hthread != hthread && g_oswindowDesktop != pdata)
            continue;

         Display * display = pdata->display();

         if(display == NULL)
            continue;


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
                     if(j == i)
                        continue;
                     PostMessage(::oswindow_data::s_pdataptra->element_at(j), WM_DISPLAYCHANGE, 0, 0);
                  }
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

               bRet = false;

               bContinue = true;

               PostMessage(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);

            }

         }

      }

   }

   return bRet;

#endif

   return false;

}




void get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

/*   if(nCa2Priority == ::core::scheduling_priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::core::scheduling_priority_normal;

      iCa2Max = (int) ::core::scheduling_priority_normal;

   }*/
   if(nCa2Priority > ::core::scheduling_priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::core::scheduling_priority_normal;

      iCa2Max = 99;

   }
   else
   {

      //iOsPolicy = SCHED_IDLE;
      iOsPolicy = SCHED_OTHER;

      iCa2Min = 0;

      iCa2Max = (int) ::core::scheduling_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iOsPriority;

   if(iCa2Min == iCa2Max)
   {
      iOsPriority = 0;
   }
   else
   {
      iOsPriority = (((nCa2Priority - iCa2Min)  * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
   }

   iOsPriority = max(iOsMin, min(iOsMax, iOsPriority));

   *piPolicy = iOsPolicy;

   pparam->sched_priority = iOsPriority;

}

int32_t get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


   if(iOsPolicy == SCHED_RR)
   {

      iCa2Min = (int) ::core::scheduling_priority_normal;

      iCa2Max = 99;

   }
/*   else if(iOsPolicy == SCHED_IDLE)
   {

      iCa2Min = 0;

      iCa2Max = (int) ::core::scheduling_priority_normal;

   }*/
   else
   {

      //iCa2Min = (int) ::core::scheduling_priority_normal;
      iCa2Min = (int) 0;

      iCa2Max = (int) ::core::scheduling_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if(iOsMax == iOsMin)
   {
      iCa2Priority = (int32_t) ::core::scheduling_priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = max(iCa2Min, min(iCa2Max, iCa2Priority));

   return iCa2Priority;

}


void thread_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


int32_t thread_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


void process_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


int32_t process_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}






namespace core
{

   CLASS_DECL_BASE bool set_priority_class(int32_t priority)
	{

      int32_t iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, priority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

	}




} // namespace core


__thread struct _TEB * t_pteb = NULL;

struct _TEB * WINAPI NtCurrentTeb(void)
{

   if (t_pteb == NULL)
      t_pteb = new _TEB;

   return t_pteb;

}



