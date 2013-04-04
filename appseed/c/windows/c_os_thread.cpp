#include "framework.h"
#include <gdiplus.h>



simple_mutex * os_thread::s_pmutex = new simple_mutex();
simple_array < os_thread * > * os_thread::s_pptra = new simple_array < os_thread * > ();
__declspec(thread) os_thread * t_posthread = NULL;

os_thread::os_thread(uint32_t ( * pfn)(void *), void * pv)
{

   m_pfn    = pfn;
   m_pv     = pv;
   m_bRun   = true;


   mutex_lock ml(*s_pmutex);

   s_pptra->add(this);

}


os_thread::~os_thread()
{

   mutex_lock ml(*s_pmutex);

   for(int i = s_pptra->get_count() - 1; i >= 0; i--)
   {

      if(s_pptra->element_at(i) == this)
      {

         s_pptra->remove_at(i);

      }

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

         mutex_lock ml(*s_pmutex);

         for(int i = 0; i < s_pptra->get_count(); i++ )
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

DWORD WINAPI os_thread::thread_proc(LPVOID lpparameter)
{

   os_thread * posthread = (os_thread *) lpparameter;

   t_posthread = posthread;

   uint32_t uiRet = posthread->run();

   t_posthread = NULL;

   delete posthread;

   return uiRet;

}


uint32_t os_thread::run()
{

   Gdiplus::GdiplusStartupInput     * pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   Gdiplus::GdiplusStartupOutput    * pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   DWORD_PTR gdiplusToken                                      = NULL;
   DWORD_PTR gdiplusHookToken                                  = NULL;

   Gdiplus::Status statusStartup = GdiplusStartup(&gdiplusToken, pgdiplusStartupInput, pgdiplusStartupOutput);

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

   return dwRet;

}


HANDLE start_thread(uint32_t (* pfn)(void *), void * pv, int32_t iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL, 0, pfn, pv, 0, NULL);

}

HANDLE create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (* pfn)(void *), void * pv, uint32_t f, uint32_t * lpui)
{

   return ::CreateThread(lpsa, cbStack, &::os_thread::thread_proc, (LPVOID) new os_thread(pfn, pv), f, (LPDWORD) lpui);

}



thread_layer::~thread_layer()
{


}


int32_t thread_layer::run()
{

   MSG msg;

   while(true)
   {

      if(!PeekMessage(&msg, NULL, 0, 0xffffffffu, TRUE))
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

   ::WaitForSingleObject(m_hthread, dwMillis);

}

static HANDLE g_hMainThread = NULL;
static UINT g_uiMainThread = -1;

CLASS_DECL_c void set_main_thread(HANDLE hThread)
{
   
   MSG msg;

   PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_hMainThread = hThread;

}

CLASS_DECL_c void set_main_thread_id(UINT uiThread)
{
   
   MSG msg;

   PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_uiMainThread = uiThread;

}


CLASS_DECL_c HANDLE get_main_thread()
{
   return g_hMainThread;

}
CLASS_DECL_c UINT   get_main_thread_id()
{
   return g_uiMainThread;
}


CLASS_DECL_c void attach_thread_input_to_main_thread(bool bAttach)
{

   MSG msg;

   PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);
   
   AttachThreadInput(::GetCurrentThreadId(), get_main_thread_id(), bAttach ? TRUE : FALSE);

}


uint32_t thread_layer::proc(void * lp)
{

   thread_layer * player   = (thread_layer *) lp;

   return player->run();

}


namespace ca
{

	///  \brief		global function to set thread priority for current thread
	///  \param		new priority
	CLASS_DECL_c bool set_thread_priority(int32_t priority)
	{

      return ( ::SetThreadPriority(::GetCurrentThread(), priority) != 0 );
	}


	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread

	CLASS_DECL_c int32_t thread_priority()
	{
      return ::GetThreadPriority(::GetCurrentThread());
   }


} // namespace ca




