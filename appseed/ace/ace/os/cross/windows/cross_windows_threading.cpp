//#include "framework.h"

static DWORD nextTlsIndex = 0;
typedef void_ptra ThreadLocalData;

#if defined(LINUX) // || defined(ANDROID)

bool ace_defer_process_x_message(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek);

#endif

#if defined(APPLE_IOS) || defined(ANDROID) || defined(LINUX)
thread_pointer < ThreadLocalData > currentThreadData;
#else
CLASS_DECL_THREAD ThreadLocalData * currentThreadData;
#endif
//thread_int_ptr < DWORD > currentThreadId;
//thread_pointer < HTHREAD > currentThread;
//thread_pointer < hthread > t_phthread;


raw_array<DWORD> * freeTlsIndices = NULL;
mutex * g_pmutexTlsData = NULL;


//map < HTHREAD,HTHREAD,HTHREAD,HTHREAD > * s_pmapHthreadHthread = NULL;
//map < DWORD,DWORD,HTHREAD,HTHREAD > * s_pmapDwordHthread = NULL;
//map < HTHREAD,HTHREAD,DWORD,DWORD > * s_pmapHthreadDword = NULL;
map < IDTHREAD,IDTHREAD,ThreadLocalData *,ThreadLocalData * > * allthreaddata = NULL;


mutex * g_pmutexMq = NULL;

map < HTHREAD,HTHREAD,mq *,mq * > * g_pmapMq = NULL;





//mq * __get_mq(IDTHREAD idthread)
//{
//
//   synch_lock sl(g_pmutexMq);
//
//   auto pmq = (mq *)__thread_get_data(idthread,TLS_MESSAGE_QUEUE);
//
//   if(pmq != NULL)
//      return pmq;
//
//   pmq   = new mq();
//
//   pmq->m_idthread    = idthread;
//
//   __thread_set_data(idthread,TLS_MESSAGE_QUEUE,pmq);
//
//   return pmq;
//
//}
//
//
//

CLASS_DECL_ACE int_bool WINAPI GetMessageW(LPMESSAGE lpMsg,oswindow oswindow,UINT wMsgFilterMin,UINT wMsgFilterMax)
{


   bool bFirst = true;

   mq * pmq = __get_mq(GetCurrentThreadId());

   if(pmq == NULL)
      return FALSE;

   synch_lock sl(&pmq->m_mutex);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT)-1;

#if defined(LINUX) || defined(ANDROID)
   HTHREAD hthread = ::GetCurrentThread();
   DWORD idThre = ::GetCurrentThreadId();
#endif

restart:

   for(int32_t i = 0; i < pmq->ma.get_count(); i++)
   {
      MESSAGE & msg = pmq->ma[i];


      if(msg.message == WM_QUIT)
      {
         *lpMsg = msg;
         //pmq->ma.remove_at(i);

         pmq->ma.remove_all();

         //         __clear_mq();

         return FALSE;
      }


      if((oswindow == NULL || msg.hwnd == oswindow) && msg.message >= wMsgFilterMin && msg.message <= wMsgFilterMax)
      {
         *lpMsg = msg;
         pmq->ma.remove_at(i);
         return TRUE;
      }
   }

#if defined(LINUX) // || defined(ANDROID)
//   if(::get_thread() != NULL)
//   {
//
//      if(!::get_thread()->get_run())
//         return FALSE;
//
//      //      ::get_thread()->step_timer();
//
//      if(!::get_thread()->get_run())
//         return FALSE;
//
//   }

   //if(ace_defer_process_x_message(hthread,lpMsg,oswindow,false))
     // return TRUE;

#endif

   //if(bFirst)
   {

      //pmq->m_eventNewMessage.wait(millis(11));

      sl.unlock();

      pmq->m_eventNewMessage.wait();

      sl.lock();

      pmq->m_eventNewMessage.ResetEvent();



      //bFirst = false;

      goto restart;

   }
//   else
//   {
//
//      lpMsg->message = 0xffffffff;
//      lpMsg->hwnd    = NULL;
//      lpMsg->wParam  = 0;
//      lpMsg->lParam  = 0;
//      lpMsg->pt.x    = 0x80000000;
//      lpMsg->pt.y    = 0x80000000;

//      return TRUE;
//
//   }






}


CLASS_DECL_ACE int_bool WINAPI PeekMessageW(LPMESSAGE lpMsg,oswindow oswindow,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg)
{

   mq * pmq = __get_mq(GetCurrentThreadId());

   if(pmq == NULL)
      return FALSE;

#if defined(LINUX) || defined(ANDROID)
   HTHREAD hthread = ::GetCurrentThread();
   DWORD idThre = ::GetCurrentThreadId();
#endif

   synch_lock ml(&pmq->m_mutex);

   if(wMsgFilterMax == 0)
      wMsgFilterMax = (UINT)-1;

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
   if(ace_defer_process_x_message(hthread,lpMsg,oswindow,!(wRemoveMsg & PM_REMOVE)))
      return TRUE;
#endif

   return FALSE;

}



DWORD WINAPI tls_alloc()
{

   synch_lock lock(g_pmutexTlsData);

   // Can we reuse a previously freed TLS slot?
   if(freeTlsIndices->get_count() > 0)
   {
      DWORD result = freeTlsIndices->element_at(freeTlsIndices->get_count() - 1);
      freeTlsIndices->remove_at(freeTlsIndices->get_count() - 1);
      return result;
   }

   // Allocate a new TLS slot.
   return nextTlsIndex++;
}


int_bool WINAPI tls_free(DWORD dwIndex)
{

   synch_lock lock(g_pmutexTlsData);

   //assert(dwIndex < nextTlsIndex);
   /*   for(int32_t i = 0; i < freeTlsIndices.get_count(); i++)
   {
   assert(freeTlsIndices.element_at(i) != dwIndex);
   }*/

   // Store this slot for reuse by TlsAlloc.
   try
   {
      freeTlsIndices->add(dwIndex);
   }
   catch(...)
   {
      return false;
   }

   // Zero the value for all threads that might be using this now freed slot.

   POSITION pos = allthreaddata->get_start_position();
   while(pos != NULL)
   {

      IDTHREAD iThreadId;

      ThreadLocalData * pdata;

      allthreaddata->get_next_assoc(pos,iThreadId,pdata);

      if(compare::gt(pdata->get_count(),dwIndex))
      {
         pdata->element_at(dwIndex) = NULL;
      }
   }

   return true;
}


LPVOID WINAPI tls_get_value(DWORD dwIndex)
{
   ThreadLocalData* threadData = currentThreadData;

   if(threadData && compare::gt(threadData->get_count(),dwIndex))
   {
      // Return the value of an allocated TLS slot.
      return threadData->element_at(dwIndex);
   }
   else
   {
      threadData = allthreaddata->operator[](::get_current_thread_id());
      if(threadData)
      {
         currentThreadData = threadData;
         if(compare::gt(threadData->get_count(),dwIndex))
         {
            return threadData->element_at(dwIndex);
         }
      }
      // Default value for unallocated slots.
      return NULL;
   }
}


//void * __thread_get_data(IDTHREAD hthread,uint32_t dwIndex)
//{
//
//   try
//   {
//
//      synch_lock lock(g_pmutexTlsData);
//
//      if(allthreaddata->is_empty())
//         return NULL;
//      auto ppair = allthreaddata->PLookup((IDTHREAD)hthread);
//
//      if(ppair == NULL)
//         return NULL;
//
//      ThreadLocalData * threadData = ppair->m_element2;
//
//      if(threadData && compare::gt(threadData->get_count(),dwIndex))
//      {
//
//         // Return the value of an allocated TLS slot.
//         return threadData->element_at(dwIndex);
//
//      }
//      else
//      {
//
//         // Default value for unallocated slots.
//         return NULL;
//
//      }
//
//   }
//   catch(...)
//   {
//
//      return NULL;
//
//   }
//
//}


int_bool thread_set_data(uint32_t dwIndex,void * pvalue)
{

   ThreadLocalData* threadData = currentThreadData;

   if(!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
         threadData = new ThreadLocalData;

         synch_lock lock(g_pmutexTlsData);

         allthreaddata->set_at(get_current_thread_id(),threadData);

         currentThreadData = threadData;

      }
      catch(...)
      {
         if(threadData)
            delete threadData;

         return false;
      }
   }

   // Store the new value for this slot.
   threadData->set_at_grow(dwIndex,pvalue);

   return true;

}


int_bool __thread_set_data(IDTHREAD hthread,uint32_t dwIndex,void * pvalue)
{

   synch_lock lock(g_pmutexTlsData);

   ThreadLocalData * threadData = allthreaddata->operator [] ((IDTHREAD)hthread);

   if(!threadData)
   {
      // First time allocation of TLS data for this thread.
      try
      {
         threadData = new ThreadLocalData;

         allthreaddata->set_at((IDTHREAD)hthread,threadData);

      }
      catch(...)
      {
         if(threadData)
            delete threadData;

         return false;
      }
   }

   // Store the new value for this slot.
   threadData->set_at_grow(dwIndex,pvalue);

   return true;

}


// Called at thread exit to clean up TLS allocations.
void thread_shutdown()
{

   ThreadLocalData * threadData = currentThreadData;

   if(threadData)
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

      auto pmq = (mq *) __thread_get_data(get_current_thread_id(),TLS_MESSAGE_QUEUE);

      if(pmq != NULL)
      {

         ::ace::del(pmq);

      }

      allthreaddata->remove_key(get_current_thread_id());

      currentThreadData = NULL;

      delete threadData;
   }
}




uint32_t thread_alloc()
{

   synch_lock lock(g_pmutexTlsData);

   // Can we reuse a previously freed TLS slot?
   if(freeTlsIndices != NULL && freeTlsIndices->get_count() > 0)
   {
      DWORD result = freeTlsIndices->element_at(freeTlsIndices->get_count() - 1);
      freeTlsIndices->remove_at(freeTlsIndices->get_count() - 1);
      return result;
   }

   // Allocate a new TLS slot.
   return nextTlsIndex++;
}


int_bool thread_free(uint32_t dwIndex)
{

   synch_lock lock(g_pmutexTlsData);

   //assert(dwIndex < nextTlsIndex);
   /*   for(int32_t i = 0; i < freeTlsIndices.get_count(); i++)
   {
   assert(freeTlsIndices.element_at(i) != dwIndex);
   }*/

   // Store this slot for reuse by TlsAlloc.
   try
   {
      freeTlsIndices->add(dwIndex);
   }
   catch(...)
   {
      return false;
   }

   // Zero the value for all threads that might be using this now freed slot.

   POSITION pos = allthreaddata->get_start_position();
   while(pos != NULL)
   {

      IDTHREAD iThreadId;

      ThreadLocalData * pdata;

      allthreaddata->get_next_assoc(pos,iThreadId,pdata);

      if(compare::gt(pdata->get_count(),dwIndex))
      {
         pdata->element_at(dwIndex) = NULL;
      }
   }

   return true;
}


void * thread_get_data(uint32_t dwIndex)
{
   ThreadLocalData* threadData = currentThreadData;

   if(threadData && compare::gt(threadData->get_count(),dwIndex))
   {
      // Return the value of an allocated TLS slot.
      return threadData->element_at(dwIndex);
   }
   else
   {
      threadData = allthreaddata->operator[](get_current_thread_id());
      if(threadData)
      {
         currentThreadData = threadData;
         if(compare::gt(threadData->get_count(),dwIndex))
         {
            return threadData->element_at(dwIndex);
         }
      }
      // Default value for unallocated slots.
      return NULL;
   }
}


void * __thread_get_data(IDTHREAD hthread,uint32_t dwIndex)
{

   try
   {

      synch_lock lock(g_pmutexTlsData);

      if(allthreaddata == NULL || allthreaddata->is_empty())
      {

         return NULL;

      }

      auto ppair = allthreaddata->PLookup((IDTHREAD)hthread);

      if(ppair == NULL)
         return NULL;

      ThreadLocalData * threadData = ppair->m_element2;

      if(threadData && compare::gt(threadData->get_count(),dwIndex))
      {

         // Return the value of an allocated TLS slot.
         return threadData->element_at(dwIndex);

      }
      else
      {

         // Default value for unallocated slots.
         return NULL;

      }

   }
   catch(...)
   {

      return NULL;

   }

}


//int_bool thread_set_data(uint32_t dwIndex,void * lpTlsValue)
//{
//
//   ThreadLocalData* threadData = currentThreadData;
//
//   if(!threadData)
//   {
//      // First time allocation of TLS data for this thread.
//      try
//      {
//         threadData = new ThreadLocalData;
//
//         synch_lock lock(g_pmutexTlsData);
//
//         allthreaddata->set_at(get_current_thread_id(),threadData);
//
//         currentThreadData = threadData;
//
//      }
//      catch(...)
//      {
//         if(threadData)
//            delete threadData;
//
//         return false;
//      }
//   }
//
//   // Store the new value for this slot.
//   threadData->set_at_grow(dwIndex,lpTlsValue);
//
//   return true;
//}

//int_bool __thread_set_data(IDTHREAD hthread,uint32_t dwIndex,void * pvalue)
//{
//
//   synch_lock lock(g_pmutexTlsData);
//
//   ThreadLocalData * threadData = allthreaddata->operator [] ((IDTHREAD)hthread);
//
//   if(!threadData)
//   {
//      // First time allocation of TLS data for this thread.
//      try
//      {
//         threadData = new ThreadLocalData;
//
//         allthreaddata->set_at((IDTHREAD)hthread,threadData);
//
//      }
//      catch(...)
//      {
//         if(threadData)
//            delete threadData;
//
//         return false;
//      }
//   }
//
//   // Store the new value for this slot.
//   threadData->set_at_grow(dwIndex,lpTlsValue);
//
//   return true;
//}

//// Called at thread exit to clean up TLS allocations.
//void thread_shutdown()
//{
//
//   ThreadLocalData * threadData = currentThreadData;
//
//   if(threadData)
//   {
//
//      /*      try
//      {
//
//      IDWriteFactory * pfactory = TlsGetWriteFactory();
//
//      if(pfactory != NULL)
//      {
//
//      pfactory->Release();
//
//      }
//
//      }
//      catch(...)
//      {
//      }
//
//      try
//      {
//
//      ID2D1Factory1 * pfactory = GetD2D1Factory1();
//
//      if(pfactory != NULL)
//      {
//
//      //pfactory->Release();
//
//      }
//
//      }
//      catch(...)
//      {
//      }
//
//      */
//
//      synch_lock ml(g_pmutexTlsData);
//
//      auto pmq = (mq *)thread_get_data((IDTHREAD)pthread_self(),TLS_MESSAGE_QUEUE);
//
//      if(pmq != NULL)
//      {
//
//         ::ace::del(pmq);
//
//      }
//
//      allthreaddata->remove_key((IDTHREAD)pthread_self());
//
//      currentThreadData = NULL;
//
//      delete threadData;
//   }
//}



mq * __get_mq(IDTHREAD  h);


mq * __get_mq()
{

   synch_lock sl(g_pmutexMq);

   auto pmq = (mq *)thread_get_data(TLS_MESSAGE_QUEUE);

   if(pmq != NULL)
      return pmq;

   pmq   = new mq();

   pmq->m_idthread    = get_current_thread_id();

   thread_set_data(TLS_MESSAGE_QUEUE,pmq);

   return pmq;

}



mq * __get_mq(IDTHREAD idthread)
{

   synch_lock sl(g_pmutexMq);

   mq * pmq = (mq *)__thread_get_data(idthread,TLS_MESSAGE_QUEUE);

   if(pmq != NULL)
      return pmq;

   pmq   = new mq();

   pmq->m_idthread    = idthread;

   __thread_set_data(idthread,TLS_MESSAGE_QUEUE,pmq);

   return pmq;

}






void __clear_mq()
{

   synch_lock sl(g_pmutexMq);

   IDTHREAD idthread = get_current_thread_id();

   auto pmq = (mq *) __thread_get_data(idthread, TLS_MESSAGE_QUEUE);

   if(pmq == NULL)
      return;

   ::ace::del(pmq);

   __thread_set_data(idthread, TLS_MESSAGE_QUEUE, NULL);

}



mq::mq():
   m_eventNewMessage(get_thread_app())
{

   m_eventNewMessage.ResetEvent();

}



void __node_init_cross_windows_threading()
{

allthreaddata = new map < IDTHREAD,IDTHREAD,ThreadLocalData *,ThreadLocalData * >();

freeTlsIndices = new raw_array<DWORD>();


}

void __node_term_cross_windows_threading()
{

   if(freeTlsIndices != NULL)
   {

      delete freeTlsIndices;

      freeTlsIndices = NULL;

   }

   if(allthreaddata != NULL)
   {

      for(auto & p : *allthreaddata)
      {

         delete p.m_element2;

      }

      delete allthreaddata;

      allthreaddata = NULL;

   }


}



