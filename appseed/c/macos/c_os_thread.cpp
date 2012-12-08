#include "framework.h"


/*os_thread::os_thread(DWORD (WINAPI * pfn)(LPVOID), LPVOID pv)
{
   m_pfn = pfn;
   m_pv = pv;
}


void * thread_proc_create_thread(LPVOID lpparameter)
{

   os_thread * posthread = (os_thread *) lpparameter;

/*   Gdiplus::GdiplusStartupInput     * pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   Gdiplus::GdiplusStartupOutput    * pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   ulong_ptr gdiplusToken                                      = NULL;
   ulong_ptr gdiplusHookToken                                  = NULL;

   //pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   // Initialize GDI+.
   Gdiplus::Status statusStartup = GdiplusStartup(&gdiplusToken, pgdiplusStartupInput, pgdiplusStartupOutput);

   if(statusStartup != Gdiplus::Ok)
   {

      delete posthread;

      return -1;

   }*/

   /*statusStartup = pgdiplusStartupOutput->NotificationHook(&gdiplusHookToken);


   if(statusStartup != Gdiplus::Ok)
   {

      Gdiplus::GdiplusShutdown(gdiplusToken);

      delete posthread;

      return -1;

   }*/

/*   DWORD dwRet = 0xffffffff;

   try
   {

      dwRet = posthread->m_pfn(posthread->m_pv);

   }
   catch(...)
   {
   }

   //pgdiplusStartupOutput->NotificationUnhook(gdiplusHookToken);

   //Gdiplus::GdiplusShutdown(gdiplusToken);

   delete posthread;

   return (void *) (dword_ptr) dwRet;

}


HTHREAD start_thread(DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, int iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL, 0, pfn, pv, 0, NULL);

}

HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, DWORD f, LPDWORD lpdwId)
{

   os_thread * pthread = new os_thread(pfn, pv);

   pthread_t thread;

   pthread_attr_t threadAttr;

//   struct sched_param param;  // scheduling priority

   // initialize the thread attribute
   pthread_attr_init(&threadAttr);

   if(cbStack > 0)
   {
      // Set the stack size of the thread
      pthread_attr_setstacksize(&threadAttr, 120*1024);
   }

   // Set thread to detached state. No need for pthread_join
   pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

   // Create the thread
   pthread_create(&thread, &threadAttr, &thread_proc_create_thread, (LPVOID) pthread);


   return (HANDLE) pthread;

}



thread_layer::~thread_layer()
{


}


int thread_layer::run()
{

   MSG msg;

   while(true)
   {

//      if(!PeekMessage(&msg, NULL, 0, 0xffffffffu, TRUE))
      {

         if(!on_idle())
         {

            Sleep(m_iSleepiness);

         }


         continue;

      }

      if(msg.message == WM_QUIT)
         break;

//      TranslateMessage(&msg);
//      DispatchMessage(&msg);

   }

   return m_iResult;

}

bool thread_layer::on_idle()
{

   return false;

}


void thread_layer::wait_thread(DWORD dwMillis)
{
   
   throw "not implemented";

   
}




DWORD WINAPI thread_layer::proc(LPVOID lp)
{
   
   thread_layer * player   = (thread_layer *) lp;
   
 //  player->m_hthread       = ::GetCurrentThread();
   
   //player->m_nId           = ::GetCurrentThreadId();
   
   return player->run();
   
}*/