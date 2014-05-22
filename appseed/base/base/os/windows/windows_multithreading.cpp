#include "framework.h"
#include "framework.h"
#include <process.h>    // for _beginthreadex and _endthreadex
#undef new
#include <gdiplus.h>



thread_data::thread_data()
{

   g_dwTlsIndex = TlsAlloc();

}


thread_data::~thread_data()
{

   TlsFree(g_dwTlsIndex);

}


void * thread_data::get()
{
   
   return TlsGetValue(g_dwTlsIndex);

}
   

void thread_data::set(void * p)
{

   TlsSetValue(g_dwTlsIndex, (LPVOID) p);

}






mutex * os_thread::s_pmutex = NULL;
comparable_raw_array < os_thread * >::type * os_thread::s_pptra = NULL;
__declspec(thread) os_thread * t_posthread = NULL;

os_thread::os_thread(uint32_t(* pfn)(void *),void * pv)
{

   m_pfn    = pfn;
   m_pv     = pv;
   m_bRun   = true;
   m_hthread = NULL;



   synch_lock ml(&*s_pmutex);

   s_pptra->add(this);

}


os_thread::~os_thread()
{

   synch_lock ml(&*s_pmutex);

   for(index i = s_pptra->get_count() - 1; i >= 0; i--)
   {

      if(s_pptra->element_at(i) == this)
      {

         s_pptra->remove_at(i);

      }

   }


   if(m_hthread != NULL)
   {

      ::CloseHandle(m_hthread);

   }



}


os_thread * os_thread::get()
{

   return t_posthread;

}

void os_thread::set(os_thread * posthread)
{

   t_posthread = posthread;

}

bool os_thread::get_run()
{

   return get()->m_bRun;

}

void os_thread::stop_all(uint32_t millisMaxWait)
{

   millisMaxWait = millisMaxWait;

   uint32_t start = get_tick_count();

   while(get_tick_count() - start < millisMaxWait)
   {

      {

         synch_lock ml(&*s_pmutex);

         for(int i = 0; i < s_pptra->get_count(); i++)
         {

            s_pptra->element_at(i)->m_bRun = false;

         }

         if(s_pptra->get_count() <= 0)
         {

            break;

         }

      }

      Sleep(184);

   }


}

unsigned int WINAPI os_thread::thread_proc(void * lpparameter)
{

   os_thread * posthread = (os_thread *)lpparameter;

   t_posthread = posthread;

   uint32_t uiRet = posthread->run();

   t_posthread = NULL;

   posthread->release();

   // allow C-runtime to cleanup, and exit the thread
   try
   {
      _endthreadex(uiRet);
   }
   catch(...)
   {
   }

   return uiRet;

}


uint32_t os_thread::run()
{

   
   on_init_thread();


   Gdiplus::GdiplusStartupInput     * pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   Gdiplus::GdiplusStartupOutput    * pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   DWORD_PTR gdiplusToken                                      = NULL;
   DWORD_PTR gdiplusHookToken                                  = NULL;

   Gdiplus::Status statusStartup = GdiplusStartup(&gdiplusToken,pgdiplusStartupInput,pgdiplusStartupOutput);

   if(statusStartup != Gdiplus::Ok)
   {

      return -1;

   }

   attach_thread_input_to_main_thread();

   uint32_t dwRet = 0xffffffff;

   try
   {

      dwRet = m_pfn(m_pv);

   }
   catch(...)
   {
   }

   Gdiplus::GdiplusShutdown(gdiplusToken);

   
   on_term_thread();


   return dwRet;

}


HANDLE start_thread(uint32_t(* pfn)(void *),void * pv,int32_t iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL,0,pfn,pv,0,NULL);

}

HANDLE create_thread(LPSECURITY_ATTRIBUTES lpsa,uint_ptr cbStack,uint32_t(* pfn)(void *),void * pv,uint32_t f,uint32_t * lpui)
{

   sp(os_thread) posthread = canew(os_thread(pfn,pv));

   posthread->add_ref();

   static int s_i = 0;

   s_i++;

   posthread->m_strDebug.Format("index = %d",s_i);

   posthread->m_hthread = (HTHREAD)_beginthreadex(lpsa,(unsigned int)cbStack,&::os_thread::thread_proc,(void *)posthread,f | CREATE_SUSPENDED,lpui);

   if(!(f & CREATE_SUSPENDED))
   {

      ::ResumeThread(posthread->m_hthread);

   }

   return posthread->m_hthread;

}



thread_layer::~thread_layer()
{


}


int32_t thread_layer::run()
{

   MSG msg;

   while(true)
   {

      if(!PeekMessage(&msg,NULL,0,0xffffffffu,TRUE))
      {

         if(!on_idle())
         {

            Sleep(m_iSleepiness);

         }


         continue;

      }

      if(msg.message == WM_QUIT)
         break;

      TranslateMessage(&msg);
      DispatchMessage(&msg);

   }

   return m_iResult;

}

bool thread_layer::on_idle()
{

   return false;

}

void thread_layer::wait_thread(uint32_t dwMillis)
{

   ::WaitForSingleObject(m_hthread,dwMillis);

}

static HANDLE g_hMainThread = NULL;
static UINT g_uiMainThread = -1;

void set_main_thread(HANDLE hThread)
{

   MSG msg;

   PeekMessage(&msg,NULL,0,0xffffffff,FALSE);

   g_hMainThread = hThread;

}

void set_main_thread_id(UINT uiThread)
{

   MSG msg;

   PeekMessage(&msg,NULL,0,0xffffffff,FALSE);

   g_uiMainThread = uiThread;

}


HANDLE get_main_thread()
{
   return g_hMainThread;

}
UINT   get_main_thread_id()
{
   return g_uiMainThread;
}


void attach_thread_input_to_main_thread(bool bAttach)
{

   MSG msg;

   PeekMessage(&msg,NULL,0,0xffffffff,FALSE);

   AttachThreadInput(::GetCurrentThreadId(),get_main_thread_id(),bAttach ? TRUE : FALSE);

}


uint32_t thread_layer::proc(void * lp)
{

   thread_layer * player   = (thread_layer *)lp;

   return player->run();

}


namespace core
{

   ///  \brief		global function to set thread priority for current thread
   ///  \param		new priority
   bool set_thread_priority(int32_t priority)
   {

      return (::SetThreadPriority(::GetCurrentThread(),get_os_thread_priority(priority)) != 0);
   }

   bool set_priority_class(int32_t priority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(),get_os_priority_class(priority)) != 0);
   }

   ///  \brief		global function to get thread priority for current thread
   ///  \return	priority of current thread

   int32_t thread_priority()
   {
      return ::GetThreadPriority(::GetCurrentThread());
   }


} // namespace core




HTHREAD get_current_thread()
{
   return ::GetCurrentThread();
}


DWORD get_current_thread_id()
{
   return ::GetCurrentThreadId();
}






int32_t get_os_thread_priority(int32_t iCa2Priority)
{

   if(iCa2Priority <= (int) ::core::scheduling_priority_none)
      return THREAD_PRIORITY_NORMAL;

   if(iCa2Priority <= (int) ::core::scheduling_priority_idle)
      return THREAD_PRIORITY_IDLE;

   if(iCa2Priority <= (int) ::core::scheduling_priority_lowest)
      return THREAD_PRIORITY_LOWEST;

   if(iCa2Priority <= (int) ::core::scheduling_priority_below_normal)
      return THREAD_PRIORITY_BELOW_NORMAL;

   if(iCa2Priority <= (int) ::core::scheduling_priority_normal)
      return THREAD_PRIORITY_NORMAL;

   if(iCa2Priority <= (int) ::core::scheduling_priority_above_normal)
      return THREAD_PRIORITY_ABOVE_NORMAL;

   if(iCa2Priority <= (int) ::core::scheduling_priority_highest)
      return THREAD_PRIORITY_HIGHEST;

   return THREAD_PRIORITY_TIME_CRITICAL;

}



int32_t get_os_priority_class(int32_t iCa2Priority)
{

   if(iCa2Priority <= (int) ::core::scheduling_priority_none)
      return 0;

   if(iCa2Priority <= (int) ::core::scheduling_priority_idle)
      return IDLE_PRIORITY_CLASS;

   if(iCa2Priority <= (int) ::core::scheduling_priority_lowest)
      return BELOW_NORMAL_PRIORITY_CLASS;

   if(iCa2Priority <= (int) ::core::scheduling_priority_below_normal)
      return BELOW_NORMAL_PRIORITY_CLASS;

   if(iCa2Priority <= (int) ::core::scheduling_priority_normal)
      return NORMAL_PRIORITY_CLASS;

   if(iCa2Priority <= (int) ::core::scheduling_priority_above_normal)
      return ABOVE_NORMAL_PRIORITY_CLASS;

   if(iCa2Priority <= (int) ::core::scheduling_priority_highest)
      return HIGH_PRIORITY_CLASS;

   return REALTIME_PRIORITY_CLASS;

}







int32_t get_os_thread_scheduling_priority(int32_t nPriority)
{

   int32_t iCa2Priority;

   if(nPriority <= THREAD_PRIORITY_IDLE)
   {
      iCa2Priority = ::core::scheduling_priority_idle;
   }
   else if(nPriority <= THREAD_PRIORITY_LOWEST)
   {
      iCa2Priority = ::core::scheduling_priority_lowest;
   }
   else if(nPriority <= THREAD_PRIORITY_BELOW_NORMAL)
   {
      iCa2Priority = ::core::scheduling_priority_below_normal;
   }
   else if(nPriority <= THREAD_PRIORITY_NORMAL)
   {
      iCa2Priority = ::core::scheduling_priority_normal;
   }
   else if(nPriority <= THREAD_PRIORITY_ABOVE_NORMAL)
   {
      iCa2Priority = ::core::scheduling_priority_above_normal;
   }
   else if(nPriority <= THREAD_PRIORITY_HIGHEST)
   {
      iCa2Priority = ::core::scheduling_priority_highest;
   }
   else
   {
      iCa2Priority = ::core::scheduling_priority_time_critical;
   }

   return iCa2Priority;

}


int32_t get_os_class_scheduling_priority(int32_t nPriority)
{

   int32_t iCa2Priority;

   if(nPriority <= IDLE_PRIORITY_CLASS)
   {
      iCa2Priority = ::core::scheduling_priority_idle;
   }
   else if(nPriority <= BELOW_NORMAL_PRIORITY_CLASS)
   {
      iCa2Priority = ::core::scheduling_priority_below_normal;
   }
   else if(nPriority <= NORMAL_PRIORITY_CLASS)
   {
      iCa2Priority = ::core::scheduling_priority_normal;
   }
   else if(nPriority <= ABOVE_NORMAL_PRIORITY_CLASS)
   {
      iCa2Priority = ::core::scheduling_priority_above_normal;
   }
   else if(nPriority <= HIGH_PRIORITY_CLASS)
   {
      iCa2Priority = ::core::scheduling_priority_highest;
   }
   else
   {
      iCa2Priority = ::core::scheduling_priority_time_critical;
   }

   return iCa2Priority;

}



void on_init_thread()
{

   __inc_threading_count();

}


void on_term_thread()
{

   __dec_threading_count();

}





void __node_init_multithreading()
{

}



void __node_term_multithreading()
{

}






