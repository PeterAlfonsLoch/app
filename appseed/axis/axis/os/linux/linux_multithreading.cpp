#include "framework.h"


#ifdef LINUX
# define SCHED_BATCH		3
# define SCHED_IDLE		5

# define SCHED_RESET_ON_FORK	0x40000000
#endif



void get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   if(nCa2Priority == ::axis::scheduling_priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::axis::scheduling_priority_normal;

      iCa2Max = (int) ::axis::scheduling_priority_normal;

   }
   else if(nCa2Priority > ::axis::scheduling_priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::axis::scheduling_priority_normal;

      iCa2Max = 99;

   }
   else
   {

      iOsPolicy = SCHED_IDLE;

      iCa2Min = 0;

      iCa2Max = (int) ::axis::scheduling_priority_normal;

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

      iCa2Min = (int) ::axis::scheduling_priority_normal;

      iCa2Max = 99;

   }
   else if(iOsPolicy == SCHED_IDLE)
   {

      iCa2Min = 0;

      iCa2Max = (int) ::axis::scheduling_priority_normal;

   }
   else
   {

      iCa2Min = (int) ::axis::scheduling_priority_normal;

      iCa2Max = (int) ::axis::scheduling_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if(iOsMax == iOsMin)
   {
      iCa2Priority = (int32_t) ::axis::scheduling_priority_normal;
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

   CLASS_DECL_AXIS bool set_priority_class(int32_t priority)
	{

      int32_t iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, priority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

	}




} // namespace core





bool defer_process_x_message(HTHREAD hthread, LPMESSAGE lpMsg, oswindow window, bool bPeek)
{

   if(hthread == NULL)
      return false;

   single_lock sl(&user_mutex(), true);

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

         if(pdata->m_hthread != hthread)
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

}

















































void __node_init_thread()
{

}

void __node_term_thread()
{

}














//thread_int_ptr < HRESULT > t_hresultCoInitialize;


bool __os_init_thread()
{

//   t_hresultCoInitialize = ::CoInitializeEx(NULL,COINIT_MULTITHREADED);
//
//   if(FAILED(t_hresultCoInitialize))
//   {
//
//      if(t_hresultCoInitialize.operator HRESULT() == RPC_E_CHANGED_MODE)
//      {
//
//         t_hresultCoInitialize = ::CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);
//
//         if(FAILED(t_hresultCoInitialize))
//         {
//
//            ::simple_message_box(NULL,"Failed to ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED) at __node_pre_init","__node_pre_init failure",MB_ICONEXCLAMATION);
//
//            return false;
//
//         }
//
//      }
//      else
//      {
//
//         ::simple_message_box(NULL,"Failed to ::CoInitializeEx(NULL, COINIT_MULTITHREADED) at __node_pre_init","__node_pre_init failure",MB_ICONEXCLAMATION);
//
//         return false;
//
//      }
//
//   }

   return true;

}



bool __os_term_thread()
{

//   if(SUCCEEDED(t_hresultCoInitialize))
//   {
//
//      CoUninitialize();
//
//   }

   return true;

}
