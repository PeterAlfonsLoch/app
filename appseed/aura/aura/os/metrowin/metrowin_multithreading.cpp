// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#include "framework.h"
#include "metrowin.h"

#undef System

#include <assert.h>
//#include <vector>
//#include <set>
//#include <map>

//using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;

BEGIN_EXTERN_C
mutex * g_pmutexPendingThreadsLock = NULL;
mutex * g_pmutexThreadIdHandleLock = NULL;
mutex * g_pmutexThreadIdLock = NULL;
mutex * g_pmutexTlsData = NULL;
END_EXTERN_C

map<HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo> & pendingThreads()
{

   static map<HTHREAD, HTHREAD, PendingThreadInfo,PendingThreadInfo> * pts = new map<HTHREAD, HTHREAD, PendingThreadInfo, PendingThreadInfo>();

   return *pts;

}
map < DWORD, DWORD, HTHREAD, HTHREAD > & thread_id_handle_map()
{

   static map < DWORD,DWORD, HTHREAD,  HTHREAD > * s_pmap = new map < DWORD, DWORD, HTHREAD, HTHREAD >();

   return *s_pmap;

}


map < HTHREAD,HTHREAD, DWORD, DWORD > & thread_id_map()
{

   static map < HTHREAD, HTHREAD, DWORD, DWORD > * s_pmap = new map < HTHREAD, HTHREAD, DWORD, DWORD >();

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
typedef comparable_array < void *, void *, array < void *, void *, ::constructor::zero < void * > > > ThreadLocalData;



__declspec(thread) ThreadLocalData* currentThreadData = nullptr;
__declspec(thread) DWORD currentThreadId = -1;
__declspec(thread) HTHREAD currentThread = NULL;

map < HTHREAD, HTHREAD, ThreadLocalData* ,  ThreadLocalData * > & all_thread_data()
{

   static map < HTHREAD, HTHREAD, ThreadLocalData* ,  ThreadLocalData * > * s_pallthreaddata = new map < HTHREAD, HTHREAD, ThreadLocalData* , ThreadLocalData * >();

   return *s_pallthreaddata;

}

DWORD nextTlsIndex = 0;
uint_array freeTlsIndices;


// Converts a Win32 thread priority to WinRT format.
WorkItemPriority GetWorkItemPriority(int nPriority)
{
   if (nPriority < 0)
      return WorkItemPriority::Low;
   else if (nPriority > 0)
      return WorkItemPriority::High;
   else
      return WorkItemPriority::Normal;
}


// Helper shared between CreateThread and ResumeThread.
void StartThread(uint32_t (* pfn)(void *), void * pv, HTHREAD hthread, int nPriority)
{

   auto workItemHandler = ref new WorkItemHandler([=](IAsyncAction^)
   {

      currentThread = hthread;

      synch_lock mlThreadId(g_pmutexThreadIdLock);

      currentThreadId =  thread_id_map()[currentThread];

      mlThreadId.unlock();

      // Run the user callback.
      try
      {
         pfn(pv);
      }
      catch (...) { }

      // Clean up any TLS allocations made by this thread.
      TlsShutdown();

      // Signal that the thread has completed.
      hthread->m_pevent->set_event();
      delete hthread;

   }, CallbackContext::Any);

   ThreadPool::RunAsync(workItemHandler, GetWorkItemPriority(nPriority), WorkItemOptions::TimeSliced);
}


HTHREAD WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, uint_ptr unusedStackSize, uint32_t (* pfn)(void *) , void * pv, uint32_t uiCreationFlags, uint32_t * puiId)
{
   // Validate parameters.
   assert(unusedThreadAttributes == nullptr);
   assert(unusedStackSize == 0);
   assert((uiCreationFlags & ~CREATE_SUSPENDED) == 0);
   //assert(unusedThreadId == nullptr);

   // Create a handle that will be signalled when the thread has completed.
   HTHREAD threadHandle = new hthread;

   //threadHandle->mCreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

   if (!threadHandle)
      return nullptr;

   synch_lock mlThreadId(g_pmutexThreadIdLock);

   thread_id_map().set_at(threadHandle, DwThreadId());

   if(puiId != NULL)
   {
      *puiId = thread_id_map()[threadHandle];
   }

   synch_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);

   thread_id_handle_map().set_at(thread_id_map()[threadHandle], threadHandle);

   mlThreadIdHandle.unlock();

   mlThreadId.unlock();

   // Make a copy of the handle for internal use. This is necessary because
   // the caller is responsible for closing the handle returned by CreateThread,
   // and they may do that before or after the thread has finished running.
   //HANDLE completionEvent;

   //if (!DuplicateHandle(GetCurrentProcess(), threadHandle->m_pevent->m_hEvent, GetCurrentProcess(), &completionEvent, 0, false, DUPLICATE_SAME_ACCESS))
   //{
     // CloseHandle(threadHandle);
      //return nullptr;
   //}

   try
   {

      if (uiCreationFlags & CREATE_SUSPENDED)
      {

         // Store info about a suspended thread.
         PendingThreadInfo info;

         info.m_pfn                 = pfn;
         info.m_pv                  = pv;
         info.m_hthread             = threadHandle;
         info.m_peventCompletion    = threadHandle->m_pevent;
         info.m_peventSuspension    = new manual_reset_event(get_thread_app());
         info.m_iPriority           = 0;

         synch_lock lock(g_pmutexPendingThreadsLock);

         pendingThreads()[threadHandle] = info;

         //::WaitForSingleObjectEx(info.suspensionEvent, INFINITE, FALSE);
      }
      else
      {
         // Start the thread immediately.
         StartThread(pfn, pv, threadHandle, 0);
      }
      if(puiId != NULL)
      {
         *puiId =thread_id_map()[threadHandle];
      }

      return threadHandle;
   }
   catch (...)
   {
      // Clean up if thread creation fails.
      delete threadHandle;

      return nullptr;
   }
}


DWORD WINAPI ResumeThread(HTHREAD hThread)
{
   synch_lock lock(g_pmutexPendingThreadsLock);

   // Look up the requested thread.
   auto threadInfo = pendingThreads().PLookup(hThread);

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

      StartThread(info.m_pfn, info.m_pv, info.m_hthread, info.m_iPriority);

   }
   catch (...)
   {
      return (DWORD)-1;
   }

   // Remove this thread from the pending list.
   pendingThreads().remove_key(hThread);

   return 0;
}


BOOL WINAPI SetThreadPriority(HTHREAD hThread, int iPriority)
{
   synch_lock lock(g_pmutexPendingThreadsLock);

   // Look up the requested thread.
   auto threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {
      // Can only set priority on threads while they are in CREATE_SUSPENDED state.
      //assert(false);
      return false;
   }

   // Store the new priority.
   threadInfo->m_element2.m_iPriority = iPriority;

   return true;
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


BOOL WINAPI TlsFree(DWORD dwTlsIndex)
{
   synch_lock lock(g_pmutexTlsData);

   assert(dwTlsIndex < nextTlsIndex);
   for(int i = 0; i < freeTlsIndices.get_count(); i++)
   {
      assert(freeTlsIndices.element_at(i) != dwTlsIndex);
   }

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

   POSITION pos = all_thread_data().get_start_position();
   while( pos != NULL)
   {

      HTHREAD hThread;

      ThreadLocalData * pdata;

      all_thread_data().get_next_assoc(pos, hThread, pdata);

      if(natural(pdata->get_count()) > dwTlsIndex)
      {
         pdata->element_at(dwTlsIndex) = nullptr;
      }
   }

   return true;
}


LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex)
{
   ThreadLocalData* threadData = currentThreadData;

   if (threadData && natural(threadData->get_count()) > dwTlsIndex)
   {
      // Return the value of an allocated TLS slot.
      return threadData->element_at(dwTlsIndex);
   }
   else
   {
      // Default value for unallocated slots.
      return nullptr;
   }
}

LPVOID WINAPI TlsGetValue(HTHREAD hthread, DWORD dwTlsIndex)
{
   ThreadLocalData* threadData = all_thread_data()[hthread];

   if (threadData && natural(threadData->get_count()) > dwTlsIndex)
   {
      // Return the value of an allocated TLS slot.
      return threadData->element_at(dwTlsIndex);
   }
   else
   {
      // Default value for unallocated slots.
      return nullptr;
   }
}


BOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue)
{
   ThreadLocalData* threadData = currentThreadData;

   if (!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
         threadData = new ThreadLocalData;

         synch_lock lock(g_pmutexTlsData);

         all_thread_data().set_at(currentThread, threadData);

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

BOOL WINAPI TlsSetValue(HTHREAD hthread, DWORD dwTlsIndex, LPVOID lpTlsValue)
{

   ThreadLocalData* threadData = all_thread_data()[hthread];

   if (!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
         threadData = new ThreadLocalData;

         synch_lock lock(g_pmutexTlsData);

         all_thread_data().set_at(hthread, threadData);

         //currentThreadData = threadData;
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

      try
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



      synch_lock ml(g_pmutexTlsData);

      all_thread_data().remove_key(currentThread);

      currentThreadData = nullptr;

      delete threadData;
   }
}




int WINAPI GetThreadPriority(_In_ HTHREAD hThread)
{

   synch_lock lock(g_pmutexPendingThreadsLock);

   // Look up the requested thread.
   auto threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {

      return 0x80000000;

   }

   return threadInfo->m_element2.m_iPriority;

}



mutex * os_thread::s_pmutex = NULL;
comparable_raw_array < os_thread * >::type * os_thread::s_pptra = NULL;
__declspec(thread) os_thread * t_posthread = NULL;

os_thread::os_thread(uint32_t ( * pfn)(void *), void * pv)
{

   m_pfn    = pfn;
   m_pv     = pv;
   m_bRun   = true;


   synch_lock ml(s_pmutex);

   s_pptra->add(this);

}


os_thread::~os_thread()
{

   synch_lock ml(s_pmutex);

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

         synch_lock ml(s_pmutex);

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

unsigned int WINAPI os_thread::thread_proc(LPVOID lpparameter)
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

/*   Gdiplus::GdiplusStartupInput     * pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   Gdiplus::GdiplusStartupOutput    * pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   DWORD_PTR gdiplusToken                                      = NULL;
   DWORD_PTR gdiplusHookToken                                  = NULL;

   Gdiplus::Status statusStartup = GdiplusStartup(&gdiplusToken, pgdiplusStartupInput, pgdiplusStartupOutput);

   if(statusStartup != Gdiplus::Ok)
   {

      return -1;

   }*/

   //attach_thread_input_to_main_thread();

   uint32_t dwRet = 0xffffffff;

   try
   {

      dwRet = m_pfn(m_pv);

   }
   catch(...)
   {
   }

//   Gdiplus::GdiplusShutdown(gdiplusToken);

   return dwRet;

}



/*os_thread::os_thread(uint32_t (* pfn)(void *), void * pv)
{

   m_pfn    = pfn;
   m_pv     = pv;

}*/


uint32_t thread_proc_create_thread(void * lpparameter)
{

   os_thread * posthread = (os_thread *) lpparameter;


   attach_thread_input_to_main_thread(true);

   DWORD dwRet = 0xffffffff;

   try
   {

      dwRet = posthread->m_pfn(posthread->m_pv);

   }
   catch(...)
   {
   }


   delete posthread;

   return dwRet;

}


HTHREAD start_thread(uint32_t ( * pfn)(void *), void * pv, int iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL, 0, pfn, pv, 0, NULL);

}

HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint32_t cbStack, uint32_t ( * pfn)(void *), void * pv, uint32_t uiFlags, uint32_t * lpuiId)
{

   return ::CreateThread(lpsa, cbStack, &thread_proc_create_thread, (void *) new os_thread(pfn, pv), uiFlags, lpuiId);

}



thread_layer::~thread_layer()
{


}


int thread_layer::run()
{

   throw "todo"; // message pumping

   /*
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

   return m_iResult;*/

   return -1;

}

bool thread_layer::on_idle()
{

   return false;

}

void thread_layer::wait_thread(uint32_t dwMillis)
{

   ::WaitForSingleObjectEx(m_hthread, dwMillis, FALSE);

}

HTHREAD g_hMainThread = NULL;
UINT g_uiMainThread = -1;

void set_main_thread(HTHREAD hThread)
{

   //   MSG msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_hMainThread = hThread;

}

void set_main_thread_id(UINT uiThread)
{

   //   MSG msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_uiMainThread = uiThread;

}


HTHREAD get_main_thread()
{
   return g_hMainThread;

}
UINT   get_main_thread_id()
{
   return g_uiMainThread;
}


void attach_thread_input_to_main_thread(int_bool bAttach)
{
   return;
   //   MSG msg;

   // metrowin todo
   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   //   AttachThreadInput(::GetCurrentThreadId(), get_main_thread_id(), bAttach ? TRUE : FALSE); // AttachThreadInput function used to attach thread input to main thread in Windows Desktop

}

uint32_t thread_layer::proc(void * pv)
{

   thread_layer * player   = (thread_layer *) pv;

   player->m_hthread       = ::get_current_thread();

   player->m_nId           = ::get_current_thread_id();

   return player->run();

}


mq * get_mq()
{

   mq * pmq = (mq *) TlsGetValue(TLS_MESSAGE_QUEUE);

   if(pmq != NULL)
      return pmq;

   pmq = new mq();

   TlsSetValue(TLS_MESSAGE_QUEUE, pmq);

   return pmq;

}

bool is_thread(HTHREAD h)
{
   return get_thread_id(h) != 0;
}

mq * get_mq(HTHREAD h)
{


   mq * pmq = (mq *) TlsGetValue(h, TLS_MESSAGE_QUEUE);

   if(pmq != NULL)
      return pmq;

   pmq = new mq();

   TlsSetValue(h, TLS_MESSAGE_QUEUE, pmq);

   return pmq;

}


WINBOOL WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

   single_lock ml(&pmq->m_mutex, false);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT) -1;

restart:

   ml.lock();

   for(int i = 0; i < pmq->ma.get_count(); i++)
   {
      MESSAGE & msg = pmq->ma[i];


      if(msg.message == WM_QUIT)
      {
         return FALSE;
      }


      if((oswindow == NULL || msg.oswindow == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {
         *lpMsg = msg;
         pmq->ma.remove_at(i);
         return TRUE;
      }
   }

   ml.unlock();

   while(!pmq->m_eventNewMessage.wait(millis(84)).signaled())
   {

      if(::get_current_thread() != NULL && ::get_current_thread()->m_pthread != NULL)
      {

         ::get_current_thread()->m_pthread->step_timer();

      }

   }

   pmq->m_eventNewMessage.ResetEvent();

   goto restart;

}


BOOL WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT) -1;

   for(int i = 0; i < pmq->ma.get_count(); i++)
   {
      MESSAGE & msg = pmq->ma[i];

      if((oswindow == NULL || msg.oswindow == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {
         *lpMsg = msg;
         if(wRemoveMsg & PM_REMOVE)
         {
            pmq->ma.remove_at(i);
         }
         return TRUE;
      }
   }

   return FALSE;
}



DWORD WINAPI get_thread_id(HTHREAD Thread)
{

   synch_lock mlThreadId(g_pmutexThreadIdLock);

   auto p = thread_id_map().PLookup(Thread);

   if(p == NULL)
      return NULL;


   return p->m_element2;

}

HTHREAD WINAPI get_thread_handle(DWORD dw)
{

   synch_lock mlThreadIdHandle(g_pmutexThreadIdHandleLock);

   auto p = thread_id_handle_map().PLookup(dw);

   if(p == NULL)
      return NULL;


   return p->m_element2;

}


BOOL WINAPI PostThreadMessageW(DWORD idThread, UINT message, WPARAM wparam, LPARAM lparam)
{

   HTHREAD h = ::get_thread_handle(idThread);

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   msg.oswindow   = NULL;
   msg.message    = message;
   msg.wParam     = wparam;
   msg.lParam     = lparam;
   msg.pt.x       = 0x80000000;
   msg.pt.y       = 0x80000000;
   msg.time       = -1;

   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}


CLASS_DECL_AURA WINBOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   HTHREAD  h = oswindow->m_pui->m_pthread->get_os_handle();

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.oswindow   = oswindow;
   msg.message    = Msg;
   msg.wParam     = wParam;
   msg.lParam     = lParam;
   msg.pt.x       = 0x80000000;
   msg.pt.y       = 0x80000000;


   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}


namespace core
{

///  \brief		global function to set thread priority for current thread
	///  \param		new priority
	bool set_thread_priority(int32_t priority)
	{
      return ( ::SetThreadPriority(::get_current_thread(), priority) != 0 );

	}


	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread

	int32_t thread_priority()
	{

      return ::GetThreadPriority(::get_current_thread());

   }


} // namespace core


HTHREAD get_current_thread()
{

   return currentThread;

}



DWORD get_current_thread_id()
{

   return get_thread_id(get_current_thread());

}
