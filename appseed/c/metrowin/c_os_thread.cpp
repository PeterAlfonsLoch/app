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


// Stored data for CREATE_SUSPENDED and ResumeThread.
struct PendingThreadInfo
{

   
   uint32_t (*       m_pfn)(void *);
   void *            m_pv;
   HANDLE            m_hCompletionEvent;
   HANDLE            m_hSuspensionEvent;
   int               m_iPriority;
   

   PendingThreadInfo()
   {

      m_hSuspensionEvent = NULL;

   }


};


static simple_map<HANDLE, PendingThreadInfo> & pendingThreads()
{

   static simple_map<HANDLE, PendingThreadInfo> * pts = new simple_map<HANDLE, PendingThreadInfo>();

   return *pts;

}
static simple_mutex pendingThreadsLock;

static simple_mutex threadHandleLock;
static simple_map < HANDLE, HANDLE > & thread_handle_map()
{

   static simple_map < HANDLE, HANDLE > * s_pmap = new simple_map < HANDLE, HANDLE >();

   return *s_pmap;

}

static simple_mutex threadIdHandleLock;
static simple_map < DWORD, HANDLE > & thread_id_handle_map()
{

   static simple_map < DWORD, HANDLE > * s_pmap = new simple_map < DWORD, HANDLE >();

   return *s_pmap;

}


static simple_mutex threadIdLock;
static simple_map < HANDLE, DWORD > & thread_id_map()
{

   static simple_map < HANDLE, DWORD > * s_pmap = new simple_map < HANDLE, DWORD >();

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
typedef simple_array<void*> ThreadLocalData;



static __declspec(thread) ThreadLocalData* currentThreadData = nullptr;
static __declspec(thread) DWORD currentThreadId = -1;
static __declspec(thread) HANDLE currentThread = NULL;

simple_map < HANDLE, ThreadLocalData * > & all_thread_data()
{

   static simple_map < HANDLE, ThreadLocalData * > * s_pallthreaddata = new simple_map < HANDLE, ThreadLocalData * >();

   return *s_pallthreaddata;

}

static DWORD nextTlsIndex = 0;
static simple_array<DWORD> freeTlsIndices;
static simple_mutex tlsAllocationLock;


// Converts a Win32 thread priority to WinRT format.
static WorkItemPriority GetWorkItemPriority(int nPriority)
{
   if (nPriority < 0)
      return WorkItemPriority::Low;
   else if (nPriority > 0)
      return WorkItemPriority::High;
   else
      return WorkItemPriority::Normal;
}


// Helper shared between CreateThread and ResumeThread.
static void StartThread(uint32_t (* pfn)(void *), void * pv, HANDLE completionEvent, int nPriority)
{

   auto workItemHandler = ref new WorkItemHandler([=](IAsyncAction^)
   {

      mutex_lock mlThreadHandle(threadHandleLock);

      currentThread =  thread_handle_map()[(HANDLE)completionEvent];

      mlThreadHandle.unlock();

      mutex_lock mlThreadId(threadIdLock);

      currentThreadId =  thread_id_map()[currentThread];

      mlThreadId.unlock();

      mlThreadHandle.unlock();

      // Run the user callback.
      try
      {
         pfn(pv);
      }
      catch (...) { }

      // Clean up any TLS allocations made by this thread.
      TlsShutdown();

      // Signal that the thread has completed.
      SetEvent(completionEvent);
      CloseHandle(completionEvent);

   }, CallbackContext::Any);

   ThreadPool::RunAsync(workItemHandler, GetWorkItemPriority(nPriority), WorkItemOptions::TimeSliced);
}


HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, uint_ptr unusedStackSize, uint32_t (* pfn)(void *) , void * pv, uint32_t uiCreationFlags, uint32_t * puiId)
{
   // Validate parameters.
   assert(unusedThreadAttributes == nullptr);
   assert(unusedStackSize == 0);
   assert((uiCreationFlags & ~CREATE_SUSPENDED) == 0);
   //assert(unusedThreadId == nullptr);

   // Create a handle that will be signalled when the thread has completed.
   HANDLE threadHandle = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

   if (!threadHandle)
      return nullptr;

   mutex_lock mlThreadId(threadIdLock);

   thread_id_map().set_at(threadHandle, DwThreadId());

   if(puiId != NULL)
   {
      *puiId = thread_id_map()[threadHandle];
   }

   mutex_lock mlThreadIdHandle(threadIdHandleLock);

   thread_id_handle_map().set_at(thread_id_map()[threadHandle], threadHandle);

   mlThreadIdHandle.unlock();

   mlThreadId.unlock();

   // Make a copy of the handle for internal use. This is necessary because
   // the caller is responsible for closing the handle returned by CreateThread,
   // and they may do that before or after the thread has finished running.
   HANDLE completionEvent;

   if (!DuplicateHandle(GetCurrentProcess(), threadHandle, GetCurrentProcess(), &completionEvent, 0, false, DUPLICATE_SAME_ACCESS))
   {
      CloseHandle(threadHandle);
      return nullptr;
   }

   mutex_lock mlThreadHandle(threadHandleLock);

   thread_handle_map().set_at(completionEvent, threadHandle);

   mlThreadHandle.unlock();

   try
   {

      if (uiCreationFlags & CREATE_SUSPENDED)
      {

         // Store info about a suspended thread.
         PendingThreadInfo info;

         info.m_pfn                 = pfn;
         info.m_pv                  = pv;
         info.m_hCompletionEvent    = completionEvent;
         info.m_hSuspensionEvent    = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
         info.m_iPriority           = 0;

         mutex_lock lock(pendingThreadsLock);

         pendingThreads()[threadHandle] = info;

         //::WaitForSingleObjectEx(info.suspensionEvent, INFINITE, FALSE);
      }
      else
      {
         // Start the thread immediately.
         StartThread(pfn, pv, completionEvent, 0);
      }

      return threadHandle;
   }
   catch (...)
   {
      // Clean up if thread creation fails.
      CloseHandle(threadHandle);
      CloseHandle(completionEvent);

      return nullptr;
   }
}


DWORD WINAPI ResumeThread(HANDLE hThread)
{
   mutex_lock lock(pendingThreadsLock);

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
      
      PendingThreadInfo& info = threadInfo->m_value;

      StartThread(info.m_pfn, info.m_pv, info.m_hCompletionEvent, info.m_iPriority);

   }
   catch (...)
   {
      return (DWORD)-1;
   }

   // Remove this thread from the pending list.
   pendingThreads().remove_key(hThread);

   return 0;
}


BOOL WINAPI SetThreadPriority(HANDLE hThread, int iPriority)
{
   mutex_lock lock(pendingThreadsLock);

   // Look up the requested thread.
   auto threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {
      // Can only set priority on threads while they are in CREATE_SUSPENDED state.
      //assert(false);
      return false;
   }

   // Store the new priority.
   threadInfo->m_value.m_iPriority = iPriority;

   return true;
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


BOOL WINAPI TlsFree(DWORD dwTlsIndex)
{
   mutex_lock lock(tlsAllocationLock);

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

      HANDLE hThread;

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

LPVOID WINAPI TlsGetValue(HANDLE hthread, DWORD dwTlsIndex)
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

BOOL WINAPI TlsSetValue(HANDLE hthread, DWORD dwTlsIndex, LPVOID lpTlsValue)
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



      mutex_lock ml(tlsAllocationLock);

      all_thread_data().remove_key(currentThread);

      currentThreadData = nullptr;

      delete threadData;
   }
}




int WINAPI GetThreadPriority(_In_ HANDLE hThread)
{

   mutex_lock lock(pendingThreadsLock);

   // Look up the requested thread.
   auto threadInfo = pendingThreads().PLookup(hThread);

   if (threadInfo == NULL)
   {

      return 0x80000000;

   }

   return threadInfo->m_value.m_iPriority;

}




os_thread::os_thread(uint32_t (* pfn)(void *), void * pv)
{

   m_pfn    = pfn;
   m_pv     = pv;

}


uint32_t thread_proc_create_thread(void * lpparameter)
{

   os_thread * posthread = (os_thread *) lpparameter;


   attach_thread_input_to_main_thread();

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


HANDLE start_thread(uint32_t ( * pfn)(void *), void * pv, int iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL, 0, pfn, pv, 0, NULL);

}

HANDLE create_thread(LPSECURITY_ATTRIBUTES lpsa, uint32_t cbStack, uint32_t ( * pfn)(void *), void * pv, uint32_t uiFlags, uint32_t * lpuiId)
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

static HANDLE g_hMainThread = NULL;
static UINT g_uiMainThread = -1;

CLASS_DECL_c void set_main_thread(HANDLE hThread)
{

   //   MSG msg;

   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_hMainThread = hThread;

}

CLASS_DECL_c void set_main_thread_id(UINT uiThread)
{

   //   MSG msg;

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
   //   MSG msg;

   // metrowin todo
   throw "todo"; // PeekMessage function used to create message queue Windows Desktop

   //PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   //   AttachThreadInput(::GetCurrentThreadId(), get_main_thread_id(), bAttach ? TRUE : FALSE); // AttachThreadInput function used to attach thread input to main thread in Windows Desktop

}

uint32_t thread_layer::proc(void * pv)
{

   thread_layer * player   = (thread_layer *) pv;

   player->m_hthread       = ::GetCurrentThread();

   player->m_nId           = ::GetCurrentThreadId();

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

bool is_thread(HANDLE h)
{
   return GetThreadId(h) != 0;
}

mq * get_mq(HANDLE h)
{


   mq * pmq = (mq *) TlsGetValue(h, TLS_MESSAGE_QUEUE);

   if(pmq != NULL)
      return pmq;

   pmq = new mq();

   TlsSetValue(h, TLS_MESSAGE_QUEUE, pmq);

   return pmq;

}


CLASS_DECL_c WINBOOL WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax)
{

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex, false);

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

   pmq->m_eventNewMessage.wait();

   ::ResetEvent(pmq->m_eventNewMessage.m_hEvent);

   goto restart;

}


CLASS_DECL_c BOOL WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{

   mq * pmq = get_mq();

   if(pmq == NULL)
      return FALSE;

   mutex_lock ml(pmq->m_mutex);

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



CLASS_DECL_c DWORD WINAPI GetThreadId(HANDLE Thread)
{

   mutex_lock mlThreadId(threadIdLock);

   auto p = thread_id_map().PLookup(Thread);

   if(p == NULL)
      return NULL;


   return p->m_value;

}

CLASS_DECL_c HANDLE WINAPI get_thread_handle(DWORD dw)
{

   mutex_lock mlThreadIdHandle(threadIdHandleLock);

   auto p = thread_id_handle_map().PLookup(dw);

   if(p == NULL)
      return NULL;


   return p->m_value;

}


CLASS_DECL_c BOOL WINAPI PostThreadMessageW(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{

   HANDLE h = ::get_thread_handle(idThread);

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

   pmq->m_eventNewMessage.set_event();

   return true;

}


