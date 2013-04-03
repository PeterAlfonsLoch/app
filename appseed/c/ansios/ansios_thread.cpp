#include "framework.h"

#ifdef LINUX
bool defer_process_x_message(HTHREAD hthread, LPMESSAGE lpMsg, oswindow oswindow, bool bPeek);
#endif

/*class sys_thread
{
public:


   pthread_t                        m_pthread;
   sys_message_queue                m_messagequeue;


   sys_thread(pthread_t pthread);


   WINBOOL GetMessage(MESSAGE * pmsg);


};


class sys_thread_pool
{
public:


   simple_mutex                     m_mutex;
   simple_array < sys_thread * >    m_threadptra;


   sys_thread * get_current();
   sys_thread * get(pthread_t pthread);


};

static sys_thread_pool * g_psysthreadpool;

#include "framework.h"



// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#include "framework.h"

#include <assert.h>
//#include <vector>
//#include <set>
//#include <map>

//using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
*/

void * WINAPI thread_proc_create_thread(LPVOID lpparameter);

// Stored data for CREATE_SUSPENDED and ResumeThread.
struct PendingThreadInfo
{

   DWORD (WINAPI * lpStartAddress)(LPVOID);
   LPVOID lpParameter;
   HTHREAD m_hthread;
   simple_event  * suspensionEvent;
   int32_t nPriority;
   int32_t cbStack;

   PendingThreadInfo()
   {
   }

};

static simple_map < HTHREAD, PendingThreadInfo > & pendingThreads()
{

   static simple_map < HTHREAD, PendingThreadInfo > * pts = new simple_map < HTHREAD, PendingThreadInfo >();

   return *pts;

}
static simple_mutex pendingThreadsLock;

static simple_mutex threadHandleLock;
static simple_map < HTHREAD, HTHREAD > & thread_handle_map()
{

   static simple_map < HTHREAD, HTHREAD > * s_pmap = new simple_map < HTHREAD, HTHREAD >();

   return *s_pmap;

}

static simple_mutex threadIdHandleLock;
static simple_map < DWORD, HTHREAD > & thread_id_handle_map()
{

   static simple_map < DWORD, HTHREAD > * s_pmap = new simple_map < DWORD, HTHREAD >();

   return *s_pmap;

}


static simple_mutex threadIdLock;
static simple_map < HTHREAD, DWORD > & thread_id_map()
{

   static simple_map < HTHREAD , DWORD > * s_pmap = new simple_map < HTHREAD, DWORD >();

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
typedef simple_array < void * > ThreadLocalData;



static __thread ThreadLocalData* currentThreadData = NULL;
static __thread DWORD currentThreadId = -1;
static __thread HTHREAD currentThread = NULL;


simple_map < HTHREAD, ThreadLocalData * > & all_thread_data()
{

   static simple_map < HTHREAD, ThreadLocalData * > * s_pallthreaddata = new simple_map < HTHREAD, ThreadLocalData * >();

   return *s_pallthreaddata;

}

static DWORD nextTlsIndex = 0;
static simple_array<DWORD> freeTlsIndices;
static simple_mutex tlsAllocationLock;


// Converts a Win32 thread priority to WinRT format.
static int32_t GetWorkItemPriority(int32_t nPriority)
{
   if (nPriority < 0)
      return nPriority; // WorkItemPriority::Low;
   else if (nPriority > 0)
      return nPriority; // WorkItemPriority::High;
   else
      return nPriority; // WorkItemPriority::Normal;
}


// Helper shared between CreateThread and ResumeThread.
static os_thread * StartThread(LPTHREAD_START_ROUTINE pfn, LPVOID pv, HTHREAD hthread, int32_t nPriority, SIZE_T cbStack)
{

   os_thread * pthread = new os_thread(pfn, pv);

   pthread->m_hthread = hthread;

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

   return pthread;

}


hthread::hthread()
{

   m_pevent = new simple_event(false, true);
   m_pthread = NULL;

}

hthread::~hthread()
{

   delete m_pevent;

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


   mutex_lock mlThreadId(threadIdLock);

   thread_id_map().set_at(threadHandle, DwThreadId());

   if(lpdwThreadId != NULL)
   {
      *lpdwThreadId = thread_id_map()[threadHandle];
   }



   mutex_lock mlThreadIdHandle(threadIdHandleLock);

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

//   mutex_lock mlThreadHandle(threadHandleLock);

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
            info.suspensionEvent    = new simple_event(false, true);
            info.nPriority = 0;

            mutex_lock lock(pendingThreadsLock);

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
   mutex_lock lock(pendingThreadsLock);

   // Look up the requested thread.
   simple_map < HTHREAD , PendingThreadInfo >::pair * threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {
      // Can only resume threads while they are in CREATE_SUSPENDED state.
      //assert(false);
      return (DWORD)-1;
   }

   // Start the thread.
   try
   {
      PendingThreadInfo& info = threadInfo->m_value;

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


WINBOOL WINAPI SetThreadPriority(HTHREAD hThread, int32_t nPriority)
{
   mutex_lock lock(pendingThreadsLock);

   // Look up the requested thread.
   simple_map < HTHREAD, PendingThreadInfo >::pair * threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {
      // Can only set priority on threads while they are in CREATE_SUSPENDED state.
      //assert(false);
      return false;
   }

   // Store the new priority.
   threadInfo->m_value.nPriority = nPriority;

   return TRUE;
}




DWORD WINAPI TlsAlloc()
{
   mutex_lock lock(tlsAllocationLock);

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


WINBOOL WINAPI TlsFree(DWORD dwTlsIndex)
{
   mutex_lock lock(tlsAllocationLock);

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

   POSITION pos = all_thread_data().get_start_position();
   while( pos != NULL)
   {

      HTHREAD hThread;

      ThreadLocalData * pdata;

      all_thread_data().get_next_assoc(pos, hThread, pdata);

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
      // Default value for unallocated slots.
      return NULL;
   }
}

LPVOID WINAPI TlsGetValue(HTHREAD hthread, DWORD dwTlsIndex)
{
   ThreadLocalData* threadData = all_thread_data()[hthread];

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


WINBOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue)
{
   ThreadLocalData* threadData = currentThreadData;

   if (!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
            threadData = new ThreadLocalData;

            mutex_lock lock(tlsAllocationLock);

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

WINBOOL WINAPI TlsSetValue(HTHREAD hthread, DWORD dwTlsIndex, LPVOID lpTlsValue)
{
   ThreadLocalData* threadData = all_thread_data()[hthread];

   if (!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
            threadData = new ThreadLocalData;

            mutex_lock lock(tlsAllocationLock);

            all_thread_data().set_at(hthread, threadData);

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

      mutex_lock ml(tlsAllocationLock);

      all_thread_data().remove_key(currentThread);

      currentThreadData = NULL;

      delete threadData;
   }
}




int32_t WINAPI GetThreadPriority(HTHREAD  hThread)
{

   mutex_lock lock(pendingThreadsLock);

   // Look up the requested thread.
   simple_map < HTHREAD, PendingThreadInfo >::pair * threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {

      return 0x80000000;

   }

   return threadInfo->m_value.nPriority;

}




os_thread::os_thread(DWORD (WINAPI * pfn)(LPVOID), LPVOID pv)
{
   m_pfn = pfn;
   m_pv = pv;
}


void * WINAPI thread_proc_create_thread(LPVOID lpparameter)
{

   os_thread * posthread = (os_thread *) lpparameter;

   mutex_lock mlThreadHandle(threadHandleLock);

   currentThread =  posthread->m_hthread;

   mlThreadHandle.unlock();

   mutex_lock mlThreadId(threadIdLock);

   currentThreadId =  thread_id_map()[currentThread];

   mlThreadId.unlock();

   mlThreadHandle.unlock();

   // Run the user callback.
   //attach_thread_input_to_main_thread();

   DWORD dwRet = 0xffffffff;

   try
   {

      dwRet = posthread->m_pfn(posthread->m_pv);

   }
   catch (...)
   {

   }

   // Clean up any TLS allocations made by this thread.
   TlsShutdown();

   // Signal that the thread has completed.
   currentThread->m_pevent->set_event();
   delete currentThread;

   delete posthread;

   return (void *) (int_ptr) dwRet;

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

CLASS_DECL_c void set_main_thread(HANDLE hThread)
{

//   MESSAGE msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_hMainThread = hThread;

}

CLASS_DECL_c void set_main_thread_id(UINT uiThread)
{

//   MESSAGE msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

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




CLASS_DECL_c WINBOOL WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{


   bool bFirst = true;

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex, false);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT) -1;

#ifdef LINUX
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

#ifdef LINUX
   if(hthread != NULL && hthread->m_pthread != NULL && hthread->m_pthread->get_x_window_count() > 0)
   {

      if(defer_process_x_message(hthread, lpMsg, oswindow, false))
         return TRUE;

   }
#endif

   if(bFirst)
   {

      pmq->m_eventNewMessage.wait(25);

      pmq->m_eventNewMessage.reset_event();

      bFirst = false;

      goto restart;

   }
   else
   {

      lpMsg->message = 0xffffffff;

      return true;

   }


}


CLASS_DECL_c WINBOOL WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

#ifdef LINUX
   HTHREAD hthread = ::GetCurrentThread();
   DWORD idThre = ::GetCurrentThreadId();
#endif

   mutex_lock ml(pmq->m_mutex);

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

#ifdef LINUX
   if(hthread != NULL && hthread->m_pthread != NULL && hthread->m_pthread->get_x_window_count() > 0)
   {

      if(defer_process_x_message(hthread, lpMsg, oswindow, !(wRemoveMsg & PM_REMOVE)))
         return TRUE;
   }
#endif

   return FALSE;

}



CLASS_DECL_c DWORD WINAPI GetThreadId(HTHREAD Thread)
{

   mutex_lock mlThreadId(threadIdLock);

   simple_map < HTHREAD, DWORD >::pair * p = thread_id_map().PLookup(Thread);

   if(p == NULL)
      return -1;


   return p->m_value;

}

CLASS_DECL_c HTHREAD  WINAPI get_thread_handle(DWORD dw)
{

   mutex_lock mlThreadIdHandle(threadIdHandleLock);

   simple_map < DWORD, HTHREAD >::pair * p = thread_id_handle_map().PLookup(dw);

   if(p == NULL)
      return NULL;


   return p->m_value;

}


CLASS_DECL_c WINBOOL WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   HTHREAD h = ::get_thread_handle(idThread);

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.message = Msg;
   msg.wParam  = wParam;
   msg.lParam  = lParam;

   pmq->ma.add(msg);

//   void * p = pmq->ma[pmq->ma.get_count() -1].hwnd;

   pmq->m_eventNewMessage.set_event();

   return true;

}

CLASS_DECL_c WINBOOL WINAPI PostMessageW(oswindow oswindow, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   HTHREAD  h = oswindow.get_user_interaction_base()->m_pthread->get_os_handle();

   if(h == NULL)
      return FALSE;


   mq * pmq = get_mq(h);

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   msg.hwnd       = oswindow;
   msg.message    = Msg;
   msg.wParam     = wParam;
   msg.lParam     = lParam;

   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}







void thread_layer::wait_thread(DWORD dwMillis)
{

   try
   {

      m_hthread->m_pevent->wait(dwMillis);

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



CLASS_DECL_c HTHREAD GetCurrentThread()
{

   return currentThread;

}

CLASS_DECL_c UINT GetCurrentThreadId()
{

   return currentThreadId;

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




