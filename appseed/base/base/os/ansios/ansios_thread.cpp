#include "framework.h"


#if defined(LINUX) // || defined(ANDROID)

bool defer_process_x_message(HTHREAD hthread, LPMESSAGE lpMsg, oswindow oswindow, bool bPeek);

extern bool (* g_defer_process_x_message)(HTHREAD hthread, LPMESSAGE lpMsg, oswindow oswindow, bool bPeek);

#endif



extern "C"
void * os_thread_thread_proc(LPVOID lpparameter);


mq::mq() :
   m_eventNewMessage(get_thread_app())
{

}






map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo > * g_ppendingThreads = NULL;

mutex * g_pmutexPendingThreadsLock = NULL;

mutex * g_pmutexThreadHandleLock = NULL;

mutex * g_pmutexThreadIdHandleLock = NULL;

mutex * g_pmutexThreadIdLock = NULL;

map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo > & pendingThreads()
{

   return * g_ppendingThreads;

}



map < HTHREAD, HTHREAD, HTHREAD, HTHREAD > & thread_handle_map()
{

   static map < HTHREAD, HTHREAD, HTHREAD, HTHREAD > * s_pmap = new map < HTHREAD, HTHREAD, HTHREAD, HTHREAD >();

   return *s_pmap;

}

map < DWORD, DWORD, HTHREAD, HTHREAD > & thread_id_handle_map()
{

   static map < DWORD, DWORD, HTHREAD, HTHREAD > * s_pmap = new map < DWORD, DWORD, HTHREAD, HTHREAD >();

   return *s_pmap;

}


map < HTHREAD, HTHREAD, DWORD, DWORD > & thread_id_map()
{

   static map < HTHREAD , HTHREAD, DWORD, DWORD > * s_pmap = new map < HTHREAD, HTHREAD, DWORD, DWORD >();

   return *s_pmap;

}

DWORD DwThreadId()
{
   static DWORD g_dw_thread_id = 0;

   if(g_dw_thread_id  <= 0)
      g_dw_thread_id = 1;

   return g_dw_thread_id++;
}

// Thread local storage.
typedef raw_array < void * > ThreadLocalData;



thread_pointer < ThreadLocalData > currentThreadData;
thread_int_ptr < DWORD > currentThreadId;
thread_pointer < hthread > currentThread;
thread_pointer < os_thread > t_posthread;


static raw_array<DWORD> freeTlsIndices;
static map < HTHREAD, HTHREAD, ThreadLocalData *, ThreadLocalData * > allthreaddata;
mutex * g_pmutexTlsData = NULL;


static DWORD nextTlsIndex = 0;

mutex * os_thread::s_pmutex = NULL;
comparable_raw_array < os_thread * >::type * os_thread::s_pptra = NULL;


// Converts a Win32 thread priority to WinRT format.
int32_t GetWorkItemPriority(int32_t nPriority)
{
   if (nPriority < 0)
      return nPriority; // WorkItemPriority::Low;
   else if (nPriority > 0)
      return nPriority; // WorkItemPriority::High;
   else
      return nPriority; // WorkItemPriority::Normal;
}


// Helper shared between CreateThread and ResumeThread.
os_thread * StartThread(LPTHREAD_START_ROUTINE pfn, LPVOID pv, HTHREAD hthread, int32_t nPriority, SIZE_T cbStack)
{

   os_thread * pthread = new os_thread(pfn, pv);

   pthread->m_hthread = hthread;

   hthread->m_posthread = pthread;

   pthread_t & thread = pthread->m_pthread;

   pthread_attr_t threadAttr;

   pthread_attr_init(&threadAttr);

   if(cbStack > 0)
   {

      pthread_attr_setstacksize(&threadAttr, 120 * 1024); // Set the stack size of the thread

   }

   int iPolicy;

   sched_param schedparam; // scheduling priority

   thread_get_os_priority(&iPolicy, &schedparam, nPriority);

   pthread_attr_setschedpolicy(&threadAttr, iPolicy);

   pthread_attr_setschedparam(&threadAttr, &schedparam);

   pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join

   pthread_create(&thread, &threadAttr, &os_thread_thread_proc, (LPVOID) pthread); // Create the thread

   return pthread;

}



HTHREAD WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, uint_ptr cbStack, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, uint32_t dwCreationFlags, uint32_t * lpdwThreadId)
{
   // Validate parameters.
//   assert(unusedThreadAttributes == nullptr);
//   assert(unusedStackSize == 0);
   //assert((dwCreationFlags & ~CREATE_SUSPENDED) == 0);
   //assert(unusedThreadId == nullptr);

   // Create a handle that will be signalled when the thread has completed
   HTHREAD threadHandle = new hthread();

   if(threadHandle == NULL)
      return NULL;


   synch_lock mlThreadId(g_pmutexThreadIdLock);

   thread_id_map().set_at(threadHandle, DwThreadId());

   if(lpdwThreadId != NULL)
   {
      *lpdwThreadId = thread_id_map()[threadHandle];
   }



   synch_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);

   thread_id_handle_map().set_at(thread_id_map()[threadHandle], threadHandle);

   mlThreadIdHandle.unlock();

   mlThreadId.unlock();

   // Make a copy of the handle for internal use. This is necessary because
   // the caller is responsible for closing the handle returned by CreateThread,
   // and they may do that before or after the thread has finished running.
   /*HANDLE completionEvent;

   if (!DuplicateHandle(GetCurrentProcess(), threadHandle, GetCurrentProcess(), &completionEvent, 0, false, DUPLICATE_SAME_ACCESS))
   {
      CloseHandle(threadHandle);
      return nullptr;
   }*/

//   synch_lock mlThreadHandle(threadHandleLock);

  // thread_handle_map().set_at(completionEvent, threadHandle);

   //mlThreadHandle.unlock();

   PendingThreadInfo info;

   ZERO(info);

   try
   {
      if (dwCreationFlags & CREATE_SUSPENDED)
      {
            // Store info about a suspended thread.

            info.lpStartAddress     = lpStartAddress;
            info.lpParameter        = lpParameter;
            info.m_hthread    = threadHandle;
            info.suspensionEvent    = new event(get_thread_app(), false, true);
            info.nPriority = 0;

            synch_lock lock(g_pmutexPendingThreadsLock);

            pendingThreads()[threadHandle] = info;

            //::WaitForSingleObjectEx(info.suspensionEvent, INFINITE, FALSE);
      }
      else
      {
            // Start the thread immediately.
            StartThread(lpStartAddress, lpParameter, threadHandle, 0, cbStack);
      }

      return threadHandle;
   }
   catch (...)
   {
      // Clean up if thread creation fails.
      threadHandle->m_pevent->set_event();
      delete threadHandle;

      if(info.suspensionEvent)
      {
         info.suspensionEvent->set_event();
         delete info.suspensionEvent;
      }


      return NULL;
   }
}


DWORD WINAPI ResumeThread(HTHREAD hThread)
{
   synch_lock lock(g_pmutexPendingThreadsLock);

   // Look up the requested thread.
   map < HTHREAD , HTHREAD, PendingThreadInfo,  PendingThreadInfo >::pair * threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {
      // Can only resume threads while they are in CREATE_SUSPENDED state.
      //assert(false);
      return (DWORD)-1;
   }

   // Start the thread.
   try
   {
      PendingThreadInfo& info = threadInfo->m_element2;

      StartThread(info.lpStartAddress, info.lpParameter, info.m_hthread, info.nPriority, info.cbStack);
   }
   catch (...)
   {
      return (DWORD)-1;
   }

   // Remove this thread from the pending list.
   pendingThreads().remove_key(hThread);

   return 0;
}


int_bool WINAPI SetThreadPriority(HTHREAD hThread, int32_t nCa2Priority)
{

   synch_lock lock(g_pmutexPendingThreadsLock);

   // Look up the requested thread.
   map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo >::pair * threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {

      int32_t iPolicy;

      sched_param schedparam;

      thread_get_os_priority(&iPolicy, &schedparam, nCa2Priority);

      pthread_setschedparam(hThread->m_posthread->m_pthread, iPolicy, &schedparam);

      return TRUE;

   }

   // Store the new priority.
   threadInfo->m_element2.nPriority = nCa2Priority;

   return TRUE;
}




DWORD WINAPI TlsAlloc()
{

   synch_lock lock(g_pmutexTlsData);

   // Can we reuse a previously freed TLS slot?
   if (freeTlsIndices.get_count() > 0)
   {
      DWORD result = freeTlsIndices.element_at(freeTlsIndices.get_count() - 1);
      freeTlsIndices.remove_at(freeTlsIndices.get_count() - 1);
      return result;
   }

   // Allocate a new TLS slot.
   return nextTlsIndex++;
}


int_bool WINAPI TlsFree(DWORD dwTlsIndex)
{

   synch_lock lock(g_pmutexTlsData);

   //assert(dwTlsIndex < nextTlsIndex);
/*   for(int32_t i = 0; i < freeTlsIndices.get_count(); i++)
   {
      assert(freeTlsIndices.element_at(i) != dwTlsIndex);
   }*/

   // Store this slot for reuse by TlsAlloc.
   try
   {
      freeTlsIndices.add(dwTlsIndex);
   }
   catch (...)
   {
      return false;
   }

   // Zero the value for all threads that might be using this now freed slot.

   POSITION pos = allthreaddata.get_start_position();
   while( pos != NULL)
   {

      HTHREAD hThread;

      ThreadLocalData * pdata;

      allthreaddata.get_next_assoc(pos, hThread, pdata);

      if(pdata->get_count() > dwTlsIndex)
      {
         pdata->element_at(dwTlsIndex) = NULL;
      }
   }

   return true;
}


LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex)
{
   ThreadLocalData* threadData = currentThreadData;

   if (threadData && threadData->get_count() > dwTlsIndex)
   {
      // Return the value of an allocated TLS slot.
      return threadData->element_at(dwTlsIndex);
   }
   else
   {
       threadData = allthreaddata[currentThread] ;
       if(threadData)
       {
           currentThreadData = threadData;
            if(threadData->get_count() > dwTlsIndex)
            {
                return threadData->element_at(dwTlsIndex);
            }
       }
      // Default value for unallocated slots.
      return NULL;
   }
}


LPVOID WINAPI TlsGetValue(HTHREAD hthread, DWORD dwTlsIndex)
{

   try
   {
      
      synch_lock lock(g_pmutexTlsData);
   
      if(allthreaddata.is_empty())
         return NULL;

      ThreadLocalData * threadData = allthreaddata[hthread];

      if (threadData && threadData->get_count() > dwTlsIndex)
      {
         
         // Return the value of an allocated TLS slot.
         return threadData->element_at(dwTlsIndex);
   
      }
      else
      {
      
         // Default value for unallocated slots.
         return NULL;
         
      }
      
   }
   catch (...)
   {
      
      return NULL;
      
   }
   
}


int_bool WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue)
{

   ThreadLocalData* threadData = currentThreadData;

   if (!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
            threadData = new ThreadLocalData;

            synch_lock lock(g_pmutexTlsData);

            allthreaddata.set_at(currentThread, threadData);

            currentThreadData = threadData;

      }
      catch (...)
      {
            if (threadData)
               delete threadData;

            return false;
      }
   }

   // Store the new value for this slot.
   threadData->set_at_grow(dwTlsIndex, lpTlsValue);

   return true;
}

int_bool WINAPI TlsSetValue(HTHREAD hthread, DWORD dwTlsIndex, LPVOID lpTlsValue)
{

    synch_lock lock(g_pmutexTlsData);

   ThreadLocalData * threadData = allthreaddata[hthread];

   if (!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
            threadData = new ThreadLocalData;

            allthreaddata.set_at(hthread, threadData);

      }
      catch (...)
      {
            if (threadData)
               delete threadData;

            return false;
      }
   }

   // Store the new value for this slot.
   threadData->set_at_grow(dwTlsIndex, lpTlsValue);

   return true;
}

// Called at thread exit to clean up TLS allocations.
void WINAPI TlsShutdown()
{

   ThreadLocalData * threadData = currentThreadData;

   if (threadData)
   {

/*      try
      {

         IDWriteFactory * pfactory = TlsGetWriteFactory();

         if(pfactory != NULL)
         {

            pfactory->Release();

         }

      }
      catch(...)
      {
      }

      try
      {

         ID2D1Factory1 * pfactory = GetD2D1Factory1();

         if(pfactory != NULL)
         {

            //pfactory->Release();

         }

      }
      catch(...)
      {
      }

*/

      synch_lock ml(g_pmutexTlsData);

      allthreaddata.remove_key(currentThread);

      currentThreadData = NULL;

      delete threadData;
   }
}




int32_t WINAPI GetThreadPriority(HTHREAD  hthread)
{

   synch_lock lock(g_pmutexPendingThreadsLock);

   // Look up the requested thread.
   map < HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo >::pair * threadInfo = pendingThreads().PLookup(hthread);

   if (threadInfo == NULL)
   {

      int iOsPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      pthread_getschedparam(hthread->m_posthread->m_pthread, &iOsPolicy, &schedparam);

      return thread_get_scheduling_priority(iOsPolicy, &schedparam);

   }

   return threadInfo->m_element2.nPriority;

}





os_thread::os_thread(uint32_t (* pfn)(void *), void * pv)
{

   m_pfn    = pfn;
   m_pv     = pv;
   m_bRun   = true;


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

extern "C"
void * os_thread_thread_proc(LPVOID lpparameter)
{

   os_thread * posthread = (os_thread *) lpparameter;

   t_posthread = posthread;
   
   on_init_thread();

   void * pvRet = (void *) (int_ptr) posthread->run();

   t_posthread = NULL;
   
   on_term_thread();

   delete posthread;

   return pvRet;

}

uint32_t os_thread::run()
{

   on_init_thread();

   synch_lock mlThreadHandle(g_pmutexThreadHandleLock);

   currentThread =  m_hthread;

   mlThreadHandle.unlock();

   synch_lock mlThreadId(g_pmutexThreadIdLock);

   currentThreadId =  thread_id_map()[currentThread];

   mlThreadId.unlock();

   mlThreadHandle.unlock();

   // Run the user callback.
   //attach_thread_input_to_main_thread();

   DWORD dwRet = 0xffffffff;

   try
   {

      dwRet = m_pfn(m_pv);

   }
   catch (...)
   {

   }

   // Clean up any TLS allocations made by this thread.
   TlsShutdown();

   // Signal that the thread has completed.
   currentThread->m_pevent->set_event();

   currentThread->release();

   on_term_thread();

   return dwRet;

}


HTHREAD start_thread(DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, int32_t iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL, 0, pfn, pv, 0, NULL);

}

HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, LPTHREAD_START_ROUTINE pfn, LPVOID pv, uint32_t f, uint32_t * lpdwId)
{

   return ::CreateThread(lpsa, cbStack, pfn, pv, f, lpdwId);

}







static HANDLE g_hMainThread = NULL;
static UINT g_uiMainThread = -1;

CLASS_DECL_BASE void set_main_thread(HANDLE hThread)
{

//   MESSAGE msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_hMainThread = hThread;

}

CLASS_DECL_BASE void set_main_thread_id(UINT uiThread)
{

//   MESSAGE msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_uiMainThread = uiThread;

}


CLASS_DECL_BASE HANDLE get_main_thread()
{
   return g_hMainThread;

}
CLASS_DECL_BASE UINT   get_main_thread_id()
{
   return g_uiMainThread;
}


CLASS_DECL_BASE void attach_thread_input_to_main_thread(bool bAttach)
{
   return;
//   MESSAGE msg;

   // metrowin todo
   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

//   AttachThreadInput(::GetCurrentThreadId(), get_main_thread_id(), bAttach ? TRUE : FALSE); // AttachThreadInput function used to attach thread input to main thread in Windows Desktop

}

DWORD WINAPI thread_layer::proc(LPVOID lp)
{

   thread_layer * player   = (thread_layer *) lp;

   return player->run();

}

mq * get_mq(HTHREAD  h);


mq * get_mq()
{

   return get_mq(GetCurrentThread());

}

bool is_thread(HTHREAD h)
{
   return GetThreadId(h) != 0;
}

mq * get_mq(HTHREAD  h)
{


   mq * pmq = (mq *) TlsGetValue(h, TLS_MESSAGE_QUEUE);

   if(pmq != NULL)
      return pmq;

   pmq               = new mq();

   pmq->m_hthread    = h;

   pmq->m_uiId       = ::GetThreadId(h);

   TlsSetValue(h, TLS_MESSAGE_QUEUE, pmq);

   return pmq;

}




CLASS_DECL_BASE int_bool WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{


   bool bFirst = true;

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

   single_lock ml(&pmq->m_mutex, false);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT) -1;

#if defined(LINUX) || defined(ANDROID)
   HTHREAD hthread = ::GetCurrentThread();
   DWORD idThre = ::GetCurrentThreadId();
#endif

restart:

   ml.lock();

   for(int32_t i = 0; i < pmq->ma.get_count(); i++)
   {
      MESSAGE & msg = pmq->ma[i];


      if(msg.message == WM_QUIT)
      {
         *lpMsg = msg;
         pmq->ma.remove_at(i);
         return FALSE;
      }


      if((oswindow == NULL || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {
         *lpMsg = msg;
         pmq->ma.remove_at(i);
         return TRUE;
      }
   }

   ml.unlock();

#if defined(LINUX) // || defined(ANDROID)
   if(hthread != NULL && hthread->m_pthread != NULL)
   {

      if(!hthread->m_pthread->get_run())
         return FALSE;

      hthread->m_pthread->step_timer();

      if(!hthread->m_pthread->get_run())
         return FALSE;

      if(g_defer_process_x_message != NULL && hthread->m_pthread->get_x_window_count() > 0)
      {

         if((*g_defer_process_x_message)(hthread, lpMsg, oswindow, false))
            return TRUE;

         if(!hthread->m_pthread->get_run())
            return FALSE;
      }

   }
#endif

   if(bFirst)
   {

      pmq->m_eventNewMessage.wait(millis(11));

      pmq->m_eventNewMessage.ResetEvent();

      bFirst = false;

      goto restart;

   }
   else
   {

      lpMsg->message = 0xffffffff;
      lpMsg->hwnd    = NULL;
      lpMsg->wParam  = 0;
      lpMsg->lParam  = 0;
      lpMsg->pt.x    = 0x80000000;
      lpMsg->pt.y    = 0x80000000;

      return TRUE;

   }






}


CLASS_DECL_BASE int_bool WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

#if defined(LINUX) || defined(ANDROID)
   HTHREAD hthread = ::GetCurrentThread();
   DWORD idThre = ::GetCurrentThreadId();
#endif

   synch_lock ml(&pmq->m_mutex);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT) -1;

   for(int32_t i = 0; i < pmq->ma.get_count(); i++)
   {
      MESSAGE & msg = pmq->ma[i];

      if((oswindow == NULL || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {
         *lpMsg = msg;
         if(wRemoveMsg & PM_REMOVE)
         {
            pmq->ma.remove_at(i);
         }
         return TRUE;
      }
   }

   ml.unlock();

#if defined(LINUX) // || defined(ANDROID)
   if(g_defer_process_x_message != NULL && hthread != NULL && hthread->m_pthread != NULL && hthread->m_pthread->get_x_window_count() > 0)
   {

      if((*g_defer_process_x_message)(hthread, lpMsg, oswindow, !(wRemoveMsg & PM_REMOVE)))
         return TRUE;
   }
#endif

   return FALSE;

}



CLASS_DECL_BASE DWORD WINAPI GetThreadId(HTHREAD Thread)
{

   synch_lock mlThreadId(g_pmutexThreadIdLock);

   map < HTHREAD, HTHREAD, DWORD, DWORD >::pair * p = thread_id_map().PLookup(Thread);

   if(p == NULL)
      return -1;


   return p->m_element2;

}

CLASS_DECL_BASE HTHREAD  WINAPI get_thread_handle(DWORD dw)
{

   synch_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);

   map < DWORD, DWORD, HTHREAD, HTHREAD >::pair * p = thread_id_handle_map().PLookup(dw);

   if(p == NULL)
      return NULL;


   return p->m_element2;

}


CLASS_DECL_BASE int_bool WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   HTHREAD h = ::get_thread_handle(idThread);

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.message = Msg;
   msg.wParam  = wParam;
   msg.lParam  = lParam;
   msg.pt.x    = 0x80000000;
   msg.pt.y    = 0x80000000;
   msg.hwnd    = NULL;

   pmq->ma.add(msg);

//   void * p = pmq->ma[pmq->ma.get_count() -1].hwnd;

   pmq->m_eventNewMessage.set_event();

   return true;

}

CLASS_DECL_BASE int_bool WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   HTHREAD  h = oswindow->get_user_interaction()->m_pthread->get_os_handle();

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.hwnd       = oswindow;
   msg.message    = Msg;
   msg.wParam     = wParam;
   msg.lParam     = lParam;
   msg.pt.x       = 0x80000000;
   msg.pt.y       = 0x80000000;


   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}







void thread_layer::wait_thread(DWORD dwMillis)
{

   try
   {

      m_hthread->m_pevent->wait(millis(dwMillis));

   }
   catch(...)
   {

   }

}





thread_layer::~thread_layer()
{

   delete m_hthread;

}


int32_t thread_layer::run()
{

   MESSAGE msg;
   
   ZERO(msg);

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



CLASS_DECL_BASE HTHREAD GetCurrentThread()
{

   return currentThread;

}

CLASS_DECL_BASE UINT GetCurrentThreadId()
{

   return currentThreadId;

}


namespace core
{

	///  \brief		global function to set thread priority for current thread
	///  \param		new priority
	CLASS_DECL_BASE bool set_thread_priority(int32_t priority)
	{

      return ( ::SetThreadPriority(::GetCurrentThread(), priority) != 0 );
	}


	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread

	CLASS_DECL_BASE int32_t thread_priority()
	{
      return ::GetThreadPriority(::GetCurrentThread());
   }


} // namespace core







void on_init_thread()
{
   
   __node_init_thread();

}


void on_term_thread()
{
   
   __node_term_thread();

}